//surf.cpp:Csurf类的实现文件

//#include "stdafx.h"
#include "surf.h"


Csurf::Csurf(int num)
{//num代表导入图像的数量
	ptpairs.clear();
	params = cvSURFParams(1000,1);
	storage = cvCreateMemStorage(0);
	for(int i=0;i<num;i++)
	{
		Keypoints.push_back(0);
		Descriptors.push_back(0);
	}
	for(int i=0;i<num-1;i++)
	{
		H.push_back(0);
	}
}

Csurf::Csurf()
{
	ptpairs.clear();
	storage = cvCreateMemStorage(0);
}
Csurf::~Csurf()
{
	ptpairs.clear();
	int n=Keypoints.size();
	for(int i=0;i<n;i++)
	{
		cvClearSeq(Keypoints[i]);
		cvClearSeq(Descriptors[i]);
	}
	Keypoints.clear();
	Descriptors.clear();
	cvReleaseMemStorage(&storage);
}

double Csurf::compareSURFDescriptors( const float* d1, const float* d2, double best, int length )
{
	//计算两个特征描述符的距离，best相当于阈值，当计算的过程中距离大于 beat  的值时即刻返回当前计算的距离值，
	//ength  --- 描述符的维数，即描述符数组长度
	double total_cost = 0;
	assert( length % 4 == 0 );
	for( int i = 0; i < length; i += 4 )
	{
		double t0 = d1[i] - d2[i];
		double t1 = d1[i+1] - d2[i+1];
		double t2 = d1[i+2] - d2[i+2];
		double t3 = d1[i+3] - d2[i+3];
		total_cost += t0*t0 + t1*t1 + t2*t2 + t3*t3;
		if( total_cost > best )
			break;
	}
	return total_cost;
}
int Csurf::naiveNearestNeighbor( const float* vec, int laplacian, const CvSeq* model_keypoints,
	const CvSeq* model_descriptors )
{
	//传入的是要比较的特征描述符合匹配候选模的参数
	int length = (int)(model_descriptors->elem_size/sizeof(float));//特征描述符的维数，其实不是64就是128
	int i, neighbor = -1;
	double d, dist1 = 1e6, dist2 = 1e6;
	//dist1保存为近邻位置，dist2保存时次近邻位置
	//dist为阈值，只要比它大就返回
	CvSeqReader reader, kreader;
	cvStartReadSeq( model_keypoints, &kreader, 0 );
	cvStartReadSeq( model_descriptors, &reader, 0 );

	for( i = 0; i < model_descriptors->total; i++ )
	{
		//将传入的特征向量和候选模型中每一个特征描述符比较
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* mvec = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );

		if( laplacian != kp->laplacian )
			continue;
		// laplacian 值不同时直接pass 不准配对
		d = compareSURFDescriptors( vec, mvec, dist2, length );

		if( d < dist1 )
		{
			dist2 = dist1;
			dist1 = d;
			neighbor = i;
		}
		else if ( d < dist2 )
			dist2 = d;
	}
	if ( dist1 < 0.55*dist2 )
		return neighbor;//返回匹配的序列号
	return -1;
}

int Csurf::naiveNearestNeighbor( const float* vec, int laplacian,const CvSeq* model_keypoints,
	const CvSeq* model_descriptors,vector<double>& dist)
{
	//该函数完成了找到与vec匹配的候选模型中的序列号
	int length = (int)(model_descriptors->elem_size/sizeof(float));
	int i, neighbor = -1;
	double d, dist1 = 1e6, dist2 = 1e6;
	CvSeqReader reader, kreader;
	cvStartReadSeq( model_keypoints, &kreader, 0 );
	cvStartReadSeq( model_descriptors, &reader, 0 );

	for( i = 0; i < model_descriptors->total; i++ )
	{
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* mvec = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		if( laplacian != kp->laplacian )
			continue;
		d = compareSURFDescriptors( vec, mvec, dist2, length );
		if( d < dist1 )
		{
			dist2 = dist1;
			dist1 = d;
			neighbor = i;
		}
		else if ( d < dist2 )
			dist2 = d;
	}
	if (dist1 < 0.55*dist2 )
	{
		dist.push_back (dist1/dist2);
		//这个和上一个函数的不同在于用dist这个容器，保存下来所有匹配对的最近邻与次近邻的比
		return neighbor;
	}
	return -1;
}

