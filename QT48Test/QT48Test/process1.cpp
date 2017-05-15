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
int m_KeyMainColorSig[111]; // ��ѯСͼ�������
double m_KeyCuve[15];
double m_KeyShape[8];
int m_Color[111];//����ͼ������
double m_Cuve[15],m_Shape[8];

extern double ColorPow;
extern double CuvePow;
extern double ShapePow;
/*************************����ondraw************************/
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
{                                           //  ����λͼ��Ϣ
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
	memcpy(lpBmi,&BIH,40);               //  ����λͼ��Ϣͷ
	if (bits==8) {                          //  256 ɫλͼ
		if (flag==1) {                       //  ���ûҽ׵�ɫ��
			for (i=0;i<256;i++) {
				ColorTab[i].rgbRed=ColorTab[i].rgbGreen=ColorTab[i].rgbBlue=(BYTE) i;
			}
			memcpy(lpBmi->bmiColors, ColorTab, 1024);
		}
		else if (flag==2) {                   //  ����Ĭ�ϵ�ɫ��
			memcpy(lpBmi->bmiColors, VgaDefPal, 1024);
		}
	}
	return(lpBmi);
}

int  imageClone(IplImage* pi, IplImage** ppo)    //  ���� IplImage λͼ (OpenCV)
{
	if (*ppo)
		cvReleaseImage(ppo);                  //  �ͷ�ԭ��λͼ
	(*ppo) = cvCloneImage(pi);                  //  ������λͼ
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
	int i, nm, in, in_min, in_max = 0, k = 0;//n��number of features in feat
	//m��minimum number of correspondences necessary to instantiate the  model computed by xform_fn
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
		//printf("��ȷƥ�����: %d\n", in);
		free(pts);
		free(mpts);
	}
	//else
	//	printf("��ȷƥ�����: %d\n", in);
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
	int i, nm, in, in_min, in_max = 0, k = 0;//n��number of features in feat

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
		ptpairs=inliers_ptpairs;//���ڵ����д洢��ptpairs��
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


////////����ƥ��
void CariRecursive(QString strInitPath, QString strFileName)  //����
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

void ScanFiles(QString strNameFile) //ɨ���ļ����ж��Ƿ��Ѿ����   ����
{


	/* QDir d=strNameFile;                        // ��./example��
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


	 //�ж�·���Ƿ����
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



double Madhosi(QString strNameFile) //��ȡͼ������ֵ,���Ƚ�   ����
{
	QString strTemp;
	CxImage imageAsli1;
	/*const size_t strsize=(strNameFile.GetLength()+1)*2; // ���ַ��ĳ���;
    char* strNameFile1= new char[strsize]; //����ռ�;
    size_t sz=0;
    wcstombs_s(&sz,strNameFile1,strsize,strNameFile,_TRUNCATE);
    int atoiato=atoi((const char*)strNameFile1); // �ַ����Ѿ���ԭ����QString ת������ const char*/
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

	xishu.push_back(dTemp);/////������
	lujing.push_back(strNameFile);///��Ӧ��·��
	return dTemp;

}



