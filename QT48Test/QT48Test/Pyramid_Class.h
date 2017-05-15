#ifndef PYRAMID_CLASS1
#define PYRAMID_CLASS1

#include "ProcessBase.h"



/*
 *	@brief Pyramid�����У�����������������ȡ�������Ⱥ����ӿڷ�װ���ڣ�
 */

class PyramidBase
{

public:

	//���캯�����Գ�Ա�����Ƚ��г�ʼ��
	PyramidBase()
	{
		//Ϊ��֧������·��������������
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
		//ע��դ������
		GDALAllRegister();
	}
	//��������
	~PyramidBase(){}

public:
	//���漸���������й�����ͼ�����Ϣ����Щ��Ϣ��CheckPyramid( )�����н��г�ʼ����
	const char* InFilePath ;		//�ñ������ڴ�Ŷ�����ļ�·��
	GDALDataset* InFile;			//�ñ������ڴ洢������ļ�����
	int iBandCount,iOverViewCount;	//iBandCount�д�������ļ��Ĳ���ֵ��iOverViewCount�д�ŵ�ǰ�����н������Ĳ�����
	int iWidth,iHeight;				//iWidth������ͼ��Ŀ�iHeight:����ͼ��ĸ�
	const char* InProjectionRef ;	//InProjectionRef��ͼ���ͶӰ��Ϣ
	double InGeotransform[6];		//����ͼ��ı任����
	
	GDALRasterBand* InRasterBand;	//����ͼ��ĵ�һ�����Σ����Ի�ȡ�����������Լ���С����Ϣ��
	GDALRasterBand* InPyramidBand;	//����ͼ���һ�����ε�ĳһ�������ͼ�����Ժ����ȡĳһ��ʱ�Ĳ������ã�
	GDALDriverH hDriver ;			//��ȡͼ������
	const char* InFormat;			//����ͼ��ĸ�ʽ
	const char* Path ;
	int iPixelNum, iTopNum, iCurNum;
	
	

	//�ú������ڽ��ļ����ݶ������ݼ����ܣ�������ļ��Ƿ���ڽ�����
	bool CheckPyramid( );
	
	
	//�ú���ʵ��GDAL����������
	bool CreatePyramid();
	

	//�������ڶ�ȡ������ĳһ��ĺ������Լ���ȡʱ��ͼ�������ã�m:��ͼ���m�Σ�n��ʾ��ȡ�ڼ��������
	void ReadPyramidFile(int m, int n);
	
	//�ú���ʵ��a��b�η�
	int p_pow(int a, int b);
	

};










#endif