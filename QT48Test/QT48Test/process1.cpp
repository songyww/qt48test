#pragma  once 
#include <iostream>
#include <io.h>
#include <fstream>
//#include "stdafx.h"
#include "process1.h"
#include <string>
//#include <vector>
#include "ximage.h"
//#include "fftw3.h"
#include "surf.h"
#include<qstring.h>
#include<qfile.h>
#include <qdir.h>
#include<qimage.h>

using namespace std;

#define  pi1 3.1415926
#define SQRT_2 1.4142136f
#define RANSAC_PROB_BAD_SUPP 0.10
extern vector<double> xishu;
extern vector<QString> lujing;
extern double	m_ColorPow;
extern double	m_CuvePow;
extern double	m_ShapePow;
#define min1(a,b)            (((a) < (b)) ? (a) : (b))
#define max1(a,b)            (((a) > (b)) ? (a) : (b))
int m_KeyMainColorSig[111]; // 查询小图像的特征
double m_KeyCuve[15];
double m_KeyShape[8];
int m_Color[111];//检索图像特征
double m_Cuve[15],m_Shape[8];

extern double ColorPow;
extern double CuvePow;
extern double ShapePow;
/*************************用于ondraw************************/
RGBQUAD VgaDefPal[256] = {
	{0x00,0x00,0x00,0x00},{0xa8,0x00,0x00,0x00},{0x00,0xa8,0x00,0x00},{0xa8,0xa8,0x00,0x00},
	{0x00,0x00,0xa8,0x00},{0xa8,0x00,0xa8,0x00},{0x00,0x54,0xa8,0x00},{0xa8,0xa8,0xa8,0x00},
	{0x54,0x54,0x54,0x00},{0xfc,0x54,0x54,0x00},{0x54,0xfc,0x54,0x00},{0xfc,0xfc,0x54,0x00},
	{0x54,0x54,0xfc,0x00},{0xfc,0x54,0xfc,0x00},{0x54,0xfc,0xfc,0x00},{0xfc,0xfc,0xfc,0x00},
	{0x00,0x00,0x00,0x00},{0x14,0x14,0x14,0x00},{0x20,0x20,0x20,0x00},{0x2c,0x2c,0x2c,0x00},
	{0x38,0x38,0x38,0x00},{0x44,0x44,0x44,0x00},{0x50,0x50,0x50,0x00},{0x60,0x60,0x60,0x00},
	{0x70,0x70,0x70,0x00},{0x80,0x80,0x80,0x00},{0x90,0x90,0x90,0x00},{0xa0,0xa0,0xa0,0x00},
	{0xb4,0xb4,0xb4,0x00},{0xc8,0xc8,0xc8,0x00},{0xe0,0xe0,0xe0,0x00},{0xfc,0xfc,0xfc,0x00},
	{0xfc,0x00,0x00,0x00},{0xfc,0x00,0x40,0x00},{0xfc,0x00,0x7c,0x00},{0xfc,0x00,0xbc,0x00},
	{0xfc,0x00,0xfc,0x00},{0xbc,0x00,0xfc,0x00},{0x7c,0x00,0xfc,0x00},{0x40,0x00,0xfc,0x00},
	{0x00,0x00,0xfc,0x00},{0x00,0x40,0xfc,0x00},{0x00,0x7c,0xfc,0x00},{0x00,0xbc,0xfc,0x00},
	{0x00,0xfc,0xfc,0x00},{0x00,0xfc,0xbc,0x00},{0x00,0xfc,0x7c,0x00},{0x00,0xfc,0x40,0x00},
	{0x00,0xfc,0x00,0x00},{0x40,0xfc,0x00,0x00},{0x7c,0xfc,0x00,0x00},{0xbc,0xfc,0x00,0x00},
	{0xfc,0xfc,0x00,0x00},{0xfc,0xbc,0x00,0x00},{0xfc,0x7c,0x00,0x00},{0xfc,0x40,0x00,0x00},
	{0xfc,0x7c,0x7c,0x00},{0xfc,0x7c,0x9c,0x00},{0xfc,0x7c,0xbc,0x00},{0xfc,0x7c,0xdc,0x00},
	{0xfc,0x7c,0xfc,0x00},{0xdc,0x7c,0xfc,0x00},{0xbc,0x7c,0xfc,0x00},{0x9c,0x7c,0xfc,0x00},
	{0x7c,0x7c,0xfc,0x00},{0x7c,0x9c,0xfc,0x00},{0x7c,0xbc,0xfc,0x00},{0x7c,0xdc,0xfc,0x00},
	{0x7c,0xfc,0xfc,0x00},{0x7c,0xfc,0xdc,0x00},{0x7c,0xfc,0xbc,0x00},{0x7c,0xfc,0x9c,0x00},
	{0x7c,0xfc,0x7c,0x00},{0x9c,0xfc,0x7c,0x00},{0xbc,0xfc,0x7c,0x00},{0xdc,0xfc,0x7c,0x00},
	{0xfc,0xfc,0x7c,0x00},{0xfc,0xdc,0x7c,0x00},{0xfc,0xbc,0x7c,0x00},{0xfc,0x9c,0x7c,0x00},
	{0xfc,0xb4,0xb4,0x00},{0xfc,0xb4,0xc4,0x00},{0xfc,0xb4,0xd8,0x00},{0xfc,0xb4,0xe8,0x00},
	{0xfc,0xb4,0xfc,0x00},{0xe8,0xb4,0xfc,0x00},{0xd8,0xb4,0xfc,0x00},{0xc4,0xb4,0xfc,0x00},
	{0xb4,0xb4,0xfc,0x00},{0xb4,0xc4,0xfc,0x00},{0xb4,0xd8,0xfc,0x00},{0xb4,0xe8,0xfc,0x00},
	{0xb4,0xfc,0xfc,0x00},{0xb4,0xfc,0xe8,0x00},{0xb4,0xfc,0xd8,0x00},{0xb4,0xfc,0xc4,0x00},
	{0xb4,0xfc,0xb4,0x00},{0xc4,0xfc,0xb4,0x00},{0xd8,0xfc,0xb4,0x00},{0xe8,0xfc,0xb4,0x00},
	{0xfc,0xfc,0xb4,0x00},{0xfc,0xe8,0xb4,0x00},{0xfc,0xd8,0xb4,0x00},{0xfc,0xc4,0xb4,0x00},
	{0x70,0x00,0x00,0x00},{0x70,0x00,0x1c,0x00},{0x70,0x00,0x38,0x00},{0x70,0x00,0x54,0x00},
	{0x70,0x00,0x70,0x00},{0x54,0x00,0x70,0x00},{0x38,0x00,0x70,0x00},{0x1c,0x00,0x70,0x00},
	{0x00,0x00,0x70,0x00},{0x00,0x1c,0x70,0x00},{0x00,0x38,0x70,0x00},{0x00,0x54,0x70,0x00},
	{0x00,0x70,0x70,0x00},{0x00,0x70,0x54,0x00},{0x00,0x70,0x38,0x00},{0x00,0x70,0x1c,0x00},
	{0x00,0x70,0x00,0x00},{0x1c,0x70,0x00,0x00},{0x38,0x70,0x00,0x00},{0x54,0x70,0x00,0x00},
	{0x70,0x70,0x00,0x00},{0x70,0x54,0x00,0x00},{0x70,0x38,0x00,0x00},{0x70,0x1c,0x00,0x00},
	{0x70,0x38,0x38,0x00},{0x70,0x38,0x44,0x00},{0x70,0x38,0x54,0x00},{0x70,0x38,0x60,0x00},
	{0x70,0x38,0x70,0x00},{0x60,0x38,0x70,0x00},{0x54,0x38,0x70,0x00},{0x44,0x38,0x70,0x00},
	{0x38,0x38,0x70,0x00},{0x38,0x44,0x70,0x00},{0x38,0x54,0x70,0x00},{0x38,0x60,0x70,0x00},
	{0x38,0x70,0x70,0x00},{0x38,0x70,0x60,0x00},{0x38,0x70,0x54,0x00},{0x38,0x70,0x44,0x00},
	{0x38,0x70,0x38,0x00},{0x44,0x70,0x38,0x00},{0x54,0x70,0x38,0x00},{0x60,0x70,0x38,0x00},
	{0x70,0x70,0x38,0x00},{0x70,0x60,0x38,0x00},{0x70,0x54,0x38,0x00},{0x70,0x44,0x38,0x00},
	{0x70,0x50,0x50,0x00},{0x70,0x50,0x58,0x00},{0x70,0x50,0x60,0x00},{0x70,0x50,0x68,0x00},
	{0x70,0x50,0x70,0x00},{0x68,0x50,0x70,0x00},{0x60,0x50,0x70,0x00},{0x58,0x50,0x70,0x00},
	{0x50,0x50,0x70,0x00},{0x50,0x58,0x70,0x00},{0x50,0x60,0x70,0x00},{0x50,0x68,0x70,0x00},
	{0x50,0x70,0x70,0x00},{0x50,0x70,0x68,0x00},{0x50,0x70,0x60,0x00},{0x50,0x70,0x58,0x00},
	{0x50,0x70,0x50,0x00},{0x58,0x70,0x50,0x00},{0x60,0x70,0x50,0x00},{0x68,0x70,0x50,0x00},
	{0x70,0x70,0x50,0x00},{0x70,0x68,0x50,0x00},{0x70,0x60,0x50,0x00},{0x70,0x58,0x50,0x00},
	{0x40,0x00,0x00,0x00},{0x40,0x00,0x10,0x00},{0x40,0x00,0x20,0x00},{0x40,0x00,0x30,0x00},
	{0x40,0x00,0x40,0x00},{0x30,0x00,0x40,0x00},{0x20,0x00,0x40,0x00},{0x10,0x00,0x40,0x00},
	{0x00,0x00,0x40,0x00},{0x00,0x10,0x40,0x00},{0x00,0x20,0x40,0x00},{0x00,0x30,0x40,0x00},
	{0x00,0x40,0x40,0x00},{0x00,0x40,0x30,0x00},{0x00,0x40,0x20,0x00},{0x00,0x40,0x10,0x00},
	{0x00,0x40,0x00,0x00},{0x10,0x40,0x00,0x00},{0x20,0x40,0x00,0x00},{0x30,0x40,0x00,0x00},
	{0x40,0x40,0x00,0x00},{0x40,0x30,0x00,0x00},{0x40,0x20,0x00,0x00},{0x40,0x10,0x00,0x00},
	{0x40,0x20,0x20,0x00},{0x40,0x20,0x28,0x00},{0x40,0x20,0x30,0x00},{0x40,0x20,0x38,0x00},
	{0x40,0x20,0x40,0x00},{0x38,0x20,0x40,0x00},{0x30,0x20,0x40,0x00},{0x28,0x20,0x40,0x00},
	{0x20,0x20,0x40,0x00},{0x20,0x28,0x40,0x00},{0x20,0x30,0x40,0x00},{0x20,0x38,0x40,0x00},
	{0x20,0x40,0x40,0x00},{0x20,0x40,0x38,0x00},{0x20,0x40,0x30,0x00},{0x20,0x40,0x28,0x00},
	{0x20,0x40,0x20,0x00},{0x28,0x40,0x20,0x00},{0x30,0x40,0x20,0x00},{0x38,0x40,0x20,0x00},
	{0x40,0x40,0x20,0x00},{0x40,0x38,0x20,0x00},{0x40,0x30,0x20,0x00},{0x40,0x28,0x20,0x00},
	{0x40,0x2c,0x2c,0x00},{0x40,0x2c,0x30,0x00},{0x40,0x2c,0x34,0x00},{0x40,0x2c,0x3c,0x00},
	{0x40,0x2c,0x40,0x00},{0x3c,0x2c,0x40,0x00},{0x34,0x2c,0x40,0x00},{0x30,0x2c,0x40,0x00},
	{0x2c,0x2c,0x40,0x00},{0x2c,0x30,0x40,0x00},{0x2c,0x34,0x40,0x00},{0x2c,0x3c,0x40,0x00},
	{0x2c,0x40,0x40,0x00},{0x2c,0x40,0x3c,0x00},{0x2c,0x40,0x34,0x00},{0x2c,0x40,0x30,0x00},
	{0x2c,0x40,0x2c,0x00},{0x30,0x40,0x2c,0x00},{0x34,0x40,0x2c,0x00},{0x3c,0x40,0x2c,0x00},
	{0x40,0x40,0x2c,0x00},{0x40,0x3c,0x2c,0x00},{0x40,0x34,0x2c,0x00},{0x40,0x30,0x2c,0x00},
	{0xa8,0xa8,0xa8,0x00},{0x54,0xfc,0xfc,0x00},{0xfc,0x54,0xfc,0x00},{0xfc,0xfc,0x54,0x00},
	{0xfc,0x54,0x54,0x00},{0x54,0xfc,0x54,0x00},{0x54,0x54,0xfc,0x00},{0xfc,0xfc,0xfc,0x00}  
};