void Csurf::findPairs(const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, 
	const CvSeq* imageDescriptors, vector<int>& ptpairs )
{
	//findPairs最后结果就是在ptpairs中object 中特征点和与之匹配特征点的image中序列号对
	CvSeqReader reader, kreader;
	cvStartReadSeq( objectKeypoints, &kreader );
	cvStartReadSeq( objectDescriptors, &reader );
	ptpairs.clear();
	for( int i = 0; i < objectDescriptors->total; i++ )
	{
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* descriptor = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		//上面四句话就是提出了存在序列中指针指向的点，同时指针也会移向下一个
		int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors );
		//nearest_neighbor保存：与object 图像中特征点匹配的候选模型image 中特征点序列号
		//如果匹配成功，那么nearest_neighbor》=0，否则为-1
		if( nearest_neighbor >= 0 )
		{
			ptpairs.push_back(i);
			ptpairs.push_back(nearest_neighbor);
		}
	}
}


void Csurf::findPairs( const CvSeq* objectKeypoints,const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, 
	const CvSeq* imageDescriptors, vector<int>& ptpairs0,vector<int>& ptpairs1 )
{
	//findpairs重载函数，我们已知ptpairs0（object----image）比说：02 14 25 36  47 时候，可以得到ptpairs1
	//ptpairs1那么他就是看看object的24567都是和谁对应的
	for( int i=0;i<ptpairs0.size()/2;i++)
	{
		int i0=ptpairs0[2*i+1];
		const CvSURFPoint* kp = (const CvSURFPoint*)cvGetSeqElem(objectKeypoints,i0); 
		const float* descriptor = (const float*)cvGetSeqElem(objectDescriptors,i0);
		int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors );
		ptpairs1.push_back(i0);
		ptpairs1.push_back(nearest_neighbor);
	}
}
void Csurf::findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints,
	const CvSeq* imageDescriptors, vector<int>& ptpairs,vector<double>& dist)
{//dist保存了每一个匹配对他们最近邻与次近邻之比
	int i;
	vector<double> T;
	CvSeqReader reader, kreader;
	cvStartReadSeq( objectKeypoints, &kreader );
	cvStartReadSeq( objectDescriptors, &reader );
	ptpairs.clear();
	dist.clear ();
	for( i = 0; i < objectDescriptors->total; i++ )
	{
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* descriptor = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors ,dist);
		if( nearest_neighbor >= 0 )
		{
			ptpairs.push_back(i);
			ptpairs.push_back(nearest_neighbor);
		}
	}
}


void Csurf::release_mem( CvPoint2D64f* pts1,CvPoint2D64f* pts2)
{
	free(pts1);
	free(pts2);
}


CvPoint2D32f Csurf::persp_xform_pt0( CvPoint2D32f pt, CvMat* T )
{
	CvMat XY, UV;
	double xy[3] = { pt.x, pt.y, 1.0 }, uv[3] = { 0 };
	CvPoint2D32f rslt;

	cvInitMatHeader( &XY, 3, 1, CV_64FC1, xy, CV_AUTOSTEP );
	cvInitMatHeader( &UV, 3, 1, CV_64FC1, uv, CV_AUTOSTEP );
	cvMatMul( T, &XY, &UV );
	rslt = cvPoint2D32f( uv[0] / uv[2], uv[1] / uv[2] );

	return rslt;
}


CvPoint2D64f Csurf::persp_xform_pt( CvPoint2D64f pt, CvMat* T )
{
	CvMat XY, UV;
	double xy[3] = { pt.x, pt.y, 1.0 }, uv[3] = { 0 };
	CvPoint2D64f rslt;

	cvInitMatHeader( &XY, 3, 1, CV_64FC1, xy, CV_AUTOSTEP );
	cvInitMatHeader( &UV, 3, 1, CV_64FC1, uv, CV_AUTOSTEP );
	cvMatMul( T, &XY, &UV );
	rslt = cvPoint2D64f( uv[0] / uv[2], uv[1] / uv[2] );

	return rslt;
}
double Csurf::homog_xfer_err( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H )
{
	CvPoint2D64f xpt = persp_xform_pt( pt, H );
	double x_diff = xpt.x - mpt.x;
	double y_diff = xpt.y - mpt.y;

	return x_diff * x_diff + y_diff * y_diff;
}


int Csurf::find_consensus( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
	CvMat* M, double err_tol,vector<int>& inliers_ptpairs)
{
	CvPoint2D64f pt, mpt;
	double err;
	int i, in = 0;
	double err_square=err_tol*err_tol;
	inliers_ptpairs.clear();
	if( mtype == 0 )
		for( i = 0; i < (int)ptpairs.size(); i += 2 )
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem( CurrentKeypoints, ptpairs[i] );
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem( PreKeypoints, ptpairs[i+1] );
			pt.x=r1->pt.x;
			pt.y=r1->pt.y;
			mpt.x=r2->pt.x;
			mpt.y=r2->pt.y;
			err = homog_xfer_err( pt, mpt, M );
			if(err<=err_square)
			{
				inliers_ptpairs.push_back(ptpairs[i]);
				inliers_ptpairs.push_back(ptpairs[i+1]);
				in++;
			}
		}
		return in;
}

