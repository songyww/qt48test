/*
 *	@brief Pyramid���Ա������ʵ��
 */

#include "Pyramid_Class.h"

bool PyramidBase::CheckPyramid()
{
	InFile = (GDALDataset*)GDALOpen(InFilePath, GA_ReadOnly);		//��·���е��ļ����뵽���ݼ���
	//�ж�ͼ���Ƿ�������ݼ���
	if (InFile == NULL)
	{
		printf("��ͼ��ʧ�ܣ�����ͼ���Ƿ���ڻ��ļ��Ƿ���ͼ���ļ���");
		return false;
	}
	iBandCount = InFile->GetRasterCount();		//��ʼ������ͼ��Ĳ�����
	InRasterBand = InFile->GetRasterBand(1);		//��ʼ������ͼ��ĵ�һ�����Σ����Ժ����ȡ����������Ϣ
	iWidth = InFile->GetRasterXSize();		//��ȡ����ͼ����X����Ĵ�С
	iHeight = InFile->GetRasterYSize();		//��ȡ����ͼ�����Y����Ĵ�С
	InProjectionRef = InFile->GetProjectionRef();		//��ȡ����ͼ���ͶӰ��Ϣ
	InFile->GetGeoTransform(InGeotransform);		//��ȡ����ͼ��ı任����
	hDriver = GDALGetDatasetDriver(InFile);			//��ȡͼ������
	InFormat = GDALGetDriverShortName(hDriver);		//��ȡͼ������������
	iPixelNum = iWidth * iHeight;		//����ͼ��������Ԫ����
	iCurNum = iPixelNum / 4;
	iOverViewCount = InRasterBand->GetOverviewCount();
	//�����ж��ļ����Ƿ��н�����,��������н���������iOverViewCount=0
	if ( iOverViewCount == 0 )	//���������н��������򷵻���Ϣ��
	{
		printf("ͼ��û�д����������ļ����봴����������");
		CreatePyramid();
		InRasterBand = InFile->GetRasterBand(1);
		iOverViewCount = InRasterBand->GetOverviewCount();
		return FALSE;
		
	}
	else
	{
		printf("ͼ���Ѿ�������������");
		return TRUE;
	}
		
	

		//��ȡ����ͼ���һ�����εĽ��������������Ժ����ж��Ƿ��н�����

}

bool PyramidBase::CreatePyramid()
{
	//iTopNum = 4096;		//�����������С��64*64
	iTopNum = 65536;
	int anLevels[1024] ={ 0 };
	int nLevelCount = 0;		//����������

	//���ȳ�ʼ��һ����������
	CConsoleProcess *pProcess = new CConsoleProcess;

	//���濪ʼ����������
	if (pProcess != NULL)  
	{  
		pProcess->SetMessage("����������");  

	} 


	//����һ�䣬���ô����Ľ������ļ�������
	CPLSetConfigOption("USE_RRD","NO");		//��ΪNO���򴴽�.ovr��ʽ�Ľ���������ΪYES���򴴽�.aus��ʽ�Ľ�����

	//����ļ���Erdas��img����PCI��pix��ʽ�������ڽ������������Ĵ����������
	if (EQUAL(InFormat, "HFA") || EQUAL(InFormat,"PCIDSK"))
	{
		GDALClose(InFile);
		InFile = (GDALDataset*)GDALOpen(InFilePath, GA_Update);
		if (InFile == NULL)
		{
			printf("��ͼ��ʧ�ܣ�����ͼ���Ƿ���ڻ��ļ��Ƿ���ͼ���ļ���");
			return false;
		}
	}


	//���濪ʼ����������
	do    //����������������ӵڶ���������  
	{  
		anLevels[nLevelCount] = static_cast<int>(pow(2.0, nLevelCount+2));  
		nLevelCount ++;  
		iCurNum /= 4;  
	} while (iCurNum > iTopNum); 

	const char      *pszResampling = "nearest"; //������ʽ  
	GDALProgressFunc pfnProgress = GDALTermProgress;//������  

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
		pProcess->SetMessage("������������ɣ�");  

	return true;  
}


int PyramidBase::p_pow(int a,int b)//�ú���ʵ��a��b�η�
{
	int c = 1;
	for(int i = 0;i < b;i++)
	{
		c = c*a;
	}
	return c;

}

//�������ڶ�ȡ������ĳһ��ĺ������Լ���ȡʱ��ͼ�������ã�m:��ͼ���m�Σ�n��ʾ��ȡ�ڼ��������
void PyramidBase::ReadPyramidFile(int m, int n)
{
	//�����ȡָ����ʽ�����������ڴ���ָ����ʽ��ͼ��,InFormatΪǰ���Ѿ���ȡ������ͼ�����������
	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(InFormat);

	/*
	 *	@brief ��������ļ���·����ͶӰ��Ϣ���Լ��任����
	 */
	char filepath[1024];
	sprintf(filepath,"%s%d%s%d%s",Path,m,"_",n,".tif");
	const char* OutFilepath = filepath;
	InPyramidBand = InRasterBand->GetOverview(n);			//InPyramidBand�д������ͼ���һ�����ε�n�����������Ҫ���г�ʼ��
	GDALDataset* OutFile = poDriver->Create(OutFilepath, InPyramidBand->GetXSize(),InPyramidBand->GetYSize(),iBandCount, GDT_Byte, NULL ) ;
	OutFile->SetProjection(InProjectionRef);
	OutFile->SetGeoTransform(InGeotransform);

	//�ֲ��Σ��ֿ��ȡ�ļ�
	int nXBlocks, nYBlocks, nXBlockSize, nYBlockSize;//nXBlocks |nYBlocks ��XY����ֿ����Ŀ��nXBlockSize, nYBlockSize���ֵĿ���xy�����ϵĴ�С
	int iXBlock, iYBlock;
	GByte *pabyData;//���ݷֵĿ�Ĵ�СΪ�û��������Ӧ�Ŀռ�

	//���ü���ֿ����Ŀ���������Ϊm
	nXBlocks = p_pow(2,m);//����x����ֵĿ���
	nYBlocks = nXBlocks;//xy����ֵĿ���һ����

	for ( int i = 1; i <= iBandCount; i++ )
	{
		InPyramidBand = InFile->GetRasterBand(i)->GetOverview(n);	//����Ĳ���nΪ��ȡ��һ�������
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