RGBQUAD  VgaColorTab[256];

LPBITMAPINFO  CtreateMapInfo(IplImage* workImg, int flag)
{                                           //  建立位图信息
	BITMAPINFOHEADER BIH={40,1,1,1,8,0,0,0,0,0,0};
	LPBITMAPINFO lpBmi;
	int          wid, hei, bits, colors,i;
	RGBQUAD  ColorTab[256];

	wid =workImg->width;
	hei =workImg->height;
	bits=workImg->depth*workImg->nChannels;
	if (bits>8) colors=0;
	else colors=1<<bits;
	lpBmi=(LPBITMAPINFO) malloc(40+4*colors);
	BIH.biWidth   =wid;
	BIH.biHeight  =hei;
	BIH.biBitCount=(BYTE) bits;
	memcpy(lpBmi,&BIH,40);               //  复制位图信息头
	if (bits==8) {                          //  256 色位图
		if (flag==1) {                       //  设置灰阶调色板
			for (i=0;i<256;i++) {
				ColorTab[i].rgbRed=ColorTab[i].rgbGreen=ColorTab[i].rgbBlue=(BYTE) i;
			}
			memcpy(lpBmi->bmiColors, ColorTab, 1024);
		}
		else if (flag==2) {                   //  设置默认调色板
			memcpy(lpBmi->bmiColors, VgaDefPal, 1024);
		}
	}
	return(lpBmi);
}

int  imageClone(IplImage* pi, IplImage** ppo)    //  复制 IplImage 位图 (OpenCV)
{
	if (*ppo)
		cvReleaseImage(ppo);                  //  释放原来位图
	(*ppo) = cvCloneImage(pi);                  //  复制新位图
	return(1);
}

IplImage* convert_to_gray8( IplImage* img )
{
	IplImage* gray8;

	gray8 = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 );
	cvCvtColor( img, gray8, CV_RGB2GRAY );

	return gray8;
}

int  calc_min_inliers2( int n, int m, double p_badsupp, double p_badxform )
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

void draw_ransac_sample2( vector<int> ptpairs,vector<int>& sample_ptpairs)
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

void extract_corresp_pts2( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
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

void extract_corresp_pts2( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
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

CvMat* lsq_homog2(CvPoint2D64f* pts, CvPoint2D64f* mpts, int n )
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

CvPoint2D64f persp_xform_pt2( CvPoint2D64f pt, CvMat* T )
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

double homog_xfer_err2( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H )
{
	CvPoint2D64f xpt = persp_xform_pt2( pt, H );
	double x_diff = xpt.x - mpt.x;
	double y_diff = xpt.y - mpt.y;

	return x_diff * x_diff + y_diff * y_diff;
}

int find_consensus2( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
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
			err = homog_xfer_err2( pt, mpt, M );
			if(err<=err_square)
			{
				inliers_ptpairs.push_back(ptpairs[i]);
				inliers_ptpairs.push_back(ptpairs[i+1]);
				in++;
			}
		}
		return in;
}

void release_mem2( CvPoint2D64f* pts1,CvPoint2D64f* pts2)
{
	free(pts1);
	free(pts2);
}

/////////////////////////////
static	CvMat* ransac_xform2( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, 
	int mtype, int m, double p_badxform, double err_tol,int &innernum)
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
		//fprintf( stderr, "Warning: not enough matches to compute xform, %s" \
		//	" line %d\n", __FILE__, __LINE__ );
		return NULL;
	}

	in_min = calc_min_inliers2( nm, m, 0.1, p_badxform );

	p = pow( 1.0 - pow( in_frac, m ), k );
	i = 0;
	vector<int> Temp_ptpairs;
	vector<int> inliers_ptpairs;
	vector<int> sample_ptpairs;
	while( p > p_badxform )
	{
		draw_ransac_sample2( ptpairs,sample_ptpairs);
		extract_corresp_pts2( sample_ptpairs,CurrentKeypoints,PreKeypoints, m, mtype, &pts, &mpts );
		M = lsq_homog2(pts,mpts, m );

		if( ! M )
			goto iteration_end;
		in = find_consensus2( ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol,Temp_ptpairs);
		if( in > in_max )
		{
			in_max = in;
			in_frac = (double)in_max / nm;
			inliers_ptpairs=Temp_ptpairs;

			Max_M=cvCloneMat(M);
		}
		cvReleaseMat( &M );

iteration_end:

		free(pts);
		free(mpts);
		p = pow( 1.0 - pow( in_frac, m ), ++k );
	}

	/* calculate final transform based on best consensus set */

	if( in_max >= in_min )
	{
		extract_corresp_pts2( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in_max, mtype, &pts, &mpts );
		M = lsq_homog2( pts, mpts, in_max );

		in = find_consensus2(ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol, inliers_ptpairs);
		cvReleaseMat( &M );
		free(pts);
		free(mpts);
		extract_corresp_pts2( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in, mtype, &pts, &mpts );

		M = lsq_homog2( pts, mpts, in );
		//printf("精确匹配对数: %d\n", in);
		free(pts);
		free(mpts);
	}
	//else
	//	printf("精确匹配对数: %d\n", in);
	innernum=in;
	return M;
}
CvMat* GetH2(vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int &innernum)
{
	CvMat* H;
	H = ransac_xform2( ptpairs,CurrentKeypoints,PreKeypoints, 0, 4, 0.05, 3.0,innernum);
	return H;
}