CvMat* Csurf::lsq_homog(CvPoint2D64f* pts, CvPoint2D64f* mpts, int n )
{
	if(n<4)
		return NULL;
	CvMat* H, * A, * B, X;
	double x[9];
	int i;
	A = cvCreateMat( 2*n, 8, CV_64FC1 );
	B = cvCreateMat( 2*n, 1, CV_64FC1 );
	X = cvMat( 8, 1, CV_64FC1, x );
	H = cvCreateMat(3, 3, CV_64FC1);
	cvZero( A );
	for( i = 0; i < n; i++ )
	{
		cvmSet( A, i, 0, pts[i].x );
		cvmSet( A, i+n, 3, pts[i].x );
		cvmSet( A, i, 1, pts[i].y );
		cvmSet( A, i+n, 4, pts[i].y );
		cvmSet( A, i, 2, 1.0 );
		cvmSet( A, i+n, 5, 1.0 );
		cvmSet( A, i, 6, -pts[i].x * mpts[i].x );
		cvmSet( A, i, 7, -pts[i].y * mpts[i].x );
		cvmSet( A, i+n, 6, -pts[i].x * mpts[i].y );
		cvmSet( A, i+n, 7, -pts[i].y * mpts[i].y );
		cvmSet( B, i, 0, mpts[i].x );
		cvmSet( B, i+n, 0, mpts[i].y );
	}
	cvSolve( A, B, &X, CV_SVD );
	x[8] = 1.0;
	X = cvMat( 3, 3, CV_64FC1, x );
	cvConvert( &X, H );

	cvReleaseMat( &A );
	cvReleaseMat( &B );
	return H;
}


void Csurf::extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts )
{
	CvPoint2D64f* _pts, * _mpts;
	int i,j=0;
	_pts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );
	_mpts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );

	if( mtype==0)
	{
		for(i=0;i<2*m;i+=2)
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem(CurrentKeypoints, ptpairs0[i] );
			_pts[j].x=r1->pt.x;
			_pts[j].y=r1->pt.y;
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem(PreKeypoints, ptpairs0[i+1] );
			_mpts[j].x =r2->pt.x;
			_mpts[j++].y =r2->pt.y;
		}
	}
	*pts = _pts;
	*mpts = _mpts;
}

void Csurf::extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts ,int DX,int DY)
{
	CvPoint2D64f* _pts, * _mpts;
	int i,j=0;
	_pts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );
	_mpts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );

	if( mtype==0)
	{
		for(i=0;i<2*m;i+=2)
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem(CurrentKeypoints, ptpairs0[i] );
			_pts[j].x=r1->pt.x;
			_pts[j].y=r1->pt.y;
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem(PreKeypoints, ptpairs0[i+1] );
			_mpts[j].x =r2->pt.x+DX;
			_mpts[j++].y =r2->pt.y+DY;
		}
	}
	*pts = _pts;
	*mpts = _mpts;
}

void Csurf::extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts,CvMat *H0)
{
	CvPoint2D64f* _pts, * _mpts;
	int i,j=0;
	_pts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );
	_mpts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );

	if( mtype==0)
	{
		for(i=0;i<2*m;i+=2)
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem(CurrentKeypoints, ptpairs0[i] );
			_pts[j].x=r1->pt.x;
			_pts[j].y=r1->pt.y;
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem(PreKeypoints, ptpairs0[i+1] );
			_mpts[j].x =r2->pt.x;
			_mpts[j].y =r2->pt.y;
			_mpts[j]=persp_xform_pt(_mpts[j],H0);
			j++;
		}
	}
	*pts = _pts;
	*mpts = _mpts;
}

void Csurf::draw_ransac_sample(vector<int> ptpairs,vector<int>& sample_ptpairs,unsigned int seed)
{
	int rank[4];
	for(int i=0;i<4;i++)
		rank[i]=-1;
	int j=0;
	int flag;
	srand(seed);   
	sample_ptpairs.clear();
	while(j<4)
	{
		flag=0;
		int k=rand()%(int)ptpairs.size();
		k=k%2 ? k+1:k;
		for(int i=0;i<4;i++)
		{
			if(k==rank[i])
			{
				flag=1;
				break;
			}
		}
		if(flag==0 && k!=((int)ptpairs.size()))
		{
			rank[j]=k;
			j++;
		}
	}
	for(int i=0;i<4;i++)
	{
		int a=rank[i];
		sample_ptpairs.push_back(ptpairs[a]);
		sample_ptpairs.push_back(ptpairs[a+1]);

	}
}


