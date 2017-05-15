/*
 *	@brief Pyramid类成员函数的实现
 */

#include "Pyramid_Class.h"

bool PyramidBase::CheckPyramid()
{
	InFile = (GDALDataset*)GDALOpen(InFilePath, GA_ReadOnly);		//将路径中的文件读入到数据集中
	//判断图像是否读入数据集中
	if (InFile == NULL)
	{
		printf("打开图像失败，请检查图像是否存在或文件是否是图像文件！");
		return false;
	}
	iBandCount = InFile->GetRasterCount();		//初始化输入图像的波段数
	InRasterBand = InFile->GetRasterBand(1);		//初始化输入图像的第一个波段；用以后面获取金字塔的信息
	iWidth = InFile->GetRasterXSize();		//获取输入图像本身X方向的大小
	iHeight = InFile->GetRasterYSize();		//获取输入图像本身的Y方向的大小
	InProjectionRef = InFile->GetProjectionRef();		//获取输入图像的投影信息
	InFile->GetGeoTransform(InGeotransform);		//获取输入图像的变换参数
	hDriver = GDALGetDatasetDriver(InFile);			//获取图像驱动
	InFormat = GDALGetDriverShortName(hDriver);		//获取图像驱动的名称
	iPixelNum = iWidth * iHeight;		//输入图像中总像元个数
	iCurNum = iPixelNum / 4;
	iOverViewCount = InRasterBand->GetOverviewCount();
	//下面判断文件中是否含有金字塔,如果不含有金字塔，则iOverViewCount=0
	if ( iOverViewCount == 0 )	//表明不含有金字塔，则返回信息；
	{
		printf("图像没有创建金字塔文件，请创建金字塔！");
		CreatePyramid();
		InRasterBand = InFile->GetRasterBand(1);
		iOverViewCount = InRasterBand->GetOverviewCount();
		return FALSE;
		
	}
	else
	{
		printf("图像已经创建金字塔！");
		return TRUE;
	}
		
	

		//获取输入图像第一个波段的金字塔层数；用以后面判断是否有金字塔

}

bool PyramidBase::CreatePyramid()
{
	//iTopNum = 4096;		//顶层金字塔大小，64*64
	iTopNum = 65536;
	int anLevels[1024] ={ 0 };
	int nLevelCount = 0;		//金字塔级数

	//首先初始化一个进度条；
	CConsoleProcess *pProcess = new CConsoleProcess;

	//下面开始创建金字塔
	if (pProcess != NULL)  
	{  
		pProcess->SetMessage("创建金字塔");  

	} 


	//下面一句，设置创建的金字塔文件的类型
	CPLSetConfigOption("USE_RRD","NO");		//若为NO，则创建.ovr格式的金字塔；若为YES，则创建.aus格式的金字塔

	//如果文件是Erdas的img或者PCI的pix格式，创建内金字塔，其他的创建外金字塔
	if (EQUAL(InFormat, "HFA") || EQUAL(InFormat,"PCIDSK"))
	{
		GDALClose(InFile);
		InFile = (GDALDataset*)GDALOpen(InFilePath, GA_Update);
		if (InFile == NULL)
		{
			printf("打开图像失败，请检查图像是否存在或文件是否是图像文件！");
			return false;
		}
	}


	//下面开始构建金字塔
	do    //计算金字塔级数，从第二级到顶层  
	{  
		anLevels[nLevelCount] = static_cast<int>(pow(2.0, nLevelCount+2));  
		nLevelCount ++;  
		iCurNum /= 4;  
	} while (iCurNum > iTopNum); 

	const char      *pszResampling = "nearest"; //采样方式  
	GDALProgressFunc pfnProgress = GDALTermProgress;//进度条  

	/* -------------------------------------------------------------------- */  
	/*      Generate overviews.                                             */  
	/* -------------------------------------------------------------------- */  
	if (nLevelCount > 0 &&  
		GDALBuildOverviews( InFile,pszResampling, nLevelCount, anLevels,  
		0, NULL, pfnProgress, pProcess ) != CE_None )  
	{  
		if (pProcess != NULL)  

			return true ;  
	}  

	//iOverViewCount = InRasterBand->GetOverviewCount();
	/* -------------------------------------------------------------------- */  
	/*      Cleanup                                                         */  
	/* -------------------------------------------------------------------- */  
	//GDALClose((GDALDatasetH)InFile);  
	//GDALDestroyDriverManager();  

	if (pProcess != NULL)  
		pProcess->SetMessage("创建金字塔完成！");  

	return true;  
}