CvPoint2D32f persp_xform_pt2( CvPoint2D32f pt, CvMat* T )
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
double GetRMSE2(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H)
{
	double rmse=0.0;
	int m=ptpairs.size()/2;
	CvSURFPoint r1;
	CvSURFPoint r2;

	for(int i=0;i<m;i++)
	{
		r1.pt=((CvSURFPoint*)cvGetSeqElem( CurrentKeypoints, ptpairs[i*2] ))->pt;
		r2.pt=((CvSURFPoint*)cvGetSeqElem( PreKeypoints, ptpairs[i*2+1] ))->pt;
		r1.pt=persp_xform_pt2(r1.pt,H);
		rmse+=sqrt((r1.pt.x-r2.pt.x)*(r1.pt.x-r2.pt.x)+(r1.pt.y-r2.pt.y)*(r1.pt.y-r2.pt.y));

	}
	rmse=rmse/m;
	ptpairs.clear();
	return rmse;
}

double compareSURFDescriptors3( const float* d1, const float* d2, double best, int length )
{
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

int naiveNearestNeighbor3( const float* vec, int laplacian,
	const CvSeq* model_keypoints,
	const CvSeq* model_descriptors )
{
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
		d = compareSURFDescriptors3( vec, mvec, dist2, length );
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
		return neighbor;
	return -1;
}

void findPairs3( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
	const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs )
{
	int i;
	CvSeqReader reader, kreader;
	cvStartReadSeq( objectKeypoints, &kreader );
	cvStartReadSeq( objectDescriptors, &reader );
	ptpairs.clear();

	for( i = 0; i < objectDescriptors->total; i++ )
	{
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* descriptor = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		int nearest_neighbor = naiveNearestNeighbor3( descriptor, kp->laplacian, imageKeypoints, imageDescriptors );
		if( nearest_neighbor >= 0 )
		{
			ptpairs.push_back(i);
			ptpairs.push_back(nearest_neighbor);
		}
	}
}

CvPoint2D32f persp_xform_pt3( CvPoint2D32f pt, CvMat* T )
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
double GetRMSE3(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H)
{
	double rmse=0.0;
	int m=ptpairs.size()/2;
	CvSURFPoint r1;
	CvSURFPoint r2;

	for(int i=0;i<m;i++)
	{
		r1.pt=((CvSURFPoint*)cvGetSeqElem( CurrentKeypoints, ptpairs[i*2] ))->pt;
		r2.pt=((CvSURFPoint*)cvGetSeqElem( PreKeypoints, ptpairs[i*2+1] ))->pt;
		r1.pt=persp_xform_pt3(r1.pt,H);
		rmse+=sqrt((r1.pt.x-r2.pt.x)*(r1.pt.x-r2.pt.x)+(r1.pt.y-r2.pt.y)*(r1.pt.y-r2.pt.y));

	}
	rmse=rmse/m;
	ptpairs.clear();
	return rmse;
}

static CvMat* lsq_homog3( CvPoint2D64f* pts, CvPoint2D64f* mpts, int n )
{
	CvMat* H, * A, * B, X;
	double x[9];
	int i;

	if( n < 4 )
	{
		fprintf( stderr, "Warning: too few points in lsq_homog(), %s line %d\n",
			__FILE__, __LINE__ );
		return NULL;
	}


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

double gsl_sf_choose3(unsigned int n, unsigned int m)
{
	unsigned long n1,m1,mfei;
	n1=m1=mfei=1;

	if(n=0)
		n1=1;

	if(m=0)
		return 0;
	else if(m==1)
		return n;
	else
	{
		int mfei=n-m;
		if(m<mfei)
		{
			for(int p=n;p>mfei;p--)
				n1*=p;
			for(int p=m;p>0;p--)
				m1*=p;
		}
		else
		{
			for(int p=n;p>m;p--)
				n1*=p;
			for(int p=mfei;p>0;p--)
				m1*=p;
		}
	}

	double k=n1/m1;
	return k;
}
static int calc_min_inliers3( int n, int m, double p_badsupp, double p_badxform )
{
	double pi, sum;
	int i, j;

	for( j = m+1; j <= n; j++ )
	{
		sum = 0;
		for( i = j; i <= n; i++ )
		{
			pi = pow( p_badsupp, i - m ) * pow( 1.0 - p_badsupp, n - i + m ) *
				gsl_sf_choose3( n - m, i - m );
			sum += pi;
		}
		if( sum < p_badxform )
			break;
	}
	return j;
}

static	void draw_ransac_sample3( vector<int> ptpairs,vector<int>& sample_ptpairs)
{
	int rank[4];
	for(int i=0;i<4;i++)
		rank[i]=-1;
	int j=0;
	int flag;

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

static void extract_corresp_pts3( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts )
{
	CvPoint2D64f* _pts, * _mpts;
	int i,j=0;
	_pts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );
	_mpts = (struct CvPoint2D64f *)calloc( m, sizeof( CvPoint2D64f ) );

	if( mtype == FEATURE_FWD_MATCH )
	{
		for(i=0;i<2*m;i+=2)
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem(CurrentKeypoints, ptpairs[i] );
			_pts[j].x=(r1->pt.x);
			_pts[j].y=(r1->pt.y);
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem(PreKeypoints, ptpairs[i+1] );
			_mpts[j].x =(r2->pt.x);
			_mpts[j++].y =(r2->pt.y);
		}
	}
	*pts = _pts;
	*mpts = _mpts;
}

static	CvPoint2D64f persp_xform_pt4( CvPoint2D64f pt, CvMat* T )
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

static	double homog_xfer_err3( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H )
{
	CvPoint2D64f xpt = persp_xform_pt4( pt, H );
	double x_diff = xpt.x - mpt.x;
	double y_diff = xpt.y - mpt.y;

	return x_diff * x_diff + y_diff * y_diff;
}

static int find_consensus3( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
	CvMat* M, double err_tol,vector<int>& inliers_ptpairs)
{
	CvPoint2D64f pt, mpt;
	double err;
	int i, in = 0;
	double err_square=err_tol*err_tol;
	inliers_ptpairs.clear();
	if( mtype == FEATURE_FWD_MATCH )
		for( i = 0; i < (int)ptpairs.size(); i += 2 )
		{
			CvSURFPoint* r1 = (CvSURFPoint*)cvGetSeqElem( CurrentKeypoints, ptpairs[i] );
			CvSURFPoint* r2 = (CvSURFPoint*)cvGetSeqElem( PreKeypoints, ptpairs[i+1] );
			pt.x=r1->pt.x;
			pt.y=r1->pt.y;
			mpt.x=r2->pt.x;
			mpt.y=r2->pt.y;
			err = homog_xfer_err3( pt, mpt, M );
			if(err<=err_square)
			{
				inliers_ptpairs.push_back(ptpairs[i]);
				inliers_ptpairs.push_back(ptpairs[i+1]);
				in++;
			}
		}
		return in;
}

static __inline void release_mem3( CvPoint2D64f* pts1, CvPoint2D64f* pts2)
{
	free( pts1 );
	free( pts2 );
}

CvMat* ransac_xform3( vector<int>& ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
	int m, double p_badxform, double err_tol)
{
	CvPoint2D64f* pts, * mpts;
	CvMat* M = NULL;
	CvMat* Max_M= NULL;

	double p, in_frac = 0.25;
	int i, nm, in, in_min, in_max = 0, k = 0;//n是number of features in feat

	nm = (int)ptpairs.size()/2;
	if( nm < m )
	{
		fprintf( stderr, "Warning: not enough matches to compute xform, %s" \
			" line %d\n", __FILE__, __LINE__ );
		return NULL;
	}

	in_min = calc_min_inliers3( nm, m, RANSAC_PROB_BAD_SUPP, p_badxform );

	p = pow( 1.0 - pow( in_frac, m ), k );
	i = 0;
	vector<int> Temp_ptpairs;
	vector<int> inliers_ptpairs;
	vector<int> sample_ptpairs;
	while( p > p_badxform )
	{
		draw_ransac_sample3( ptpairs,sample_ptpairs);
		extract_corresp_pts3( sample_ptpairs,CurrentKeypoints,PreKeypoints, m, mtype, &pts, &mpts );
		M = lsq_homog3(pts,mpts, m );

		if( ! M )
			goto iteration_end;
		in = find_consensus3( ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol,Temp_ptpairs);
		if( in > in_max )
		{
			in_max = in;
			in_frac = (double)in_max / nm;
			inliers_ptpairs=Temp_ptpairs;

			Max_M=cvCloneMat(M);
		}
		cvReleaseMat( &M );

iteration_end:
		release_mem3( pts, mpts);
		p = pow( 1.0 - pow( in_frac, m ), ++k );
	}

	if( in_max >= in_min )
	{
		extract_corresp_pts3( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in_max, mtype, &pts, &mpts );
		M = lsq_homog3( pts, mpts, in_max );

		in = find_consensus3(ptpairs,CurrentKeypoints,PreKeypoints, mtype, M, err_tol, inliers_ptpairs);
		cvReleaseMat( &M );
		release_mem3( pts, mpts );
		extract_corresp_pts3( inliers_ptpairs,CurrentKeypoints,PreKeypoints, in, mtype, &pts, &mpts );
		ptpairs.clear();
		ptpairs=inliers_ptpairs;//把内点序列存储在ptpairs内
		M = lsq_homog3( pts, mpts, in );
		release_mem3( pts, mpts );
	}

	Temp_ptpairs.clear();
	inliers_ptpairs.clear();
	sample_ptpairs.clear();
	return M;
}


CvMat* GetH3(vector<int>& ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints)
{
	CvMat* H;
	H = ransac_xform3( ptpairs,CurrentKeypoints,PreKeypoints, FEATURE_FWD_MATCH, 4, 0.02, 3.0 );
	return H;
}


////////快速匹配
void CariRecursive(QString strInitPath, QString strFileName)  //暗号
{
	/*CFileFind ff;
	QString strPath;
	BOOL bFound = TRUE;
	QString strrrr("\\*");
	strPath = strInitPath +strrrr;
	if( ff.FindFile(strPath) )
	{		
		while(bFound)
		{
			bFound = ff.FindNextFile();
			if(!ff.IsDots())
			{
				QString strFile = ff.GetFilePath();

				if(ff.IsDirectory())
				{
					CariRecursive(strFile, strFileName);
				}
			}
		}*/
		QString sttttr("\\");
		ScanFiles(strInitPath /*+ sttttr + strFileName */);

	/*}

	ff.Close();*/

}

void ScanFiles(QString strNameFile) //扫描文件，判断是否已经入库   暗号
{


	/* QDir d=strNameFile;                        // “./example”
    if ( !d.exists() )
        qWarning( "Cannot find the example directory" );
  
	CFileFind ff;
	BOOL bFound = TRUE;
	xishu.clear();
	lujing.clear();

	if( ff.FindFile(strNameFile) )
	{
		while(bFound)
		{
			bFound = ff.FindNextFile();
			if((!ff.IsDots()) && (!ff.IsDirectory()))
			{
				CString strFile = ff.GetFilePath();
				
				Madhosi(strFile);
						
			}
		}
	}

	ff.Close();*/


	 //判断路径是否存在
    QDir dir(strNameFile);
    if(!dir.exists())
    {
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
    {
        return;
    }

    QStringList string_list;
    for(int i=0; i<file_count;i++)
    {
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("jpg"), Qt::CaseInsensitive) == 0)   
        {   
            QString absolute_file_path = file_info.absoluteFilePath();
            string_list.append(absolute_file_path);
			Madhosi(absolute_file_path);
        }
    }

}