int  Csurf::calc_min_inliers( int n, int m, double p_badsupp, double p_badxform )
{

	if(n>800)
		return n/8;
	double pi, sum;
	int i, j;

	for( j = m+1; j <= n; j++ )
	{
		sum = 0;
		for( i = j; i <= n; i++ )
		{
			pi = pow( p_badsupp, i - m ) * pow( 1.0 - p_badsupp, n - i + m ) *
				gsl_sf_choose( n - m, i - m );
			sum += pi;
		}
		if( sum < p_badxform )
			break;
	}
	return j;
}


CvMat* Csurf:: ransac_xform( vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
	int m, double p_badxform, double err_tol,int DX,int DY)
{
	//在使用ransanc_xform过程中特征点对就已经发生了变化，相对于精匹配
	unsigned int seed;
	CvPoint2D64f* pts, * mpts;
	CvMat* M = NULL;
	CvMat* Max_M= NULL;
	double p, in_frac = 0.25;
	int i, nm, in, in_min, in_max = 0, k = 0;                                       
	nm = (int)ptpairs.size()/2;
	if(nm<4)
		return NULL;
	in_min = calc_min_inliers( nm, m, 0.10, p_badxform );

	p = pow( 1.0 - pow( in_frac, m ), k );
	i = 0;
	vector<int> Temp_ptpairs;
	vector<int> inliers_ptpairs;
	vector<int> sample_ptpairs;
	seed=0;
	while( p > p_badxform )
	{

		draw_ransac_sample( ptpairs,sample_ptpairs,seed);
		seed=seed+1;
		extract_corresp_pts( sample_ptpairs,CurrentKeypoints,PreKeypoints, m, mtype, &pts, &mpts );
		M = lsq_homog(pts,mpts, m );

		if( ! M )
			goto iteration_end;
		in = find_consensus( ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol,Temp_ptpairs);
		if( in > in_max )
		{
			in_max = in;
			in_frac = (double)in_max / nm;
			inliers_ptpairs=Temp_ptpairs;

			Max_M=cvCloneMat(M);
		}
		cvReleaseMat( &M );
iteration_end:
		release_mem( pts, mpts);
		p = pow( 1.0 - pow( in_frac, m ), ++k );
	}


	if( in_max >= in_min )
	{
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in_max, mtype, &pts, &mpts );
		M = lsq_homog( pts, mpts, in_max );
		in = find_consensus(ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol, inliers_ptpairs);
		cvReleaseMat( &M );
		release_mem( pts, mpts );
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in, mtype, &pts, &mpts,DX,DY);
		M = lsq_homog( pts, mpts, in );
		release_mem( pts, mpts );
		ptpairs.clear();
		ptpairs=inliers_ptpairs;//把内点序列存储在ptpairs内
		if (!M)
		{
			Temp_ptpairs.clear();
			inliers_ptpairs.clear();
			sample_ptpairs.clear();
			return NULL;

		}
		else
			Max_M=cvCloneMat(M);	
	}
	else
	{
		if(M)
			cvReleaseMat( &M );
		if(Max_M)
			cvReleaseMat( &Max_M );
		return NULL;
	}

	Temp_ptpairs.clear();
	inliers_ptpairs.clear();
	sample_ptpairs.clear();
	return Max_M;

}