int PyramidBase::p_pow(int a,int b)//该函数实现a的b次方
{
	int c = 1;
	for(int i = 0;i < b;i++)
	{
		c = c*a;
	}
	return c;

}

//定义用于读取金字塔某一层的函数，以及读取时的图像块的设置；m:将图像分m次；n表示读取第几层金字塔
void PyramidBase::ReadPyramidFile(int m, int n)
{
	//下面获取指定格式的驱动，用于创建指定格式的图像,InFormat为前面已经获取的输入图像的驱动名称
	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(InFormat);

	/*
	 *	@brief 设置输出文件的路径、投影信息、以及变换参数
	 */
	char filepath[1024];
	sprintf(filepath,"%s%d%s%d%s",Path,m,"_",n,".tif");
	const char* OutFilepath = filepath;
	InPyramidBand = InRasterBand->GetOverview(n);			//InPyramidBand中存放输入图像第一个波段第n层金字塔；需要进行初始化
	GDALDataset* OutFile = poDriver->Create(OutFilepath, InPyramidBand->GetXSize(),InPyramidBand->GetYSize(),iBandCount, GDT_Byte, NULL ) ;
	OutFile->SetProjection(InProjectionRef);
	OutFile->SetGeoTransform(InGeotransform);

	//分波段，分块读取文件
	int nXBlocks, nYBlocks, nXBlockSize, nYBlockSize;//nXBlocks |nYBlocks ：XY反向分块的数目；nXBlockSize, nYBlockSize：分的块在xy方向上的大小
	int iXBlock, iYBlock;
	GByte *pabyData;//根据分的块的大小为该缓存分配相应的空间

	//设置计算分块的数目；传入参数为m
	nXBlocks = p_pow(2,m);//计算x方向分的块数
	nYBlocks = nXBlocks;//xy方向分的快数一样多

	for ( int i = 1; i <= iBandCount; i++ )
	{
		InPyramidBand = InFile->GetRasterBand(i)->GetOverview(n);	//传入的参数n为读取那一层金字塔
		GDALRasterBand* OutBand = OutFile->GetRasterBand(i);
		iOverViewCount = InFile->GetRasterBand(i)->GetOverviewCount();
		CPLAssert( InPyramidBand->GetRasterDataType()  ==  GDT_Byte);
		nYBlockSize = InPyramidBand->GetYSize() / nYBlocks;
		nXBlockSize = InPyramidBand->GetXSize() / nXBlocks;
		pabyData = (GByte *)CPLMalloc( nXBlockSize * nYBlockSize );

		for ( iYBlock = 0;iYBlock < nYBlocks; iYBlock++ )
		{
			for ( iXBlock = 0; iXBlock < nXBlocks; iXBlock++ )
			{
				InPyramidBand->RasterIO(GF_Read, iXBlock *nXBlockSize,iYBlock*nYBlockSize,nXBlockSize,nYBlockSize,pabyData,nXBlockSize, nYBlockSize, GDT_Byte, 0,0);

				OutBand->RasterIO(GF_Write,iXBlock*nXBlockSize,iYBlock*nYBlockSize,nXBlockSize,nYBlockSize,pabyData,nXBlockSize,nYBlockSize, GDT_Byte,0,0);
			}

		}

	}

	/* -------------------------------------------------------------------- */  
	/*      Cleanup                                                         */  
	/* -------------------------------------------------------------------- */  
	//GDALClose((GDALDatasetH)InFile);  
	//GDALDestroyDriverManager();  


}