double Madhosi(QString strNameFile) //获取图像特征值,并比较   暗号
{
	QString strTemp;
	CxImage imageAsli1;
	/*const size_t strsize=(strNameFile.GetLength()+1)*2; // 宽字符的长度;
    char* strNameFile1= new char[strsize]; //分配空间;
    size_t sz=0;
    wcstombs_s(&sz,strNameFile1,strsize,strNameFile,_TRUNCATE);
    int atoiato=atoi((const char*)strNameFile1); // 字符串已经由原来的QString 转换成了 const char*/
	QString dir_s=strNameFile;
	const QByteArray text = dir_s.toLocal8Bit();
	const char *strNameFile1 = text.data();

	//imageAsli1.Load(strNameFile1,CXIMAGE_FORMAT_TIF);
	imageAsli1.Load(strNameFile1);

	double dTemp,dTempColor,dTempCuve,dTempShape;
	int i;
	double powCuve[15]={0.1,0.1,0.1,0.1,0.1,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05};
	double powShape[8]={0.2,0.2,0.15,0.15,0.1,0.05,0.05,01};
	
	ColorSplit(imageAsli1);
	CuveSplit(imageAsli1);
	ShapeSplit(imageAsli1);
	//
	//
	dTempColor = 0.0;
	dTempCuve=0.0;
	dTempShape=0.0;
	double dQueryNum = 0.0;
	for(i = 0; i < 111; i++ )
	{
		dTempColor += max1(m_KeyMainColorSig[i],m_Color[i]);
		dQueryNum += m_KeyMainColorSig[i];
	}

	//
	dTempColor = dQueryNum/dTempColor;

	for(i=0;i<15;i++)
	{
		if(m_KeyCuve[i]!=0||m_Cuve[i]!=0)
			dTempCuve = dTempCuve + powCuve[i]*fabs((m_KeyCuve[i]-m_Cuve[i])/max1(m_KeyCuve[i],m_Cuve[i]));
	}
	dTempCuve = 1 -dTempCuve;

	for(i=0;i<8;i++)
	{
		if(m_KeyShape[i]!=0&&m_Shape[i]!=0)
			dTempShape = dTempShape + powShape[i]*fabs((m_KeyShape[i]-m_Shape[i])/(m_KeyShape[i] > m_Shape[i]?m_KeyShape[i]:m_Shape[i]));

	}
	dTempShape = 1-dTempShape;

	dTemp = dTempColor*ColorPow + dTempCuve*CuvePow + dTempShape*ShapePow;
	dTemp = 1-dTemp;

	xishu.push_back(dTemp);/////相似性
	lujing.push_back(strNameFile);///对应的路径
	return dTemp;

}