CvMat* Csurf:: ransac_xform( vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
	int m, double p_badxform, double err_tol,CvMat *H0)
{
	unsigned int seed;
	CvPoint2D64f* pts, * mpts;
	CvMat* M = NULL;
	CvMat* Max_M= NULL;
	double p, in_frac = 0.25;
	int i, nm, in, in_min, in_max = 0, k = 0;                                       
	nm = (int)ptpairs.size()/2;
	if(nm<4)
		return NULL;
	in_min = calc_min_inliers( nm, m, 0.10, p_badxform );

	p = pow( 1.0 - pow( in_frac, m ), k );
	i = 0;
	vector<int> Temp_ptpairs;
	vector<int> inliers_ptpairs;
	vector<int> sample_ptpairs;
	seed=0;
	while( p > p_badxform )
	{

		draw_ransac_sample( ptpairs,sample_ptpairs,seed);
		seed=seed+1;
		extract_corresp_pts( sample_ptpairs,CurrentKeypoints,PreKeypoints, m, mtype, &pts, &mpts );
		M = lsq_homog(pts,mpts, m );

		if( ! M )
			goto iteration_end;
		in = find_consensus( ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol,Temp_ptpairs);
		if( in > in_max )
		{
			in_max = in;
			in_frac = (double)in_max / nm;
			inliers_ptpairs=Temp_ptpairs;

			Max_M=cvCloneMat(M);
		}
		cvReleaseMat( &M );
iteration_end:
		release_mem( pts, mpts);
		p = pow( 1.0 - pow( in_frac, m ), ++k );
	}

	if( in_max >= in_min )
	{
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in_max, mtype, &pts, &mpts );
		M = lsq_homog( pts, mpts, in_max );
		in = find_consensus(ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol, inliers_ptpairs);
		cvReleaseMat( &M );
		release_mem( pts, mpts );
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in, mtype, &pts, &mpts,H0);
		M = lsq_homog( pts, mpts, in );
		release_mem( pts, mpts );
		ptpairs.clear();
		ptpairs=inliers_ptpairs;//把内点序列存储在ptpairs内
		if (!M)
		{
			Temp_ptpairs.clear();
			inliers_ptpairs.clear();
			sample_ptpairs.clear();
			return NULL;

		}
		else
			Max_M=cvCloneMat(M);	
	}

	Temp_ptpairs.clear();
	inliers_ptpairs.clear();
	sample_ptpairs.clear();
	return Max_M;

}

CvMat* Csurf::GetH(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int DX,int DY)
{//随机一致性，得到两幅图片之间的转换矩阵

	CvMat* H;
	H = ransac_xform(ptpairs,CurrentKeypoints,PreKeypoints,0, 4, 0.05, 3.0,DX,DY);
	return H;
}

CvMat* Csurf::GetH(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,CvMat *H0 )
{
	CvMat* H;
	H = ransac_xform(ptpairs,CurrentKeypoints,PreKeypoints,0, 4, 0.05, 3.0,H0 );
	return H;
}
CvMat* Csurf::GetM(vector<int> &pt,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int DX,int DY)
{
	CvMat* H=NULL,*M=NULL;;
	CvPoint2D64f *pts=NULL, *mpts=NULL;
	int num=(int)pt.size()/2;
	if(num<4)
		return NULL;
	extract_corresp_pts( pt,CurrentKeypoints,PreKeypoints, num, 0, &pts, &mpts );
	for(int i=0;i<num;i++)
	{
		mpts[i].x +=DX;
		mpts[i].y +=DY;
	}
	M= lsq_homog( pts, mpts, num );
	H=cvCloneMat(M);
	release_mem( pts, mpts);
	cvReleaseMat( &M );

	return H;
}
CvMat* Csurf::GetM(vector<int> &pt,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,CvMat *H0)
{
	CvMat* H=NULL,*M=NULL;;
	CvPoint2D64f *pts=NULL, *mpts=NULL;
	int num=(int)pt.size()/2;
	if(num<4)
		return 0;
	extract_corresp_pts( pt,CurrentKeypoints,PreKeypoints, num, 0, &pts, &mpts );
	for(int i=0;i<num;i++)
	{
		mpts[i]=persp_xform_pt(mpts[i],H0);  
	}
	M= lsq_homog( pts, mpts, num );
	H=cvCloneMat(M);
	release_mem( pts, mpts);
	cvReleaseMat( &M );

	return H;
}