bool ColorSplit(CxImage m_img)
{
	CxImage imgTemp;
	CxImage hImage;      //HSIͼ��H����
	CxImage sImage;		//HSIͼ��S����
	CxImage iImage;		//HSIͼ��I����
	CxImage rImage;      //HSIͼ��H����
	CxImage gImage;		//HSIͼ��S����
	CxImage bImage;		//HSIͼ��I����
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



	//��ͼ���س���������hsi����
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
			//R=G=B��S=[0,0.05)��I=[0,20)��I=[250,255]��I=[20,40)&&S=[0.02,0.16)��I=[228,250)&&S=[0.02,0.05)
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
				// ����Ϊһά L = 9h+3s+i
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
	QImage hImage;      //HSIͼ��H����
	QImage sImage;		//HSIͼ��S����
	QImage iImage;		//HSIͼ��I����
	QImage rImage;      //HSIͼ��H����
	QImage gImage;		//HSIͼ��S����
	QImage bImage;		//HSIͼ��I����
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



	//��ͼ���س���������hsi����
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
			//R=G=B��S=[0,0.05)��I=[0,20)��I=[250,255]��I=[20,40)&&S=[0.02,0.16)��I=[228,250)&&S=[0.02,0.05)
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
				// ����Ϊһά L = 9h+3s+i
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
	CxImage hImage;      //HSIͼ��H����
	CxImage sImage;		//HSIͼ��S����
	CxImage iImage;		//HSIͼ��I����
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
	double H[16][16];//�Ҷ��ݶȾ���
	// double *m_Cuve;
	double mean=0,L1=0,L2=0,L3=0,L4=0,L5=0,L6=0,L7=0,L8=0,L9=0,L10=0,L11=0,L12=0,L13=0,L14=0,L15=0,L16=0,L17=0,L18=0;//��ֵ��һЩ���м�������

	for(iRow=0;iRow<15;iRow++)
	{
		m_Cuve[iRow]=0;
	}


	for(iRow=0;iRow<256*256;iRow++)
		m_cuve[iRow] = 0;	


	//�����ݶ�
	//
	imgTemp.Copy(m_img);
	//imgTemp.Resample(iWidth, iHeight);
	imgTemp.SplitHSL(&hImage,&sImage,&iImage);		
	piImage = iImage.GetBits();

	//��ʼ���Ҷ��ݶȾ���
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
	CxImage hImage;      //HSIͼ��H����
	CxImage sImage;		//HSIͼ��S����
	CxImage iImage;		//HSIͼ��I����
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

	Canny(pUnch,iWidth,iHeight,0.4,1.2,0.79,copyImage);//Canny�����Ե

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
 * \�������ƣ�
 *   MakeGauss()
 *
 * \�������:
 *   double sigma         - ��˹�����ı�׼��
 *   double **pdKernel - ָ���˹���������ָ��
 *   int *pnWindowSize - ���ݵĳ���
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ���������������һ��һά�ĸ�˹�������������ݣ������ϸ�˹���ݵĳ���Ӧ
 *   �������޳��ģ�����Ϊ�˼���ļ򵥺��ٶȣ�ʵ�ʵĸ�˹����ֻ�������޳���
 *   pnWindowSize�������ݳ���
 *   
 *************************************************************************
 */
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize)
{
// ѭ�����Ʊ���
int i   ;

// ��������ĵ�
int nCenter;

// �����ĳһ�㵽���ĵ�ľ���
double  dDis  ; 

//double PI = 3.1415926;
// �м����
double  dValue; 
double  dSum  ;
dSum = 0 ; 

// ���鳤�ȣ����ݸ����۵�֪ʶ��ѡȡ[-3*sigma, 3*sigma]���ڵ����ݡ�
// ��Щ���ݻḲ�Ǿ��󲿷ֵ��˲�ϵ��
*pnWindowSize = 1 + 2 * ceil(3 * sigma);

// ����
nCenter = (*pnWindowSize) / 2;

// �����ڴ�
*pdKernel = new double[*pnWindowSize] ;

for(i=0; i< (*pnWindowSize); i++)
{
dDis = (double)(i - nCenter);
dValue = exp(-(1/2)*dDis*dDis/(sigma*sigma)) / (sqrt(2 * PI) * sigma );
(*pdKernel)[i] = dValue ;
dSum += dValue;
}

// ��һ��
for(i=0; i<(*pnWindowSize) ; i++)
{
(*pdKernel)[i] /= dSum;
}
}

/*************************************************************************
 *
 * \�������ƣ�
 *   GaussianSmooth()
 *
 * \�������:
 *   unsigned char * pUnchImg - ָ��ͼ�����ݵ�ָ��
 *   int nWidth - ͼ�����ݿ��
 *   int nHeight - ͼ�����ݸ߶�
 *   double dSigma - ��˹�����ı�׼��
 *   unsigned char * pUnchSmthdImg - ָ�򾭹�ƽ��֮���ͼ������
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   Ϊ����ֹ���������ø�˹�˲���ͼ������˲����˲��ȶ�x������У�Ȼ���
 *   y������С�
 *   
 *************************************************************************
 */
