//surf.cpp:Csurf��ӿ��ļ�
#pragma once
#include "opencv\\cv.h"
#include "opencv\\highgui.h"
#include "opencv\\cxcore.h"
#include "opencv2\\stitching\\stitcher.hpp"
#include "opencv2\\calib3d\\calib3d.hpp"
#include "opencv2\\nonfree\\features2d.hpp"
#include "opencv2\\nonfree\\nonfree.hpp"
#include "opencv2\\imgproc\\imgproc_c.h"
#include "opencv2\\features2d\\features2d.hpp"
#include <vector>
#include"gsl.h"
using namespace std;


class Csurf
{
public:
	vector<CvSeq *> Keypoints;//������
	//��֮��������������Ϊ����ʱͼ�����У�����ÿ��ͼ���������ͱ�����KeyPoint[i]�У�
	vector<CvSeq *> Descriptors;//������������
	vector<CvMat *> H;//����ͼƬ��ת������
	vector<int> ptpairs;//��ƥ�����=patpairs.size()/2��
	//�����������洢��01 13 24 �ȣ���һ��ͼ��0�͵ڶ���ͼ��1��һ��ƥ����
	CvMemStorage* storage;
	CvSURFParams params;//surf��׼�Ĳ���
private:
	double compareSURFDescriptors( const float* d1, const float* d2, double best, int length );
	int naiveNearestNeighbor( const float* vec, int laplacian, const CvSeq* model_keypoints,
		const CvSeq* model_descriptors );
	int naiveNearestNeighbor( const float* vec, int laplacian,const CvSeq* model_keypoints,
		const CvSeq* model_descriptors,vector<double>& dist);

	void release_mem( CvPoint2D64f* pts1, CvPoint2D64f* pts2);
	CvPoint2D64f persp_xform_pt( CvPoint2D64f pt, CvMat* T );
	double homog_xfer_err( CvPoint2D64f pt, CvPoint2D64f mpt, CvMat* H );
	int find_consensus( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype,
		CvMat* M, double err_tol,vector<int>& inliers_ptpairs);
	CvMat* lsq_homog( CvPoint2D64f* pts, CvPoint2D64f* mpts, int n );
	void extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
		CvPoint2D64f** pts, CvPoint2D64f** mpts ,int DX,int DY);
	void extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
		CvPoint2D64f** pts, CvPoint2D64f** mpts);
	void extract_corresp_pts( vector<int> &ptpairs0,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int m, int mtype,
		CvPoint2D64f** pts, CvPoint2D64f** mpts,CvMat *H0);
	void draw_ransac_sample( vector<int> ptpairs,vector<int>& sample_ptpairs,unsigned int seed);
	int calc_min_inliers( int n, int m, double p_badsupp, double p_badxform );

public:
	Csurf(int num);
	Csurf();
	~Csurf();
	CvMat* ransac_xform(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
		int m, double p_badxform, double err_tol,int DX,int DY);
	CvMat* ransac_xform(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, 
		int m, double p_badxform, double err_tol,CvMat *H0);
	CvPoint2D32f persp_xform_pt0( CvPoint2D32f pt, CvMat* T );
	void findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, 
		const CvSeq* imageDescriptors, vector<int>& ptpairs );
	void findPairs( const CvSeq* objectKeypoints,const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, 
		const CvSeq* imageDescriptors, vector<int>& ptpairs0,vector<int>& ptpairs1 );
	void findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints,
		const CvSeq* imageDescriptors, vector<int>& ptpairs,vector<double>& dist);
	CvMat* GetH(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,CvMat *H0);
	CvMat* GetH(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int DX,int DY);
	CvMat* Csurf::  GetH(vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int &innernum);
	CvMat* GetM(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,int DX,int DY);
	CvMat* GetM(vector<int> &ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints,CvMat *H0);
	void maxfive(vector<double> &d,vector<int> &ptpairs0);
	void gsotransform(const CvSeq* objectKeypoints,const CvSeq* imageKeypoints, vector<int>& ptpairs0,vector<int>& ptpairs);
	double GetRMSE(vector<int> ptpairs,CvSeq* CurrentKeypoints,CvSeq* PreKeypoints,CvMat* H,int DX,int DY);
	CvMat*   ransac_xform( vector<int> ptpairs,CvSeq *CurrentKeypoints,CvSeq *PreKeypoints, int mtype, int m, double p_badxform, double err_tol,int &innernum);
	void  draw_ransac_sample( vector<int> ptpairs,vector<int>& sample_ptpairs);
};