void Csurf::maxfive(vector<double> &d,vector<int> &ptpairs0)
{
	int maxp[5]={-1,-1,-1,-1,-1};
	double maxd[5]={10,10,10,10,10};
	for(int i=0;i<d.size();i++)
	{
		if(d[i]>=maxd[4])
			continue;
		else if((d[i]<maxd[4])&&(d[i]>=maxd[3]))
		{
			maxd[4]=d[i];
			maxp[4]=i;
		}
		else if((d[i]<maxd[3])&&(d[i]>=maxd[2]))
		{
			maxd[4]=maxd[3];
			maxp[4]=maxp[3];
			maxd[3]=d[i];
			maxp[3]=i;
		}
		else if((d[i]<maxd[2])&&(d[i]>=maxd[1]))
		{
			maxd[4]=maxd[3];
			maxp[4]=maxp[3];
			maxd[3]=maxd[2];
			maxp[3]=maxp[2];
			maxd[2]=d[i];
			maxp[2]=i;

		}
		else if((d[i]<maxd[1])&&(d[i]>=maxd[0]))
		{
			maxd[4]=maxd[3];
			maxp[4]=maxp[3];
			maxd[3]=maxd[2];
			maxp[3]=maxp[2];
			maxd[2]=maxd[1];
			maxp[2]=maxp[1];
			maxd[1]=d[i];
			maxp[1]=i;

		}
		else if(d[i]<maxd[0])
		{
			maxd[4]=maxd[3];
			maxp[4]=maxp[3];
			maxd[3]=maxd[2];
			maxp[3]=maxp[2];
			maxd[2]=maxd[1];
			maxp[2]=maxp[1];
			maxd[1]=maxd[0];
			maxp[1]=maxp[0];
			maxd[0]=d[i];
			maxp[0]=i;

		}
	}
	for (int i=0;i<5;i++)
	{
		ptpairs0.push_back (ptpairs[2*maxp[i]]);
		ptpairs0.push_back (ptpairs[2*maxp[i]+1]);

	}
}
void Csurf::gsotransform(const CvSeq* objectKeypoints,const CvSeq* imageKeypoints, vector<int>& ptpairs0,vector<int>& ptpairs1)
{
	float s=0.005,o=0.0005;
	vector<int> temp;
	const CvSURFPoint* ra1 = (const CvSURFPoint*)cvGetSeqElem(objectKeypoints,ptpairs0[0]); 
	const CvSURFPoint* rb1 = (const CvSURFPoint*)cvGetSeqElem(objectKeypoints,ptpairs0[2]); 
	const CvSURFPoint* ra2 = (const CvSURFPoint*)cvGetSeqElem(imageKeypoints,ptpairs0[1]); 
	const CvSURFPoint* rb2 = (const CvSURFPoint*)cvGetSeqElem(imageKeypoints,ptpairs0[3]); 
	CvPoint2D32f Pa1,Pb1, Pa2,Pb2;
	float Dab1,Dab2;
	float a1,b1,c1,a2,b2,c2;
	Pa1=ra1->pt;
	Pb1=rb1->pt;
	Pa2=ra2->pt;
	Pb2=rb2->pt;
	Dab1=sqrt((Pb1.x-Pa1.x)*(Pb1.x-Pa1.x)+(Pb1.y-Pa1.y)*(Pb1.y-Pa1.y));
	Dab2=sqrt((Pb2.x-Pa2.x)*(Pb2.x-Pa2.x)+(Pb2.y-Pa2.y)*(Pb2.y-Pa2.y));
	a1=(Pb1.x-Pa1.x);
	b1=(Pb1.y-Pa1.y);
	c1=Pa1.y*Pb1.x-Pb1.y*Pa1.x;
	a2=(Pb2.x-Pa2.x);
	b2=(Pb2.y-Pa2.y);
	c2=Pa2.y*Pb2.x-Pb2.y*Pa2.x;
	for(int i=0;i<4;i++)
	{
		temp.push_back(ptpairs0[i]);
	}
	for(int i=0;i<ptpairs1.size()/2;i++)
	{
		const CvSURFPoint* rc1 = (const CvSURFPoint*)cvGetSeqElem(objectKeypoints,ptpairs1[2*i]); 
		const CvSURFPoint* rc2 = (const CvSURFPoint*)cvGetSeqElem(imageKeypoints,ptpairs1[2*i+1]); 
		CvPoint2D32f Pc1,Pc2;
		float Dac1,Dbc1, Dac2,Dbc2;
		float Ky1,Kx1,Ky2,Kx2;
		Pc1=rc1->pt;
		Pc2=rc2->pt;
		Dac1=sqrt((Pc1.x-Pa1.x)*(Pc1.x-Pa1.x)+(Pc1.y-Pa1.y)*(Pc1.y-Pa1.y));
		Dbc1=sqrt((Pc1.x-Pb1.x)*(Pc1.x-Pb1.x)+(Pc1.y-Pb1.y)*(Pc1.y-Pb1.y));
		Dac2=sqrt((Pc2.x-Pa2.x)*(Pc2.x-Pa2.x)+(Pc2.y-Pa2.y)*(Pc2.y-Pa2.y));
		Dbc2=sqrt((Pc2.x-Pb2.x)*(Pc2.x-Pb2.x)+(Pc2.y-Pb2.y)*(Pc2.y-Pb2.y));
		Ky1=a1*Pc1.y;
		Kx1=b1*Pc1.x+c1;
		Ky2=a1*Pc2.y;
		Kx2=b2*Pc2.x+c2;
		if(Ky1==Kx1)
		{
			if(((Pc1.x!=Pa1.x)||(Pc1.y!=Pa1.y))&&((Pc1.x!=Pb1.x)||(Pc1.y!=Pb1.y)))
			{
				if((Dac1/Dbc1-Dac2/Dbc2)*(Dac1/Dbc1-Dac2/Dbc2)<s)
				{
					float pa1=((Pb1.x-Pa1.x)*(Pc1.x-Pa1.x)+(Pb1.y-Pa1.y)*(Pc1.y-Pa1.y))/(Dab1*Dac1);
					float oa1=acos(pa1);
					float pa2=((Pb2.x-Pa2.x)*(Pc2.x-Pa2.x)+(Pb2.y-Pa2.y)*(Pc2.y-Pa2.y))/(Dab2*Dac2);
					float oa2=acos(pa2);
					float oa=oa1-oa2;
					float pb1=((Pa1.x-Pb1.x)*(Pc1.x-Pb1.x)+(Pa1.y-Pb1.y)*(Pc1.y-Pb1.y))/(Dab1*Dbc1);
					float ob1=acos(pb1);
					float pb2=((Pa2.x-Pb2.x)*(Pc2.x-Pb2.x)+(Pa2.y-Pb2.y)*(Pc2.y-Pb2.y))/(Dab2*Dbc2);
					float ob2=acos(pb2);
					float ob=ob1-ob2;
					if((oa*oa<o)&&(ob*ob<o))
					{
						temp.push_back(ptpairs1[2*i]);
						temp.push_back(ptpairs1[2*i+1]);
					}
				}

			}

		}
		else if(Ky1>Kx1)
		{
			if(Ky2>Kx2)
			{
				if((Dac1/Dbc1-Dac2/Dbc2)*(Dac1/Dbc1-Dac2/Dbc2)<s)
				{
					float pa1=((Pb1.x-Pa1.x)*(Pc1.x-Pa1.x)+(Pb1.y-Pa1.y)*(Pc1.y-Pa1.y))/(Dab1*Dac1);
					float oa1=acos(pa1);
					float pa2=((Pb2.x-Pa2.x)*(Pc2.x-Pa2.x)+(Pb2.y-Pa2.y)*(Pc2.y-Pa2.y))/(Dab2*Dac2);
					float oa2=acos(pa2);
					float oa=oa1-oa2;
					float pb1=((Pa1.x-Pb1.x)*(Pc1.x-Pb1.x)+(Pa1.y-Pb1.y)*(Pc1.y-Pb1.y))/(Dab1*Dbc1);
					float ob1=acos(pb1);
					float pb2=((Pa2.x-Pb2.x)*(Pc2.x-Pb2.x)+(Pa2.y-Pb2.y)*(Pc2.y-Pb2.y))/(Dab2*Dbc2);
					float ob2=acos(pb2);
					float ob=ob1-ob2;
					if((oa*oa<o)&&(ob*ob<o))
					{
						temp.push_back(ptpairs1[2*i]);
						temp.push_back(ptpairs1[2*i+1]);
					}
				}

			}
		}
		else
		{
			if(Ky2<Kx2)
			{
				if((Dac1/Dbc1-Dac2/Dbc2)*(Dac1/Dbc1-Dac2/Dbc2)<s)
				{
					float pa1=((Pb1.x-Pa1.x)*(Pc1.x-Pa1.x)+(Pb1.y-Pa1.y)*(Pc1.y-Pa1.y))/(Dab1*Dac1);
					float oa1=acos(pa1);
					float pa2=((Pb2.x-Pa2.x)*(Pc2.x-Pa2.x)+(Pb2.y-Pa2.y)*(Pc2.y-Pa2.y))/(Dab2*Dac2);
					float oa2=acos(pa2);
					float oa=oa1-oa2;
					float pb1=((Pa1.x-Pb1.x)*(Pc1.x-Pb1.x)+(Pa1.y-Pb1.y)*(Pc1.y-Pb1.y))/(Dab1*Dbc1);
					float ob1=acos(pb1);
					float pb2=((Pa2.x-Pb2.x)*(Pc2.x-Pb2.x)+(Pa2.y-Pb2.y)*(Pc2.y-Pb2.y))/(Dab2*Dbc2);
					float ob2=acos(pb2);
					float ob=ob1-ob2;
					if((oa*oa<o)&&(ob*ob<o))
					{
						temp.push_back(ptpairs1[2*i]);
						temp.push_back(ptpairs1[2*i+1]);
					}
				}

			}
		}

	}

	ptpairs1.clear();
	for(int i=0;i<temp.size();i++)
	{
		ptpairs1.push_back(temp[i]);
	}
}