void GaussianSmooth(unsigned char *pUnchImg, int nWidth, int nHeight, 
double sigma, unsigned char * pUnchSmthdImg)
{
// ѭ�����Ʊ���
  int y;
int x;

int i;

// ��˹�˲��������鳤��

int nWindowSize;

//  ���ڳ��ȵ�1/2
int nHalfLen;   

// һά��˹�����˲���
double *pdKernel ;

// ��˹ϵ����ͼ�����ݵĵ��
double  dDotMul     ;

// ��˹�˲�ϵ�����ܺ�
double  dWeightSum     ;          
  
// �м����
double * pdTmp ;

// �����ڴ�
pdTmp = new double[nWidth*nHeight];

// ����һά��˹�����˲���
// MakeGauss(sigma, &dKernel, &nWindowSize);
MakeGauss(sigma, &pdKernel, &nWindowSize) ;

// MakeGauss���ش��ڵĳ��ȣ����ô˱������㴰�ڵİ볤
nHalfLen = nWindowSize / 2;

  // x��������˲�
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
dDotMul = 0;
dWeightSum = 0;
for(i=(-nHalfLen); i<=nHalfLen; i++)
{
// �ж��Ƿ���ͼ���ڲ�
if( (i+x) >= 0  && (i+x) < nWidth )
{
dDotMul += (double)pUnchImg[y*nWidth + (i+x)] * pdKernel[nHalfLen+i];
dWeightSum += pdKernel[nHalfLen+i];
}
}
pdTmp[y*nWidth + x] = dDotMul/dWeightSum ;
}
}

// y��������˲�
for(x=0; x<nWidth; x++)
{
for(y=0; y<nHeight; y++)
{
dDotMul = 0;
dWeightSum = 0;
for(i=(-nHalfLen); i<=nHalfLen; i++)
{
// �ж��Ƿ���ͼ���ڲ�
if( (i+y) >= 0  && (i+y) < nHeight )
{
dDotMul += (double)pdTmp[(y+i)*nWidth + x] * pdKernel[nHalfLen+i];
dWeightSum += pdKernel[nHalfLen+i];
}
}
pUnchSmthdImg[y*nWidth + x] = (unsigned char)(int)dDotMul/dWeightSum ;
}
}

// �ͷ��ڴ�
delete []pdKernel;
pdKernel = NULL ;

delete []pdTmp;
pdTmp = NULL;
}
/*************************************************************************
 *
 * \�������ƣ�
 *   DirGrad()
 *
 * \�������:
 *   unsigned char *pUnchSmthdImg - ������˹�˲����ͼ��
 *   int nWidht - ͼ����
 *   int nHeight       - ͼ��߶�
 *   int *pnGradX                         - x����ķ�����
 *   int *pnGradY                         - y����ķ�����
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ����������㷽���������õ�΢��������(-1 0 1) �� (-1 0 1)'(ת��)
 *   �����ʱ��Ա߽����ز��������⴦��
 *   
 *   
 *************************************************************************
 */
void DirGrad(unsigned char *pUnchSmthdImg, int nWidth, int nHeight,
 int *pnGradX , int *pnGradY)
{
// ѭ�����Ʊ���
int y ;
int x ;

// ����x����ķ��������ڱ߽�������˴�����ֹҪ���ʵ����س���
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
pnGradX[y*nWidth+x] = (int) ( pUnchSmthdImg[y*nWidth+min1(nWidth-1,x+1)]  
          - pUnchSmthdImg[y*nWidth+max1(0,x-1)]     );
}
}