bool ColorSplit(CxImage m_img)
{
	CxImage imgTemp;
	CxImage hImage;      //HSI图像H分量
	CxImage sImage;		//HSI图像S分量
	CxImage iImage;		//HSI图像I分量
	CxImage rImage;      //HSI图像H分量
	CxImage gImage;		//HSI图像S分量
	CxImage bImage;		//HSI图像I分量
	int iWidth = m_img.GetWidth();
	int iHeight = m_img.GetHeight();
	iWidth = 256;
	iHeight = 256;
	// int* m_ColorSig;
	m_img.Resample(iWidth, iHeight);	
	int iPixelSize = 1; // 1=GrayScale, 3=24bpp, 4=32bpp

	int iRow;
	int iCol;
	int dTemp;
	BYTE *phImage;
	BYTE *psImage;
	BYTE *piImage;
	BYTE *prImage;
	BYTE *pgImage;
	BYTE *pbImage;

	for(iRow=0;iRow<111;iRow++)
	{
		m_Color[iRow]=0;
	}



	//将图像重抽样并分离hsi分量
	imgTemp.Copy(m_img);
	//imgTemp.Resample(iWidth, iHeight);
	imgTemp.SplitRGB(&rImage,&gImage,&bImage);	
	prImage = rImage.GetBits();
	pgImage = gImage.GetBits();
	pbImage = bImage.GetBits();
	imgTemp.SplitHSL(&hImage,&sImage,&iImage);		
	phImage = hImage.GetBits();
	psImage = sImage.GetBits();
	piImage = iImage.GetBits();
	//
	for(iRow = 0; iRow < iHeight; iRow ++)
	{		
		for(iCol = 0; iCol < iWidth; iCol ++ )
		{
			bool isGray = false;
			//R=G=B或S=[0,0.05)或I=[0,20)或I=[250,255]或I=[20,40)&&S=[0.02,0.16)或I=[228,250)&&S=[0.02,0.05)
			isGray = isGray||((prImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)] == pgImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]) &&
				(prImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]  == pbImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]));
			isGray = isGray||(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=0&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=5);
			isGray = isGray||(piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=0&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<20);
			isGray = isGray||(piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=250&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=255);
			isGray = isGray||((piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=20&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<40) &&
				(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=5&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=40));
			isGray = isGray||((piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=228&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<250) &&
				(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=5&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=12));
			if(isGray)
			{
				dTemp = 108+(int)piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86;
			}
			else
			{
				// 量化为一维 L = 9h+3s+i
				dTemp = ((int)((float)phImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]*12.0f/255.0f) % 12) * 9 + 
					((int)psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86) * 3 +
					(int)piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86;
			}
			if(dTemp < 0)
			{
				dTemp = 0;
			}
			if(dTemp > 110)
			{
				dTemp = 110;
			}
			m_Color[dTemp]++;
		}
	}
	return true;
}
/*bool ColorSplit(QImage m_img)
{
	QImage imgTemp;
	QImage hImage;      //HSI图像H分量
	QImage sImage;		//HSI图像S分量
	QImage iImage;		//HSI图像I分量
	QImage rImage;      //HSI图像H分量
	QImage gImage;		//HSI图像S分量
	QImage bImage;		//HSI图像I分量
	int iWidth = m_img.width();
	int iHeight = m_img.height();
	iWidth = 256;
	iHeight = 256;
	// int* m_ColorSig;
	m_img.scaled(iWidth, iHeight,Qt::KeepAspectRatio);	
	int iPixelSize = 1; // 1=GrayScale, 3=24bpp, 4=32bpp

	int iRow;
	int iCol;
	int dTemp;
	BYTE *phImage;
	BYTE *psImage;
	BYTE *piImage;
	BYTE *prImage;
	BYTE *pgImage;
	BYTE *pbImage;

	for(iRow=0;iRow<111;iRow++)
	{
		m_Color[iRow]=0;
	}



	//将图像重抽样并分离hsi分量
	imgTemp=m_img;
	//imgTemp.Resample(iWidth, iHeight);
	imgTemp.SplitRGB(&rImage,&gImage,&bImage);	
	prImage = rImage.GetBits();
	pgImage = gImage.GetBits();
	pbImage = bImage.GetBits();
	imgTemp.SplitHSL(&hImage,&sImage,&iImage);		
	phImage = hImage.GetBits();
	psImage = sImage.GetBits();
	piImage = iImage.GetBits();
	//
	for(iRow = 0; iRow < iHeight; iRow ++)
	{		
		for(iCol = 0; iCol < iWidth; iCol ++ )
		{
			bool isGray = false;
			//R=G=B或S=[0,0.05)或I=[0,20)或I=[250,255]或I=[20,40)&&S=[0.02,0.16)或I=[228,250)&&S=[0.02,0.05)
			isGray = isGray||((prImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)] == pgImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]) &&
				(prImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]  == pbImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]));
			isGray = isGray||(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=0&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=5);
			isGray = isGray||(piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=0&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<20);
			isGray = isGray||(piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=250&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=255);
			isGray = isGray||((piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=20&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<40) &&
				(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=5&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=40));
			isGray = isGray||((piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=228&&piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<250) &&
				(psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]>=5&&psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]<=12));
			if(isGray)
			{
				dTemp = 108+(int)piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86;
			}
			else
			{
				// 量化为一维 L = 9h+3s+i
				dTemp = ((int)((float)phImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]*12.0f/255.0f) % 12) * 9 + 
					((int)psImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86) * 3 +
					(int)piImage[(iRow*iPixelSize*iWidth) + (iCol*iPixelSize)]/86;
			}
			if(dTemp < 0)
			{
				dTemp = 0;
			}
			if(dTemp > 110)
			{
				dTemp = 110;
			}
			m_Color[dTemp]++;
		}
	}
	return true;
}*/

bool CuveSplit(CxImage m_img)
{
	CxImage imgTemp;
	CxImage hImage;      //HSI图像H分量
	CxImage sImage;		//HSI图像S分量
	CxImage iImage;		//HSI图像I分量
	int iWidth = m_img.GetWidth();
	int iHeight = m_img.GetHeight();
	iWidth = 256;
	iHeight = 256;
	m_img.Resample(iWidth, iHeight);

	int iPixelSize = 1; // 1=GrayScale, 3=24bpp, 4=32bpp

	int iRow;
	int iCol;
	int max=0,min=255;
	BYTE *piImage;
	int m_cuve[256*256];
	int mWidth,mHeight;
	double H[16][16];//灰度梯度矩阵
	// double *m_Cuve;
	double mean=0,L1=0,L2=0,L3=0,L4=0,L5=0,L6=0,L7=0,L8=0,L9=0,L10=0,L11=0,L12=0,L13=0,L14=0,L15=0,L16=0,L17=0,L18=0;//均值及一些简单中间运算结果

	for(iRow=0;iRow<15;iRow++)
	{
		m_Cuve[iRow]=0;
	}


	for(iRow=0;iRow<256*256;iRow++)
		m_cuve[iRow] = 0;	


	//计算梯度
	//
	imgTemp.Copy(m_img);
	//imgTemp.Resample(iWidth, iHeight);
	imgTemp.SplitHSL(&hImage,&sImage,&iImage);		
	piImage = iImage.GetBits();

	//初始化灰度梯度矩阵
	for(iRow=0;iRow<16;iRow++)
	{
		for(iCol=0;iCol<16;iCol++)
		{
			H[iRow][iCol]=0;
		}
	}

	for(iRow=0;iRow<iHeight;iRow++)
		for(iCol=0;iCol<iWidth;iCol++)
		{
			piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize] = (int)piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize]/16;
		}

		for(iRow=0;iRow<iHeight;iRow++)
		{for(iCol=0;iCol<iWidth;iCol++)
		if(iCol!=0 && iRow!=0 && iCol!=(iWidth-1) && iRow!=(iHeight-1))
		{
			m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize] = abs(piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize]-piImage[(iRow+1)*iWidth*iPixelSize+iCol*iPixelSize+1]) + abs(piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize+1] - piImage[(iRow+1)*iWidth*iPixelSize+iCol*iPixelSize]);

			if(m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize] > 15)
				m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize] = 15;
		}
		else
			m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize] = piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize];
		}

		for(iRow=0;iRow<iHeight;iRow++)
		{for(iCol=0;iCol<iWidth;iCol++)
		{if(max<m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize])
		max = m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize];
		if(min>m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize])
			min = m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize];
		}
		}

		mWidth = 16;
		mHeight = max-min;

		for(iRow=0;iRow<iHeight;iRow++)
		{
			for(iCol=0;iCol<iWidth;iCol++)
			{
				m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize] -= min;
				H[piImage[iRow*iWidth*iPixelSize+iCol*iPixelSize]][m_cuve[iRow*iWidth*iPixelSize+iCol*iPixelSize]]++;
			}
		}


		for(iRow=0;iRow<mWidth;iRow++)
		{	for(iCol=0;iCol<mHeight;iCol++)
		H[iRow][iCol]/= pow((iHeight*iWidth),2.0);
		}

		for(iRow=0;iRow<mWidth;iRow++)
		{for(iCol=0;iCol<mHeight;iCol++)

		{mean += H[iRow][iCol];
		L2+= H[iRow][iCol]*pow((iCol),2.0);
		L15+= H[iRow][iCol];
		L5+= ((iRow-iCol)^2)*H[iRow][iCol];
		L6+= H[iRow][iCol]/(1+pow((iRow-iCol),2.0));
		L7+= pow(H[iRow][iCol],2);
		L1+= H[iRow][iCol]/pow((iCol+1),2.0);
		if (H[iRow][iCol]>0) 
		{
			L4+= -H[iRow][iCol]*log10(H[iRow][iCol]);
		}

		}
		L3+=pow(L15,2);
		if (mean>0) 
		{
			L8+=-H[iRow][iCol]*log10(mean);
		}		   

		}
		for(iCol=0;iCol<mHeight;iCol++)
		{for(iRow=0;iRow<mWidth;iRow++)


		{
			L16+= H[iRow][iCol];

			L10+=iCol*L16;
		}

		L11+=-H[iRow][iCol]*log10(L16);

		L9+=pow(L16,2);

		}
		for(iRow=0;iRow<mWidth;iRow++)
		{	for(iCol=0;iCol<mHeight;iCol++)
		{
			{
				L17+=H[iRow][iCol];
			}
			L12+=pow((iRow-mean),2)*L17;
			L13+=(iRow-mean)*(iCol-L10)*L17;
		}
		}

		for(iCol=0;iCol<mHeight;iCol++)
		{for(iRow=0;iRow<mWidth;iRow++)
		{
			{
				L18+=H[iRow][iCol];
			}
			L14+=pow((iCol-L10),2)*L18;
		}
		}

		m_Cuve[0] = fabs(L1/mean);
		m_Cuve[1] = fabs(L2/mean);
		m_Cuve[2] = fabs(L3/mean);
		m_Cuve[3] = fabs(L9/mean);
		m_Cuve[4] = fabs(L7);
		m_Cuve[5] = fabs(mean);
		m_Cuve[6] = fabs(L10);
		m_Cuve[7] = sqrt(L12);
		m_Cuve[8] = sqrt(L14);
		m_Cuve[9] = fabs(L13);
		m_Cuve[10] = fabs(L8);
		m_Cuve[11] = fabs(L11);
		m_Cuve[12] = fabs(L4);
		m_Cuve[13] = fabs(L5);
		m_Cuve[14] = fabs(L6);
		return true;
}