double Csurf::GetRMSE(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H,int DX,int DY)
{
	double rmse=0.0;
	int m=ptpairs.size()/2;
	CvSURFPoint r1;
	CvSURFPoint r2;

	for(int i=0;i<m;i++)
	{
		r1.pt=((CvSURFPoint*)cvGetSeqElem( CurrentKeypoints, ptpairs[i*2] ))->pt;
		r2.pt=((CvSURFPoint*)cvGetSeqElem( PreKeypoints, ptpairs[i*2+1] ))->pt;
		r1.pt=persp_xform_pt0(r1.pt,H);//点构造一个矩阵，与H相乘，然后结果矩阵中0/1，1/2作为点返回
		rmse+=sqrt((r1.pt.x-r2.pt.x-DX)*(r1.pt.x-r2.pt.x-DX)+(r1.pt.y-r2.pt.y-DY)*(r1.pt.y-r2.pt.y-DY));

	}
	rmse=rmse/m;//是不是返回是匹配点对的平均误差
	return rmse;
}


CvMat* Csurf::  GetH(vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int &innernum)
{
	CvMat* H;

	H = ransac_xform( ptpairs,CurrentKeypoints,PreKeypoints, 0, 4, 0.01, 3,innernum);

	return H;
}

CvMat*  Csurf:: ransac_xform( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, int m, double p_badxform, double err_tol,int &innernum)
{
	CvPoint2D64f* pts, * mpts;
	CvMat* M = NULL;
	CvMat* Max_M= NULL;
	//gsl_rng* rng;
	double p, in_frac = 0.25;
	int i, nm, in, in_min, in_max = 0, k = 0;//n是number of features in feat
	//m是minimum number of correspondences necessary to instantiate the  model computed by xform_fn
	nm = (int)ptpairs.size()/2;
	if( nm < m )
	{
		fprintf( stderr, "Warning: not enough matches to compute xform, %s" \
			" line %d\n", __FILE__, __LINE__ );
		return NULL;
	}

	/* initialize random number generator */

	//rng = gsl_rng_alloc( gsl_rng_mt19937 );
	//gsl_rng_set( rng, time(NULL) );

	in_min = calc_min_inliers( nm, m, 0.1, p_badxform );
	//printf("符合这一要求的内点至少得有  : %d\n", in_min);

	p = pow( 1.0 - pow( in_frac, m ), k );
	i = 0;
	vector<int> Temp_ptpairs;
	vector<int> inliers_ptpairs;
	vector<int> sample_ptpairs;
	while( p > p_badxform )
	{
		draw_ransac_sample( ptpairs,sample_ptpairs);
		extract_corresp_pts( sample_ptpairs,CurrentKeypoints,PreKeypoints, m, mtype, &pts, &mpts );
		M = lsq_homog(pts,mpts, m );

		if( ! M )
			goto iteration_end;
		in = find_consensus( ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol,Temp_ptpairs);
		if( in > in_max )
		{
			in_max = in;
			in_frac = (double)in_max / nm;
			inliers_ptpairs=Temp_ptpairs;

			Max_M=cvCloneMat(M);
		}
		cvReleaseMat( &M );

iteration_end:
		release_mem( pts, mpts);
		p = pow( 1.0 - pow( in_frac, m ), ++k );
	}

	/* calculate final transform based on best consensus set */

	if( in_max >= in_min )
	{
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in_max, mtype, &pts, &mpts );
		M = lsq_homog( pts, mpts, in_max );
		//printf("RANSAC  in_max : %d\n", in_max);

		in = find_consensus(ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol, inliers_ptpairs);
		cvReleaseMat( &M );
		release_mem( pts, mpts );
		extract_corresp_pts( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in, mtype, &pts, &mpts );
		// printf("RANSAC : %d\n", in);

		M = lsq_homog( pts, mpts, in );
		printf("精确匹配对数: %d\n", in);

		release_mem( pts, mpts );
	}
	else
		printf("精确匹配对数: %d\n", in);
	innernum=in;

	//gsl_rng_free( rng );
	//return Max_M;
	return M;
}

void Csurf:: draw_ransac_sample( vector<int> ptpairs,vector<int>& sample_ptpairs)
{
	int rank[4];
	for(int i=0;i<4;i++)
		rank[i]=-1;
	int j=0;
	int flag;
	//	srand((unsigned)time(NULL));   
	sample_ptpairs.clear();
	while(j<4)
	{
		flag=0;
		int k=rand()%(int)ptpairs.size();
		k=k%2 ? k+1:k;
		for(int i=0;i<4;i++)
		{
			if(k==rank[i])
			{
				flag=1;
				break;
			}
		}
		if(flag==0 && k!=((int)ptpairs.size()))
		{
			rank[j]=k;
			j++;
		}
	}
	for(int i=0;i<4;i++)
	{
		int a=rank[i];
		sample_ptpairs.push_back(ptpairs[a]);
		sample_ptpairs.push_back(ptpairs[a+1]);

	}

}