// ����y����ķ��������ڱ߽�������˴�����ֹҪ���ʵ����س���
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
 * \�������ƣ�
 *   GradMagnitude()
 *
 * \�������:
 *   int *pnGradX                         - x����ķ�����
 *   int *pnGradY                         - y����ķ�����
 *   int nWidht - ͼ����
 *   int nHeight       - ͼ��߶�
 *   int *pnMag                           - �ݶȷ���   
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ����������÷����������ݶȷ��ȣ���������DirGrad��������Ľ��
 *   
 *************************************************************************
 */
void GradMagnitude(int *pnGradX, int *pnGradY, int nWidth, int nHeight, int *pnMag)
{

// ѭ�����Ʊ���
int y ;
int x ;

// �м����
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
 * \�������ƣ�
 *   NonmaxSuppress()
 *
 * \�������:
 *   int *pnMag                - �ݶ�ͼ
 *   int *pnGradX  - x����ķ����� 
 *   int *pnGradY              - y����ķ�����
 *   int nWidth                - ͼ�����ݿ��
 *   int nHeight               - ͼ�����ݸ߶�
 *   unsigned char *pUnchRst   - ����NonmaxSuppress�����Ľ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ��ֹ�ݶ�ͼ�зǾֲ���ֵ������ء�
 *   
 *************************************************************************
 */
void NonmaxSuppress(int *pnMag, int *pnGradX, int *pnGradY, int nWidth, 
int nHeight, unsigned char *pUnchRst)
{
// ѭ�����Ʊ���
int y ;
int x ;
int nPos;

// x�����ݶȷ���
int gx  ;
int gy  ;

// ��ʱ����
int g1, g2, g3, g4 ;
double weight  ;
double dTmp1   ;
double dTmp2   ;
double dTmp    ;

// ����ͼ���Ե����Ϊ�����ܵı߽��
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

// �����ǰ���ص��ݶȷ���Ϊ0�����Ǳ߽��
if(pnMag[nPos] == 0 )
{
pUnchRst[nPos] = 0 ;
}
else
{
// ��ǰ���ص��ݶȷ���
dTmp = pnMag[nPos] ;

// x��y������
gx = pnGradX[nPos]  ;
gy = pnGradY[nPos]  ;

// ���������y������x������˵�������ķ�����ӡ�������y������
if (abs(gy) > abs(gx)) 
{
// �����ֵ�ı���
weight = fabs(float(gx))/fabs(float(gy)); 

g2 = pnMag[nPos-nWidth] ; 
g4 = pnMag[nPos+nWidth] ;

// ���x��y��������ķ������ķ�����ͬ
// C�ǵ�ǰ���أ���g1-g4��λ�ù�ϵΪ��
// g1 g2 
//  C         
//  g4 g3 
if (gx*gy > 0) 
{  
g1 = pnMag[nPos-nWidth-1] ;
g3 = pnMag[nPos+nWidth+1] ;
} 

// ���x��y��������ķ������ķ����෴
// C�ǵ�ǰ���أ���g1-g4��λ�ù�ϵΪ��
//    g2 g1
//  C         
// g3 g4  
else 
{ 
g1 = pnMag[nPos-nWidth+1] ;
g3 = pnMag[nPos+nWidth-1] ;
} 
}

// ���������x������y������˵�������ķ�����ӡ�������x����
// ����ж���������x������y������ȵ����
else
{
// �����ֵ�ı���
weight = fabs(float(gy))/fabs(float(gx)); 

g2 = pnMag[nPos+1] ; 
g4 = pnMag[nPos-1] ;

// ���x��y��������ķ������ķ�����ͬ
// C�ǵ�ǰ���أ���g1-g4��λ�ù�ϵΪ��
// g3   
// g4 C g2       
//       g1
if (gx*gy > 0) 
{ 
g1 = pnMag[nPos+nWidth+1] ;
g3 = pnMag[nPos-nWidth-1] ;
} 
// ���x��y��������ķ������ķ����෴
// C�ǵ�ǰ���أ���g1-g4��λ�ù�ϵΪ��
//      g1
// g4 C g2       
//  g3     
else 
{ 
g1 = pnMag[nPos-nWidth+1] ;
g3 = pnMag[nPos+nWidth-1] ;
}
}

// ��������g1-g4���ݶȽ��в�ֵ
{
dTmp1 = weight*g1 + (1-weight)*g2 ;
dTmp2 = weight*g3 + (1-weight)*g4 ;

// ��ǰ���ص��ݶ��Ǿֲ������ֵ
// �õ�����Ǹ��߽��
if(dTmp>=dTmp1 && dTmp>=dTmp2)
{
pUnchRst[nPos] = 128 ;
}
else
{
// �������Ǳ߽��
pUnchRst[nPos] = 0 ;
}
}
} //else
} // for

}
} 
/*************************************************************************
 *
 * \�������ƣ�
 *   EstimateThreshold()
 *
 * \�������:
 *   int *pnMag               - �ݶȷ���ͼ
 *  int nWidth               - ͼ�����ݿ��
 *  int nHeight              - ͼ�����ݸ߶�
 *   int *pnThdHigh           - ����ֵ
 *   int *pnThdLow            - ����ֵ
 *  double dRatioLow         - ����ֵ�͸���ֵ֮��ı���
 *  double dRatioHigh        - ����ֵռͼ�����������ı���
 *   unsigned char *pUnchEdge - ����non-maximum����������
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ����non-maximum����������pUnchEdge��ͳ��pnMag��ֱ��ͼ��ȷ����ֵ��
 *   ��������ֻ��ͳ��pUnchEdge�п���Ϊ�߽�����Щ���ء�Ȼ������ֱ��ͼ��
 *   ����dRatioHigh���ø���ֵ���洢��pnThdHigh������dRationLow�͸���ֵ��
 *   ���õ���ֵ���洢��*pnThdLow��dRatioHigh��һ�ֱ����������ݶ�С��
 *   *pnThdHigh��������Ŀռ��������Ŀ�ı�����dRationLow����*pnThdHigh
 *   ��*pnThdLow�ı��������������canny�㷨��ԭ������߸�����һ�����䡣
 *
 *************************************************************************
 */