bool ShapeSplit(CxImage m_img)
{
	CxImage imgTemp;
	CxImage hImage;      //HSI图像H分量
	CxImage sImage;		//HSI图像S分量
	CxImage iImage;		//HSI图像I分量
	int iWidth = m_img.GetWidth();
	int iHeight = m_img.GetHeight();
	iWidth = 256;
	iHeight = 256;
	m_img.Resample(iWidth, iHeight);
	BYTE *copyImage,*pUnch;
	int iPixelSize = 1; // 1=GrayScale, 3=24bpp, 4=32bpp

	int iRow;
	int iCol;
	int i,j;
	//	double dRatioLow,dRatioHigh;
	// 	int max=0,min=255;
	// 	int Dist;

	double M[4][4];

	for(i=0;i<8;i++)
	{
		m_Shape[i]=0;
	}
	imgTemp.Copy(m_img);
	//	imgTemp.Resample(iWidth, iHeight);
	imgTemp.SplitHSL(&hImage,&sImage,&iImage);		


	pUnch = iImage.GetBits();
	copyImage=new BYTE[iWidth*iHeight];
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			M[i][j] = 0;

	Canny(pUnch,iWidth,iHeight,0.4,1.2,0.79,copyImage);//Canny计算边缘

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(iRow=0;iRow<iHeight;iRow++)
			{
				for(iCol=0;iCol<iWidth;iCol++)
					M[i][j] += copyImage[iRow*iWidth*iPixelSize+iCol*iPixelSize]*pow((float(iRow)),i)*pow((float(iCol)),j);
			}
		}

	}
		m_Shape[0] = fabs((M[2][0] + M[0][2])/M[0][0]);
		m_Shape[1] = fabs((pow((M[2][0]-M[0][2]),2) + 4*pow(M[1][1],2))/pow(M[0][0],2));
		m_Shape[2] = fabs((pow((M[3][0]-3*M[1][2]),2) + pow((3*M[2][1]-M[0][3]),2))/pow(M[0][0],3));
		m_Shape[3] = fabs((pow((M[3][0]+M[1][2]),2) + pow((M[0][3]+M[2][1]),2))/pow(M[0][0],3));
		m_Shape[4] = fabs(((M[3][0]-3*M[1][2])*(M[3][0]+M[1][2])*(pow((M[3][0]+M[1][2]),2)-3*pow((M[2][1]+M[0][3]),2)) + (3*M[2][1]-M[0][3])*(M[2][1]+M[0][3])*(3*pow((M[3][0]+M[1][2]),2)-pow((M[2][1]+M[0][3]),2)))/pow(M[0][0],6));
		m_Shape[5] = fabs(((M[2][0]-M[0][2])*((pow((M[3][0]+M[1][2]),2)) - (pow((M[0][3]+M[2][1]),2))) + 4*M[1][1]*(M[3][0]+M[1][2])*(M[2][1]+M[0][3]))/pow(M[0][0],4));
		m_Shape[6] = fabs(((3*M[2][1]-M[0][3])*(M[2][1]+M[0][3])*(pow((M[3][0]+M[2][1]),2)-3*pow((M[0][3]+M[1][2]),2)) + (3*M[1][2]-M[3][0])*(M[1][2]+M[3][0])*(3*pow((M[0][3]+M[2][1]),2)-pow((M[3][0]+M[1][2]),2)))/pow(M[0][0],6));
		m_Shape[7] = ((M[2][0]-M[0][2])*(M[2][0]-M[0][2])+4*M[1][1]*M[1][1])/((M[2][0]+M[0][2])*(M[2][0]+M[0][2]));

		return true;

}

/*************************************************************************
 *
 * \函数名称：
 *   MakeGauss()
 *
 * \输入参数:
 *   double sigma         - 高斯函数的标准差
 *   double **pdKernel - 指向高斯数据数组的指针
 *   int *pnWindowSize - 数据的长度
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   这个函数可以生成一个一维的高斯函数的数字数据，理论上高斯数据的长度应
 *   该是无限长的，但是为了计算的简单和速度，实际的高斯数据只能是有限长的
 *   pnWindowSize就是数据长度
 *   
 *************************************************************************
 */
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize)
{
// 循环控制变量
int i   ;

// 数组的中心点
int nCenter;

// 数组的某一点到中心点的距离
double  dDis  ; 

//double PI = 3.1415926;
// 中间变量
double  dValue; 
double  dSum  ;
dSum = 0 ; 

// 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
// 这些数据会覆盖绝大部分的滤波系数
*pnWindowSize = 1 + 2 * ceil(3 * sigma);

// 中心
nCenter = (*pnWindowSize) / 2;

// 分配内存
*pdKernel = new double[*pnWindowSize] ;

for(i=0; i< (*pnWindowSize); i++)
{
dDis = (double)(i - nCenter);
dValue = exp(-(1/2)*dDis*dDis/(sigma*sigma)) / (sqrt(2 * PI) * sigma );
(*pdKernel)[i] = dValue ;
dSum += dValue;
}

// 归一化
for(i=0; i<(*pnWindowSize) ; i++)
{
(*pdKernel)[i] /= dSum;
}
}

/*************************************************************************
 *
 * \函数名称：
 *   GaussianSmooth()
 *
 * \输入参数:
 *   unsigned char * pUnchImg - 指向图象数据的指针
 *   int nWidth - 图象数据宽度
 *   int nHeight - 图象数据高度
 *   double dSigma - 高斯函数的标准差
 *   unsigned char * pUnchSmthdImg - 指向经过平滑之后的图象数据
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   为了抑止噪声，采用高斯滤波对图象进行滤波，滤波先对x方向进行，然后对
 *   y方向进行。
 *   
 *************************************************************************
 */
void GaussianSmooth(unsigned char *pUnchImg, int nWidth, int nHeight, 
double sigma, unsigned char * pUnchSmthdImg)
{
// 循环控制变量
  int y;
int x;

int i;

// 高斯滤波器的数组长度

int nWindowSize;

//  窗口长度的1/2
int nHalfLen;   

// 一维高斯数据滤波器
double *pdKernel ;

// 高斯系数与图象数据的点乘
double  dDotMul     ;

// 高斯滤波系数的总和
double  dWeightSum     ;          
  
// 中间变量
double * pdTmp ;

// 分配内存
pdTmp = new double[nWidth*nHeight];

// 产生一维高斯数据滤波器
// MakeGauss(sigma, &dKernel, &nWindowSize);
MakeGauss(sigma, &pdKernel, &nWindowSize) ;

// MakeGauss返回窗口的长度，利用此变量计算窗口的半长
nHalfLen = nWindowSize / 2;

  // x方向进行滤波
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
dDotMul = 0;
dWeightSum = 0;
for(i=(-nHalfLen); i<=nHalfLen; i++)
{
// 判断是否在图象内部
if( (i+x) >= 0  && (i+x) < nWidth )
{
dDotMul += (double)pUnchImg[y*nWidth + (i+x)] * pdKernel[nHalfLen+i];
dWeightSum += pdKernel[nHalfLen+i];
}
}
pdTmp[y*nWidth + x] = dDotMul/dWeightSum ;
}
}

// y方向进行滤波
for(x=0; x<nWidth; x++)
{
for(y=0; y<nHeight; y++)
{
dDotMul = 0;
dWeightSum = 0;
for(i=(-nHalfLen); i<=nHalfLen; i++)
{
// 判断是否在图象内部
if( (i+y) >= 0  && (i+y) < nHeight )
{
dDotMul += (double)pdTmp[(y+i)*nWidth + x] * pdKernel[nHalfLen+i];
dWeightSum += pdKernel[nHalfLen+i];
}
}
pUnchSmthdImg[y*nWidth + x] = (unsigned char)(int)dDotMul/dWeightSum ;
}
}

