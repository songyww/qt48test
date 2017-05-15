#ifndef PYRAMID_CLASS1
#define PYRAMID_CLASS1

#include "ProcessBase.h"



/*
 *	@brief Pyramid该类中，将创建金字塔，读取金字塔等函数接口封装在内；
 */

class PyramidBase
{

public:

	//构造函数，对成员变量等进行初始化
	PyramidBase()
	{
		//为了支持中文路径，添加下面代码
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
		//注册栅格驱动
		GDALAllRegister();
	}
	//析构函数
	~PyramidBase(){}

public:
	//下面几个变量是有关输入图像的信息，这些信息在CheckPyramid( )函数中进行初始化；
	const char* InFilePath ;		//该变量用于存放读入的文件路径
	GDALDataset* InFile;			//该变量用于存储读入的文件数据
	int iBandCount,iOverViewCount;	//iBandCount中存放输入文件的波段值，iOverViewCount中存放当前波段中金字塔的层数；
	int iWidth,iHeight;				//iWidth：输入图像的宽；iHeight:输入图像的高
	const char* InProjectionRef ;	//InProjectionRef：图像的投影信息
	double InGeotransform[6];		//输入图像的变换参数
	
	GDALRasterBand* InRasterBand;	//输入图像的第一个波段；用以获取金字塔层数以及大小等信息；
	GDALRasterBand* InPyramidBand;	//输入图像第一个波段的某一层金字塔图像；用以后面读取某一层时的参数设置；
	GDALDriverH hDriver ;			//获取图像驱动
	const char* InFormat;			//输入图像的格式
	const char* Path ;
	int iPixelNum, iTopNum, iCurNum;
	
	

	//该函数用于将文件数据读入数据集汇总，并检查文件是否存在金字塔
	bool CheckPyramid( );
	
	
	//该函数实现GDAL构建金字塔
	bool CreatePyramid();
	

	//定义用于读取金字塔某一层的函数，以及读取时的图像块的设置；m:将图像分m次；n表示读取第几层金字塔
	void ReadPyramidFile(int m, int n);
	
	//该函数实现a的b次方
	int p_pow(int a, int b);
	

};










#endif