void EstimateThreshold(int *pnMag, int nWidth, int nHeight, int *pnThdHigh,int *pnThdLow, 
 unsigned char * pUnchEdge, double dRatioHigh, double dRationLow) 
{ 
// ѭ�����Ʊ���
int y;
int x;
int k;

// ������Ĵ�С���ݶ�ֵ�ķ�Χ�йأ�������ñ�������㷨����ô�ݶȵķ�Χ���ᳬ��pow(2,10)
int nHist[1024] ;

// ���ܵı߽���Ŀ
int nEdgeNb     ;

// ����ݶ�ֵ
int nMaxMag     ;

int nHighCount  ;

nMaxMag = 0     ; 

// ��ʼ��
for(k=0; k<1024; k++) 
{
nHist[k] = 0; 
}

// ͳ��ֱ��ͼ��Ȼ������ֱ��ͼ������ֵ
for(y=0; y<nHeight; y++)
{
for(x=0; x<nWidth; x++)
{
// ֻ��ͳ����Щ�����Ǳ߽�㣬���һ�û�д����������
if(pUnchEdge[y*nWidth+x]==128)
{
nHist[ pnMag[y*nWidth+x] ]++;
}
}
}

nEdgeNb = nHist[0]  ;
nMaxMag = 0         ;
// ͳ�ƾ����������ֵ��ֹ(non-maximum suppression)�����ж�������
for(k=1; k<1024; k++)
{
if(nHist[k] != 0)
{
// ����ݶ�ֵ
nMaxMag = k;
}

// �ݶ�Ϊ0�ĵ��ǲ�����Ϊ�߽���
// ����non-maximum suppression���ж�������
nEdgeNb += nHist[k];
}

// �ݶȱȸ���ֵ*pnThdHighС�����ص�����Ŀ
nHighCount = (int)(dRatioHigh * nEdgeNb +0.5);

k = 1;
nEdgeNb = nHist[1];

// �������ֵ
while( (k<(nMaxMag-1)) && (nEdgeNb < nHighCount) )
{
k++;
nEdgeNb += nHist[k];
}

// ���ø���ֵ
*pnThdHigh = k ;

// ���õ���ֵ
*pnThdLow  = (int)((*pnThdHigh) * dRationLow+ 0.5);
}