// 释放内存
delete []pdKernel;
pdKernel = NULL ;

delete []pdTmp;
pdTmp = NULL;
}
/*************************************************************************
 *
 * \函数名称：
 *   DirGrad()
 *
 * \输入参数:
 *   unsigned char *pUnchSmthdImg - 经过高斯滤波后的图象
 *   int nWidht - 图象宽度
 *   int nHeight       - 图象高度
 *   int *pnGradX                         - x方向的方向导数
 *   int *pnGradY                         - y方向的方向导数
 * \返回值:
 *   无
 *
 * \说明:
 *   这个函数计算方向倒数，采用的微分算子是(-1 0 1) 和 (-1 0 1)'(转置)
 *   计算的时候对边界象素采用了特殊处理
 *   
 *   
 *************************************************************************
 */
void DirGrad(unsigned char *pUnchSmthdImg, int nWidth, int nHeight,
 int *pnGradX , int *pnGradY)
{
// 循环控制变量
int y ;
int x ;

// 计算x方向的方向导数，在边界出进行了处理，防止要访问的象素出界
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
pnGradX[y*nWidth+x] = (int) ( pUnchSmthdImg[y*nWidth+min1(nWidth-1,x+1)]  
          - pUnchSmthdImg[y*nWidth+max1(0,x-1)]     );
}
}

// 计算y方向的方向导数，在边界出进行了处理，防止要访问的象素出界
for(x=0; x<nWidth; x++)
{
for(y=0; y<nHeight; y++)
{
pnGradY[y*nWidth+x] = (int) ( pUnchSmthdImg[min1(nHeight-1,y+1)*nWidth + x]  
- pUnchSmthdImg[max1(0,y-1)*nWidth+ x ]     );
}
}
}

/*************************************************************************
 *
 * \函数名称：
 *   GradMagnitude()
 *
 * \输入参数:
 *   int *pnGradX                         - x方向的方向导数
 *   int *pnGradY                         - y方向的方向导数
 *   int nWidht - 图象宽度
 *   int nHeight       - 图象高度
 *   int *pnMag                           - 梯度幅度   
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   这个函数利用方向倒数计算梯度幅度，方向倒数是DirGrad函数计算的结果
 *   
 *************************************************************************
 */
void GradMagnitude(int *pnGradX, int *pnGradY, int nWidth, int nHeight, int *pnMag)
{

// 循环控制变量
int y ;
int x ;

// 中间变量
double dSqtOne;
double dSqtTwo;

for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
dSqtOne = pnGradX[y*nWidth + x] * pnGradX[y*nWidth + x];
dSqtTwo = pnGradY[y*nWidth + x] * pnGradY[y*nWidth + x];
pnMag[y*nWidth + x] = (int)(sqrt(dSqtOne + dSqtTwo) + 0.5);
}
}
}


/*************************************************************************
 *
 * \函数名称：
 *   NonmaxSuppress()
 *
 * \输入参数:
 *   int *pnMag                - 梯度图
 *   int *pnGradX  - x方向的方向导数 
 *   int *pnGradY              - y方向的方向导数
 *   int nWidth                - 图象数据宽度
 *   int nHeight               - 图象数据高度
 *   unsigned char *pUnchRst   - 经过NonmaxSuppress处理后的结果
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   抑止梯度图中非局部极值点的象素。
 *   
 *************************************************************************
 */
void NonmaxSuppress(int *pnMag, int *pnGradX, int *pnGradY, int nWidth, 
int nHeight, unsigned char *pUnchRst)
{
// 循环控制变量
int y ;
int x ;
int nPos;

// x方向梯度分量
int gx  ;
int gy  ;

// 临时变量
int g1, g2, g3, g4 ;
double weight  ;
double dTmp1   ;
double dTmp2   ;
double dTmp    ;

// 设置图象边缘部分为不可能的边界点
for(x=0; x<nWidth; x++) 
{
pUnchRst[x] = 0 ;
pUnchRst[nHeight-1+x] = 0;
}
for(y=0; y<nHeight; y++) 
{
pUnchRst[y*nWidth] = 0 ;
pUnchRst[y*nWidth + nWidth-1] = 0;
}

for(y=1; y<nHeight-1; y++)
{
for(x=1; x<nWidth-1; x++)
{
nPos = y*nWidth + x ;

// 如果当前象素的梯度幅度为0，则不是边界点
if(pnMag[nPos] == 0 )
{
pUnchRst[nPos] = 0 ;
}
else
{
// 当前象素的梯度幅度
dTmp = pnMag[nPos] ;

// x，y方向导数
gx = pnGradX[nPos]  ;
gy = pnGradY[nPos]  ;

// 如果方向导数y分量比x分量大，说明导数的方向更加“趋向”于y分量。
if (abs(gy) > abs(gx)) 
{
// 计算插值的比例
weight = fabs(float(gx))/fabs(float(gy)); 

g2 = pnMag[nPos-nWidth] ; 
g4 = pnMag[nPos+nWidth] ;

// 如果x，y两个方向的方向导数的符号相同
// C是当前象素，与g1-g4的位置关系为：
// g1 g2 
//  C         
//  g4 g3 
if (gx*gy > 0) 
{  
g1 = pnMag[nPos-nWidth-1] ;
g3 = pnMag[nPos+nWidth+1] ;
} 

// 如果x，y两个方向的方向导数的符号相反
// C是当前象素，与g1-g4的位置关系为：
//    g2 g1
//  C         
// g3 g4  
else 
{ 
g1 = pnMag[nPos-nWidth+1] ;
g3 = pnMag[nPos+nWidth-1] ;
} 
}

// 如果方向导数x分量比y分量大，说明导数的方向更加“趋向”于x分量
// 这个判断语句包含了x分量和y分量相等的情况
else
{
// 计算插值的比例
weight = fabs(float(gy))/fabs(float(gx)); 

g2 = pnMag[nPos+1] ; 
g4 = pnMag[nPos-1] ;

// 如果x，y两个方向的方向导数的符号相同
// C是当前象素，与g1-g4的位置关系为：
// g3   
// g4 C g2       
//       g1
if (gx*gy > 0) 
{ 
g1 = pnMag[nPos+nWidth+1] ;
g3 = pnMag[nPos-nWidth-1] ;
} 
// 如果x，y两个方向的方向导数的符号相反
// C是当前象素，与g1-g4的位置关系为：
//      g1
// g4 C g2       
//  g3     
else 
{ 
g1 = pnMag[nPos-nWidth+1] ;
g3 = pnMag[nPos+nWidth-1] ;
}
}

// 下面利用g1-g4对梯度进行插值
{
dTmp1 = weight*g1 + (1-weight)*g2 ;
dTmp2 = weight*g3 + (1-weight)*g4 ;

// 当前象素的梯度是局部的最大值
// 该点可能是个边界点
if(dTmp>=dTmp1 && dTmp>=dTmp2)
{
pUnchRst[nPos] = 128 ;
}
else
{
// 不可能是边界点
pUnchRst[nPos] = 0 ;
}
}
} //else
} // for

}
} 
/*************************************************************************
 *
 * \函数名称：
 *   EstimateThreshold()
 *
 * \输入参数:
 *   int *pnMag               - 梯度幅度图
 *  int nWidth               - 图象数据宽度
 *  int nHeight              - 图象数据高度
 *   int *pnThdHigh           - 高阈值
 *   int *pnThdLow            - 低阈值
 *  double dRatioLow         - 低阈值和高阈值之间的比例
 *  double dRatioHigh        - 高阈值占图象象素总数的比例
 *   unsigned char *pUnchEdge - 经过non-maximum处理后的数据
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   经过non-maximum处理后的数据pUnchEdge，统计pnMag的直方图，确定阈值。
 *   本函数中只是统计pUnchEdge中可能为边界点的那些象素。然后利用直方图，
 *   根据dRatioHigh设置高阈值，存储到pnThdHigh。利用dRationLow和高阈值，
 *   设置低阈值，存储到*pnThdLow。dRatioHigh是一种比例：表明梯度小于
 *   *pnThdHigh的象素数目占象素总数目的比例。dRationLow表明*pnThdHigh
 *   和*pnThdLow的比例，这个比例在canny算法的原文里，作者给出了一个区间。
 *
 *************************************************************************
 */
