
#ifndef PROCESS_H
#define  PROCESS_H
#include "ximage.h"
#undef min
#undef max

#include "cxcore.h"

//#include "stdafx.h"
#include <vector>
#include <cv.h>
#include <highgui.h>
#include"qstring.h"
using namespace std;

enum feature_match_type
{
	FEATURE_FWD_MATCH,
	FEATURE_BCK_MATCH,
	FEATURE_MDL_MATCH,
};

LPBITMAPINFO  CtreateMapInfo(IplImage* workImg, int flag);
int  imageClone(IplImage* pi, IplImage** ppo);
//double gsl_sf_choose(unsigned int n, unsigned int m);
IplImage* convert_to_gray8( IplImage* img );
CvMat* GetH3(vector<int>& ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints);
CvMat* ransac_xform3( vector<int>& ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
	int m, double p_badxform, double err_tol);
static __inline void release_mem3( CvPoint2D64f* pts1, CvPoint2D64f* pts2);
static int find_consensus3( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
	CvMat* M, double err_tol,vector<int>& inliers_ptpairs);
static	double homog_xfer_err3( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H );
static	CvPoint2D64f persp_xform_pt4( CvPoint2D64f pt, CvMat* T );
static void extract_corresp_pts3( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts );
static	void draw_ransac_sample3( vector<int> ptpairs,vector<int>& sample_ptpairs);
static int calc_min_inliers3( int n, int m, double p_badsupp, double p_badxform );
double gsl_sf_choose3(unsigned int n, unsigned int m);
static CvMat* lsq_homog3( CvPoint2D64f* pts, CvPoint2D64f* mpts, int n );
double GetRMSE3(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H);
CvPoint2D32f persp_xform_pt3( CvPoint2D32f pt, CvMat* T );
void findPairs3( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
	const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs );
int naiveNearestNeighbor3( const float* vec, int laplacian,
	const CvSeq* model_keypoints,
	const CvSeq* model_descriptors );
double compareSURFDescriptors3( const float* d1, const float* d2, double best, int length );
double GetRMSE2(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H);
CvPoint2D32f persp_xform_pt2( CvPoint2D32f pt, CvMat* T );
CvMat* GetH2(vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int &innernum);
static	CvMat* ransac_xform2( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, 
	int mtype, int m, double p_badxform, double err_tol,int &innernum);
void release_mem2( CvPoint2D64f* pts1,CvPoint2D64f* pts2);
int find_consensus2( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
	CvMat* M, double err_tol,vector<int>& inliers_ptpairs);
double homog_xfer_err2( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H );
CvPoint2D64f persp_xform_pt2( CvPoint2D64f pt, CvMat* T );
CvMat* lsq_homog2(CvPoint2D64f* pts, CvPoint2D64f* mpts, int n );
void extract_corresp_pts2( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts ,int DX,int DY);
void extract_corresp_pts2( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
	CvPoint2D64f** pts, CvPoint2D64f** mpts );
void draw_ransac_sample2( vector<int> ptpairs,vector<int>& sample_ptpairs);
int  calc_min_inliers2( int n, int m, double p_badsupp, double p_badxform );
void Canny(unsigned char *pUnchImage, int nWidth, int nHeight, double sigma, double dRatioLow, double dRatioHigh, unsigned char *pUnchEdge);
void Hysteresis(int *pnMag, int nWidth, int nHeight, double dRatioLow, 
	double dRatioHigh, unsigned char *pUnchEdge);
void TraceEdge (int y, int x, int nLowThd, unsigned char *pUnchEdge, int *pnMag, int nWidth) ;
void EstimateThreshold(int *pnMag, int nWidth, int nHeight, int *pnThdHigh,int *pnThdLow, 
	unsigned char * pUnchEdge, double dRatioHigh, double dRationLow) ;
void NonmaxSuppress(int *pnMag, int *pnGradX, int *pnGradY, int nWidth, 
	int nHeight, unsigned char *pUnchRst);
void GradMagnitude(int *pnGradX, int *pnGradY, int nWidth, int nHeight, int *pnMag);
void DirGrad(unsigned char *pUnchSmthdImg, int nWidth, int nHeight,
	int *pnGradX , int *pnGradY);
void GaussianSmooth(unsigned char *pUnchImg, int nWidth, int nHeight, 
	double sigma, unsigned char * pUnchSmthdImg);
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize);
bool ShapeSplit(CxImage m_img);
bool CuveSplit(CxImage m_img);
bool ColorSplit(CxImage m_img);
double Madhosi(QString strNameFile) ;
void ScanFiles(QString strNameFile) ;
void CariRecursive(QString strInitPath, QString strFileName);




void RGBToHSV(int r,int g,int b,double *h,double *s,double *v);
#endif