/*************************************************************************
 *
 * \�������ƣ�
 *   TraceEdge()
 *
 * \�������:
 *   int    x - ��������x���� 
 *   int    y - ��������y����
 *   int nLowThd - �ж�һ�����Ƿ�Ϊ�߽��ĵ���ֵ
 *   unsigned char *pUnchEdge - ��¼�߽��Ļ�����
 *   int *pnMag               - �ݶȷ���ͼ
 *   int nWidth               - ͼ�����ݿ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �ݹ����  
 *   ��(x,y)������������б߽��ĸ��٣�����ֻ����pUnchEdge��û�д�����
 *   �����Ǳ߽�����Щ����(=128),����ֵΪ0�����õ㲻�����Ǳ߽�㣬����ֵ
 *   Ϊ255�����õ��Ѿ�������Ϊ�߽�㣬�����ٿ���
 *   
 *   
 *************************************************************************
 */
void TraceEdge (int y, int x, int nLowThd, unsigned char *pUnchEdge, int *pnMag, int nWidth) 
{ 
// ��8�������ؽ��в�ѯ
int xNb[8] = {1, 1, 0,-1,-1,-1, 0, 1} ;
int yNb[8] = {0, 1, 1, 1,0 ,-1,-1,-1} ;

int yy ;
int xx ;

int k  ;

for(k=0; k<8; k++)
{
yy = y + yNb[k] ;
xx = x + xNb[k] ;
// ���������Ϊ���ܵı߽�㣬��û�д����
// �����ݶȴ�����ֵ
if(pUnchEdge[yy*nWidth+xx] == 128  && pnMag[yy*nWidth+xx]>=nLowThd)
{
// �Ѹõ����ó�Ϊ�߽��
pUnchEdge[yy*nWidth+xx] = 255 ;

// �Ըõ�Ϊ���Ľ��и���
TraceEdge(yy, xx, nLowThd, pUnchEdge, pnMag, nWidth);
}
}
} 


/*************************************************************************
 *
 * \�������ƣ�
 *   Hysteresis()
 *
 * \�������:
 *   int *pnMag               - �ݶȷ���ͼ
 *  int nWidth               - ͼ�����ݿ��
 *  int nHeight              - ͼ�����ݸ߶�
 *  double dRatioLow         - ����ֵ�͸���ֵ֮��ı���
 *  double dRatioHigh        - ����ֵռͼ�����������ı���
 *   unsigned char *pUnchEdge - ��¼�߽��Ļ�����
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ������ʵ�����ơ��������󡱵�һ�����ܣ�Ҳ���ǣ��ȵ���EstimateThreshold
 *   �����Ծ���non-maximum����������pUnchSpr����һ������ֵ��Ȼ���ж�
 *   pUnchSpr�п��ܵı߽�����(=128)���ݶ��ǲ��Ǵ��ڸ���ֵnThdHigh�������
 *   ����ֵ�󣬸õ㽫��Ϊһ���߽����㣬����TraceEdge�������Ѷ�Ӧ�ñ߽�
 *   �����������ҳ�������󣬵������������ʱ�������������û�б���־��
 *   �߽�㣬��ô��һ�����Ǳ߽�㡣
 *   
 *************************************************************************
 */