void EstimateThreshold(int *pnMag, int nWidth, int nHeight, int *pnThdHigh,int *pnThdLow, 
 unsigned char * pUnchEdge, double dRatioHigh, double dRationLow) 
{ 
// 循环控制变量
int y;
int x;
int k;

// 该数组的大小和梯度值的范围有关，如果采用本程序的算法，那么梯度的范围不会超过pow(2,10)
int nHist[1024] ;

// 可能的边界数目
int nEdgeNb     ;

// 最大梯度值
int nMaxMag     ;

int nHighCount  ;

nMaxMag = 0     ; 

// 初始化
for(k=0; k<1024; k++) 
{
nHist[k] = 0; 
}

// 统计直方图，然后利用直方图计算阈值
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
// 只是统计那些可能是边界点，并且还没有处理过的象素
if(pUnchEdge[y*nWidth+x]==128)
{
nHist[ pnMag[y*nWidth+x] ]++;
}
}
}

nEdgeNb = nHist[0]  ;
nMaxMag = 0         ;
// 统计经过“非最大值抑止(non-maximum suppression)”后有多少象素
for(k=1; k<1024; k++)
{
if(nHist[k] != 0)
{
// 最大梯度值
nMaxMag = k;
}

// 梯度为0的点是不可能为边界点的
// 经过non-maximum suppression后有多少象素
nEdgeNb += nHist[k];
}

// 梯度比高阈值*pnThdHigh小的象素点总数目
nHighCount = (int)(dRatioHigh * nEdgeNb +0.5);

k = 1;
nEdgeNb = nHist[1];

// 计算高阈值
while( (k<(nMaxMag-1)) && (nEdgeNb < nHighCount) )
{
k++;
nEdgeNb += nHist[k];
}

// 设置高阈值
*pnThdHigh = k ;

// 设置低阈值
*pnThdLow  = (int)((*pnThdHigh) * dRationLow+ 0.5);
}

/*************************************************************************
 *
 * \函数名称：
 *   TraceEdge()
 *
 * \输入参数:
 *   int    x - 跟踪起点的x坐标 
 *   int    y - 跟踪起点的y坐标
 *   int nLowThd - 判断一个点是否为边界点的低阈值
 *   unsigned char *pUnchEdge - 记录边界点的缓冲区
 *   int *pnMag               - 梯度幅度图
 *   int nWidth               - 图象数据宽度
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   递归调用  
 *   从(x,y)坐标出发，进行边界点的跟踪，跟踪只考虑pUnchEdge中没有处理并且
 *   可能是边界点的那些象素(=128),象素值为0表明该点不可能是边界点，象素值
 *   为255表明该点已经被设置为边界点，不必再考虑
 *   
 *   
 *************************************************************************
 */
void TraceEdge (int y, int x, int nLowThd, unsigned char *pUnchEdge, int *pnMag, int nWidth) 
{ 
// 对8邻域象素进行查询
int xNb[8] = {1, 1, 0,-1,-1,-1, 0, 1} ;
int yNb[8] = {0, 1, 1, 1,0 ,-1,-1,-1} ;

int yy ;
int xx ;

int k  ;

for(k=0; k<8; k++)
{
yy = y + yNb[k] ;
xx = x + xNb[k] ;
// 如果该象素为可能的边界点，又没有处理过
// 并且梯度大于阈值
if(pUnchEdge[yy*nWidth+xx] == 128  && pnMag[yy*nWidth+xx]>=nLowThd)
{
// 把该点设置成为边界点
pUnchEdge[yy*nWidth+xx] = 255 ;

// 以该点为中心进行跟踪
TraceEdge(yy, xx, nLowThd, pUnchEdge, pnMag, nWidth);
}
}
} 


/*************************************************************************
 *
 * \函数名称：
 *   Hysteresis()
 *
 * \输入参数:
 *   int *pnMag               - 梯度幅度图
 *  int nWidth               - 图象数据宽度
 *  int nHeight              - 图象数据高度
 *  double dRatioLow         - 低阈值和高阈值之间的比例
 *  double dRatioHigh        - 高阈值占图象象素总数的比例
 *   unsigned char *pUnchEdge - 记录边界点的缓冲区
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   本函数实现类似“磁滞现象”的一个功能，也就是，先调用EstimateThreshold
 *   函数对经过non-maximum处理后的数据pUnchSpr估计一个高阈值，然后判断
 *   pUnchSpr中可能的边界象素(=128)的梯度是不是大于高阈值nThdHigh，如果比
 *   该阈值大，该点将作为一个边界的起点，调用TraceEdge函数，把对应该边界
 *   的所有象素找出来。最后，当整个搜索完毕时，如果还有象素没有被标志成
 *   边界点，那么就一定不是边界点。
 *   
 *************************************************************************
 */
void Hysteresis(int *pnMag, int nWidth, int nHeight, double dRatioLow, 
double dRatioHigh, unsigned char *pUnchEdge)
{
// 循环控制变量
int y;
int x;

int nThdHigh ;
int nThdLow  ;

int nPos;

// 估计TraceEdge需要的低阈值，以及Hysteresis函数使用的高阈值
EstimateThreshold(pnMag, nWidth, nHeight, &nThdHigh, 
               &nThdLow, pUnchEdge,dRatioHigh, dRatioLow);

  // 这个循环用来寻找大于nThdHigh的点，这些点被用来当作边界点，然后用
// TraceEdge函数来跟踪该点对应的边界
   for(y=0; y<nHeight; y++)
 {
      for(x=0; x<nWidth; x++)
{
nPos = y*nWidth + x ; 

// 如果该象素是可能的边界点，并且梯度大于高阈值，该象素作为
// 一个边界的起点
if((pUnchEdge[nPos] == 128) && (pnMag[nPos] >= nThdHigh))
{
// 设置该点为边界点
pUnchEdge[nPos] = 255;
TraceEdge(y, x, nThdLow, pUnchEdge, pnMag, nWidth);
}
      }
   }

 // 那些还没有被设置为边界点的象素已经不可能成为边界点
   for(y=0; y<nHeight; y++)
 {
 for(x=0; x<nWidth; x++)
 {
 nPos = y*nWidth + x ; 
 if(pUnchEdge[nPos] != 255)
 {
 // 设置为非边界点
 pUnchEdge[nPos] = 0 ;
 }
 }
 }
}


/*************************************************************************
 *
 * \函数名称：
 *   Canny()
 *
 * \输入参数:
 *   unsigned char *pUnchImage- 图象数据
 *  int nWidth               - 图象数据宽度
 *  int nHeight              - 图象数据高度
 *   double sigma             - 高斯滤波的标准方差
 *  double dRatioLow         - 低阈值和高阈值之间的比例
 *  double dRatioHigh        - 高阈值占图象象素总数的比例
 *   unsigned char *pUnchEdge - canny算子计算后的分割图
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   canny分割算子，计算的结果保存在pUnchEdge中，逻辑1(255)表示该点为
 *   边界点，逻辑0(0)表示该点为非边界点。该函数的参数sigma，dRatioLow
 *   dRatioHigh，是需要指定的。这些参数会影响分割后边界点数目的多少
 *************************************************************************
 */
void Canny(unsigned char *pUnchImage, int nWidth, int nHeight, double sigma, double dRatioLow, double dRatioHigh, unsigned char *pUnchEdge)
{
// 经过高斯滤波后的图象数据
unsigned char * pUnchSmooth ;
  
// 指向x方向导数的指针
int * pnGradX ; 

// 指向y方向导数的指针
int * pnGradY ;

// 梯度的幅度
int * pnGradMag ;

pUnchSmooth  = new unsigned char[nWidth*nHeight] ;
pnGradX      = new int [nWidth*nHeight]          ;
pnGradY      = new int [nWidth*nHeight]          ;
pnGradMag    = new int [nWidth*nHeight]          ;

// 对原图象进行滤波
GaussianSmooth(pUnchImage, nWidth, nHeight, sigma, pUnchSmooth) ;

// 计算方向导数
DirGrad(pUnchSmooth, nWidth, nHeight, pnGradX, pnGradY) ;

// 计算梯度的幅度
GradMagnitude(pnGradX, pnGradY, nWidth, nHeight, pnGradMag) ;

// 应用non-maximum 抑制
NonmaxSuppress(pnGradMag, pnGradX, pnGradY, nWidth, nHeight, pUnchEdge) ;

// 应用Hysteresis，找到所有的边界
Hysteresis(pnGradMag, nWidth, nHeight, dRatioLow, dRatioHigh, pUnchEdge);


// 释放内存
delete pnGradX      ;
pnGradX      = NULL ;
delete pnGradY      ;
pnGradY      = NULL ;
delete pnGradMag    ;
pnGradMag    = NULL ;
delete pUnchSmooth ;
pUnchSmooth  = NULL ;
}