void Hysteresis(int *pnMag, int nWidth, int nHeight, double dRatioLow, 
double dRatioHigh, unsigned char *pUnchEdge)
{
// ѭ�����Ʊ���
int y;
int x;

int nThdHigh ;
int nThdLow  ;

int nPos;

// ����TraceEdge��Ҫ�ĵ���ֵ���Լ�Hysteresis����ʹ�õĸ���ֵ
EstimateThreshold(pnMag, nWidth, nHeight, &nThdHigh, 
               &nThdLow, pUnchEdge,dRatioHigh, dRatioLow);

  // ���ѭ������Ѱ�Ҵ���nThdHigh�ĵ㣬��Щ�㱻���������߽�㣬Ȼ����
// TraceEdge���������ٸõ��Ӧ�ı߽�
   for(y=0; y<nHeight; y++)
 {
      for(x=0; x<nWidth; x++)
{
nPos = y*nWidth + x ; 

// ����������ǿ��ܵı߽�㣬�����ݶȴ��ڸ���ֵ����������Ϊ
// һ���߽�����
if((pUnchEdge[nPos] == 128) && (pnMag[nPos] >= nThdHigh))
{
// ���øõ�Ϊ�߽��
pUnchEdge[nPos] = 255;
TraceEdge(y, x, nThdLow, pUnchEdge, pnMag, nWidth);
}
      }
   }

 // ��Щ��û�б�����Ϊ�߽��������Ѿ������ܳ�Ϊ�߽��
   for(y=0; y<nHeight; y++)
 {
 for(x=0; x<nWidth; x++)
 {
 nPos = y*nWidth + x ; 
 if(pUnchEdge[nPos] != 255)
 {
 // ����Ϊ�Ǳ߽��
 pUnchEdge[nPos] = 0 ;
 }
 }
 }
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Canny()
 *
 * \�������:
 *   unsigned char *pUnchImage- ͼ������
 *  int nWidth               - ͼ�����ݿ��
 *  int nHeight              - ͼ�����ݸ߶�
 *   double sigma             - ��˹�˲��ı�׼����
 *  double dRatioLow         - ����ֵ�͸���ֵ֮��ı���
 *  double dRatioHigh        - ����ֵռͼ�����������ı���
 *   unsigned char *pUnchEdge - canny���Ӽ����ķָ�ͼ
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   canny�ָ����ӣ�����Ľ��������pUnchEdge�У��߼�1(255)��ʾ�õ�Ϊ
 *   �߽�㣬�߼�0(0)��ʾ�õ�Ϊ�Ǳ߽�㡣�ú����Ĳ���sigma��dRatioLow
 *   dRatioHigh������Ҫָ���ġ���Щ������Ӱ��ָ��߽����Ŀ�Ķ���
 *************************************************************************
 */
void Canny(unsigned char *pUnchImage, int nWidth, int nHeight, double sigma, double dRatioLow, double dRatioHigh, unsigned char *pUnchEdge)
{
// ������˹�˲����ͼ������
unsigned char * pUnchSmooth ;
  
// ָ��x��������ָ��
int * pnGradX ; 

// ָ��y��������ָ��
int * pnGradY ;

// �ݶȵķ���
int * pnGradMag ;

pUnchSmooth  = new unsigned char[nWidth*nHeight] ;
pnGradX      = new int [nWidth*nHeight]          ;
pnGradY      = new int [nWidth*nHeight]          ;
pnGradMag    = new int [nWidth*nHeight]          ;

// ��ԭͼ������˲�
GaussianSmooth(pUnchImage, nWidth, nHeight, sigma, pUnchSmooth) ;

// ���㷽����
DirGrad(pUnchSmooth, nWidth, nHeight, pnGradX, pnGradY) ;

// �����ݶȵķ���
GradMagnitude(pnGradX, pnGradY, nWidth, nHeight, pnGradMag) ;

// Ӧ��non-maximum ����
NonmaxSuppress(pnGradMag, pnGradX, pnGradY, nWidth, nHeight, pUnchEdge) ;

// Ӧ��Hysteresis���ҵ����еı߽�
Hysteresis(pnGradMag, nWidth, nHeight, dRatioLow, dRatioHigh, pUnchEdge);


// �ͷ��ڴ�
delete pnGradX      ;
pnGradX      = NULL ;
delete pnGradY      ;
pnGradY      = NULL ;
delete pnGradMag    ;
pnGradMag    = NULL ;
delete pUnchSmooth ;
pUnchSmooth  = NULL ;
}


