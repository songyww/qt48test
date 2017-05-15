#include "qt48test.h"
#include<ArcSDK.h>
#include <QUuid>
#include"qmessagebox.h"
#include<qstring.h>
#include<qfiledialog.h>
#include "gdal_priv.h"
#include "prosess2.h"
#include "process1.h"
#include"qchar.h"
#include"qmatrix.h"
#include"qimage.h"
#include"qpainter.h"
#include"qtimer.h"
#include <QTime>

#include"LineSignature.h"
#include"ipoint.h"
#include"integral.h"
#include"surf11.h"
//#include"D:\vs PZ\GDAL\gdal201\include\gdal_alg.h"
//#include"D:\vs PZ\GDAL\gdal201\include\gdalwarper.h"

#include "gdal_alg_priv.h"
#include "gdalwarper.h"
#include"BuildPyramids.h"
#include "Pyramid_Class.h"
#include <QTextCodec>

#include <opencv2\opencv.hpp>
#include<opencv2\legacy\legacy.hpp> 
#include<opencv2\nonfree\features2d.hpp>
#include<opencv2\nonfree\nonfree.hpp>

//
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\features2d\features2d.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\calib3d\calib3d.hpp"
#include "opencv2\nonfree\nonfree.hpp"
#include "opencv2\imgproc\imgproc_c.h"
#include "opencv2\legacy\legacy.hpp"
#include "opencv2\legacy\compat.hpp"
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

using namespace std;
using namespace cv;

#define MAXNUM 100000

/*!成功执行*/
const int RE_SUCCESS		=	0;
/*!文件不存在*/
const int RE_FILENOTEXIST	=	1;
/*!文件格式不被支持*/
const int RE_FILENOTSUPPORT	=	2;
/*!图像数据类型不正确*/
const int RE_FILETYPEERROR	=	3;
/*!创建图像失败*/
const int RE_CREATEFAILED	=	4;
/*!输入参数错误*/
const int RE_PARAMERROR		=	5;
/*!其他错误*/
const int RE_FAILED			=	6;
/*!图像不存在公共区域*/
const int RE_NOSAMEEXTENT	=	7;
/*!用户取消操作*/
const int RE_USERCANCEL		=	8;
/*!文件已经被使用*/
const int RE_FILEISUESED	=	9;
/*!不支持的像素深度*/
const int RE_DEPTHNOTSUPPORT	=	10;
/*!波段数量不符合要求*/
const int RE_BANDCOUNTERROR		=	11;
/*!文件不存在投影*/
const int RE_NOPROJECTION		=	12;
/*!投影不一致*/
const int RE_PROJECTIONDIFF		=	13;
static double	       dfXRes = 0.0, dfYRes = 0.0;

double ww;
double hh;
int h0;
int w0;

double ColorPow;
double CuvePow;
double ShapePow;

double t1;
//double t2;
int num1;
double mese1;
vector<CvMat*> H_1;
//vector<CvMat*> H_2;


//extern 
double	m_ColorPow;
//extern 
double	m_CuvePow;
//extern 
double	m_ShapePow;
vector<double> xishu;
vector<QString> lujing;


CvSeq *objectKeypoints = 0, *objectDescriptors = 0;
CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
double t2;
int num2;
double mese2;
vector<CvMat*> H_2;

QString file_full, file_name, file_path; 
QString file_full2, file_name2, file_path2; 
QString fen1path;
QString fen2path;
//double rotate;

QT48Test::QT48Test(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	
/////////	ui.globecontrol->setControl("{3D389650-DC2D-4b05-9669-5EB732781BEB}");
	///ui.toolbarcontrol->setControl("{B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}");
///	ui.toccontrol->setControl("{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}");
	ui.mapcontrol->setControl("{C552EA94-6FBB-11d5-A9C1-00104BB6FC1C}");
	ui.mapcontrol_3->setControl("{C552EA94-6FBB-11d5-A9C1-00104BB6FC1C}");
	ui.mapcontrol_4->setControl("{C552EA94-6FBB-11d5-A9C1-00104BB6FC1C}");
	
////////	ui.maptoccontrol->setControl("{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}");
/////////	ui.maptoccontrol_3->setControl("{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}");
////	///ui.maptoccontrol_4->setControl("{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}");

	ui.maptoolbarcontrol->setControl("{B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}");
	ui.maptoolbarcontrol_3->setControl("{B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}");
	ui.maptoolbarcontrol_4->setControl("{B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}");

	//ui.scenecontrol->setControl("{DD4B8602-61F1-4528-82DF-8B5ACC862F84}");
	//ui.scenetoccontrol->setControl("{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}");
	//ui.scenetoolbarcontrol->setControl("{B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}");
	//ui.licensecontrol->setControl("{D7EAD71E-B663-4dce-82C7-AEE2793DF5F3}");
	
	//ui.m_pToolbarControl->SetBuddyControl(ui.m_pGlobeControl);
	//m_pToolbarControl->SetBuddyControl(m_pGlobeControl);
	//ui.toolbarcontrol->queryInterface(QUuid(IID_IToolbarControl),(void**)&m_pToolbarControl);
	ui.maptoolbarcontrol->queryInterface(QUuid(IID_IToolbarControl),(void**)&m_pToolbarControl2);
	ui.maptoolbarcontrol_3->queryInterface(QUuid(IID_IToolbarControl),(void**)&m_pToolbarControl2_3);
	ui.maptoolbarcontrol_4->queryInterface(QUuid(IID_IToolbarControl),(void**)&m_pToolbarControl2_4);

//	ui.globecontrol->queryInterface(QUuid(IID_IGlobeControl),(void**)&m_pGlobeControl);

	ui.mapcontrol->queryInterface(QUuid(IID_IMapControl3),(void**)&m_pMapControl);
	ui.mapcontrol_3->queryInterface(QUuid(IID_IMapControl3),(void**)&m_pMapControl_3);
	ui.mapcontrol_4->queryInterface(QUuid(IID_IMapControl3),(void**)&m_pMapControl_4);

///	ui.toccontrol->queryInterface(QUuid(IID_ITOCControl),(void**)&m_pTOCControl);
	//ui.maptoccontrol->queryInterface(QUuid(IID_ITOCControl),(void**)&m_pTOCControl2);
	//ui.maptoccontrol_3->queryInterface(QUuid(IID_ITOCControl),(void**)&m_pTOCControl2_3);
	//ui.maptoccontrol_4->queryInterface(QUuid(IID_ITOCControl),(void**)&m_pTOCControl2_4);

	//ui.scenecontrol->queryInterface(QUuid(IID_ISceneControl),(void**)& m_pSceneControl);
	//ui.scenetoolbarcontrol->queryInterface(QUuid(IID_IToolbarControl),(void**)&m_pToolbarControl3);
	//ui.scenetoccontrol->queryInterface(QUuid(IID_ITOCControl),(void**)&m_pTOCControl3);

	//m_pToolbarControl->SetBuddyControl(m_pGlobeControl);

	m_pToolbarControl2->SetBuddyControl(m_pMapControl);
	m_pToolbarControl2_3->SetBuddyControl(m_pMapControl_3);
	m_pToolbarControl2_4->SetBuddyControl(m_pMapControl_4);

//	m_pToolbarControl3->SetBuddyControl(m_pSceneControl);

	//m_pTOCControl->SetBuddyControl(m_pGlobeControl);

	//m_pTOCControl2->SetBuddyControl(m_pMapControl);
	//m_pTOCControl2_3->SetBuddyControl(m_pMapControl_3);
	//m_pTOCControl2_4->SetBuddyControl(m_pMapControl_4);

	//m_pTOCControl3->SetBuddyControl(m_pSceneControl);

	AddToolBarCommand(m_pToolbarControl2);
	AddToolBarCommand(m_pToolbarControl2_3);
	AddToolBarCommand(m_pToolbarControl2_4);
	//add_toolbar_items(m_pToolbarControl);
//	AddToolbarItems(m_pToolbarControl3);
}

QT48Test::~QT48Test()
{

}

void QT48Test::AddToolBarCommand(IToolbarControlPtr ipToolBarControl)

{

    CComVariant varTool;

    long itemindex;

 

    if (!ipToolBarControl)

        return;

 

    varTool = L"esriControlCommands.ControlsOpenDocCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsAddDataCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

 

   varTool = L"esriControlCommands.ControlsMapZoomInTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_TRUE, 0,

        esriCommandStyleIconOnly, &itemindex);

      

    

    varTool = L"esriControlCommands.ControlsMapZoomOutTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);
	
	varTool = L"esriControlCommands.ControlsMapRotateTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);
	
	varTool = L"esriControlCommands.ControlsMapClearMapRotationCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);


    varTool = L"esriControlCommands.ControlsMapZoomInFixedCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsMapZoomOutFixedCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsMapPanTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsMapFullExtentCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsMapZoomToLastExtentBackCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsMapZoomToLastExtentForwardCommand";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsSelectFeaturesTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);

    varTool = L"esriControlCommands.ControlsSelectTool";

    ipToolBarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,

        esriCommandStyleIconOnly, &itemindex);
	
	

}

void QT48Test::add_toolbar_items(IToolbarControlPtr pToolbar)
{
	CComVariant varTool;
	long itemIndex;

	if (!pToolbar) 
    return;

  varTool = L"esriGlobeCore.ControlsGlobeOpenDocCommand";
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);

   varTool = L"esriControlCommands.ControlsAddDataCommand";

    pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);

  varTool = L"esriGlobeCore.ControlsGlobeZoomInOutTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_TRUE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeFixedZoomInCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeFixedZoomOutCommand";
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobePanTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeFullExtentCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeNavigateTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeRotateForwardCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeRotateBackCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeRotateClockwiseCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeRotateCounterClockwiseCommand";
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSpinClockwiseCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSpinCounterClockwiseCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSpinFasterCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSpinSlowerCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSpinStopCommand"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeTargetCenterTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeTargetZoomTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeWalkTool"; 
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriGlobeCore.ControlsGlobeSelectFeaturesTool";
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriControlCommands.ControlsSelectTool";
  pToolbar->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                     esriCommandStyleIconOnly, &itemIndex);
}

void QT48Test::AddToolbarItems(IToolbarControlPtr g_ipToolbarControl)
{
  long itemIndex;
  CComVariant varTool;

  varTool = L"esri3DAnalyst.ControlsSceneOpenDocCommand";
  g_ipToolbarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                              esriCommandStyleIconOnly, &itemIndex);  
  varTool = L"esri3DAnalyst.ControlsSceneSceneToolbar";
  g_ipToolbarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                              esriCommandStyleIconOnly, &itemIndex);
  varTool = L"esriControlCommands.ControlsSelectTool";
  g_ipToolbarControl->AddItem(varTool, 0, -1, VARIANT_FALSE, 0,
                              esriCommandStyleIconOnly, &itemIndex);
}
void QT48Test::fenkuai()
{
	// TODO: 在此添加命令处理程序代码
	int m=0;
	int n=0;
	QString Gaodu=ui.height->text();
	QString Kuandu=ui.width->text();
	bool ok;
	h0=Gaodu.toInt(&ok,10);
    w0=Kuandu.toInt(&ok,10);
	

	//先将CString的m_strRawImageFilePath转成const char* m_dakaidetuxiang
	//QString m_dakaidetuxiang;
	QString dir_s=m_strFileName;
	const QByteArray text = dir_s.toLocal8Bit();
	const char *m_dakaidetuxiang = text.data();

   /*const size_t strsize=(m_strRawImageFilePath.GetLength()+1)*2; // 宽字符的长度;
    char* m_dakaidetuxiang= new char[strsize]; //分配空间;
    size_t sz=0;
    wcstombs_s(&sz,m_dakaidetuxiang,strsize,m_strRawImageFilePath,_TRUNCATE);
    int atoiato=atoi((const char*)m_dakaidetuxiang); // 字符串已经由原来的CString 转换成了 const char**/

	GDALAllRegister();
    GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(m_dakaidetuxiang, GA_ReadOnly);
	

    int datuWidth = pSrcDS->GetRasterXSize();
    int datuHeight=pSrcDS->GetRasterYSize();
	
	m=datuHeight/h0;
	n=datuWidth/w0;
	if(datuHeight%h0>0.5*h0)
		m++;
	if(datuWidth%w0>0.5*w0)
		n++;
	
	ww=((double)datuWidth)/((double)n);
	hh=((double)datuHeight)/((double)m);
	//int iDstWidth  = ww;
	//int iDstHeight = hh;

//////判断是否有文件夹，若有，清空文件夹，若没有，自动创建//////////////
    QDir *temp = new QDir;
	fen1path=file_path+"\\fen1";
    bool exist = temp->exists(fen1path);
    if(exist)
	{
		QDir d(fen1path);//删除文件夹，以免上次过程裁剪的图像加入到此次运行
		int p=d.count()-1;
		for(int q=0;q<=p;q++)
			d.remove(d[q]);
	
	}
        
    else
    {
        bool ok = temp->mkdir(fen1path);
    }
//////////////////////////////////////////////////

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			QString fen1name=fen1path+"\\%d %d.jpg";
			const QByteArray textfen1 = fen1name.toLocal8Bit();
	        const char *fen1name1 = textfen1.data();

			char name[100];
			char* bb;
			sprintf(name,fen1name1, i,j);
			bb=name;
			const char*bbb=bb;
			//int iStartX=j*ww;
			//int iStartY=i*hh;
			//int iSizeX=ww;
			//int iSizeY=hh;
			//const char* pszDstFile=bbb;
			//const char* pszFormat="GTiff";
			//IProcessIt* pPro=NULL;
            ImageCut(m_dakaidetuxiang,bbb,j*ww,i*hh,ww,hh,"GTiff");///////////////
		}

	}
	
	//QMessageBox::information(NULL, "Title", "Equal division finished!", QMessageBox::Yes, QMessageBox::Yes);
	GDALClose((GDALDatasetH)pSrcDS);
	
	return  ;

}

void QT48Test::ImageCut(const char* pszSrcFile, const char* pszDstFile, int iStartX, int iStartY, int iSizeX, int iSizeY,const char* pszFormat)
{

	        /*int iDstWidth  = ww;
	        int iDstHeight = hh;
	       double adfGeoTransform[6] = {0};
			GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(pszSrcFile, GA_ReadOnly);

			GDALDataType eDT = pSrcDS->GetRasterBand(1)->GetRasterDataType();
			int iBandCount = pSrcDS->GetRasterCount();

			pSrcDS->GetGeoTransform(adfGeoTransform);

	        // 计算裁切后的图像的左上角坐标	
			adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + iStartY*adfGeoTransform[2];
	        adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + iStartY*adfGeoTransform[5];

	        // 创建输出文件并设置空间参考和坐标信息
	        GDALDriver *poDriver = (GDALDriver *) GDALGetDriverByName(pszFormat);
	        GDALDataset *pDstDS = poDriver->Create(pszDstFile, iDstWidth, iDstHeight, iBandCount, eDT, NULL);
	        pDstDS->SetGeoTransform(adfGeoTransform);
	        pDstDS->SetProjection(pSrcDS->GetProjectionRef());

	        int *pBandMap = new int[iBandCount];
	        for (int i=0; i<iBandCount; i++)
		    pBandMap[i] = i+1;
			// 下面这里需要根据数据类型来判断，申请不同类型的缓存来进行处理，这里仅仅以8bit图像进行演示
			if (eDT == GDT_Byte)	// 如果是8bit图像
			{
		// 申请所有数据所需要的缓存，如果图像太大应该用分块处理
		    char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount];	

		    pSrcDS->RasterIO(GF_Read, iStartX, iStartY, iSizeX, iSizeY, pDataBuff, iSizeX, iSizeY, eDT, iBandCount, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write, 0, 0, iSizeX, iSizeY, pDataBuff, iSizeX, iSizeY, eDT, iBandCount, pBandMap, 0, 0, 0);

		    delete(pDataBuff);
	        }
	        else
	        {
		   // 其他类型的图像，与8bit类似，就是申请的缓存类型不同而已
			QMessageBox::information(NULL, "Title", "不支持该图像", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	         }

	        delete(pBandMap);
			GDALClose((GDALDatasetH)pDstDS);*/

		GDALAllRegister();

	GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(pszSrcFile, GA_ReadOnly);
	GDALDataType eDT = pSrcDS->GetRasterBand(1)->GetRasterDataType();

	int iBandCount = pSrcDS->GetRasterCount();

	// 根据裁切范围确定裁切后的图像宽高
	int iDstWidth  = iSizeX;
	int iDstHeight = iSizeY;

	double adfGeoTransform[6] = {0};
	pSrcDS->GetGeoTransform(adfGeoTransform);

	// 计算裁切后的图像的左上角坐标	
	//adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + iStartY*adfGeoTransform[2];
	//adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + iStartY*adfGeoTransform[5];

	// 创建输出文件并设置空间参考和坐标信息
	GDALDriver *poDriver = (GDALDriver *) GDALGetDriverByName(pszFormat);
	GDALDataset *pDstDS = poDriver->Create(pszDstFile, iDstWidth, iDstHeight, iBandCount, eDT, NULL);
	pDstDS->SetGeoTransform(adfGeoTransform);
	pDstDS->SetProjection(pSrcDS->GetProjectionRef());

	int *pBandMap = new int[iBandCount];
	for (int i=0; i<iBandCount; i++)
		pBandMap[i] = i+1;

	// 下面这里需要根据数据类型来判断，申请不同类型的缓存来进行处理，这里仅仅以8bit图像进行演示
	if (eDT == GDT_Byte)	// 如果是8bit图像
	{
		// 申请所有数据所需要的缓存，如果图像太大应该用分块处理
		char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount];	

		pSrcDS->RasterIO(GF_Read, iStartX, iStartY, iSizeX, iSizeY, pDataBuff, iSizeX, iSizeY, eDT, iBandCount, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, 0, iSizeX, iSizeY, pDataBuff, iSizeX, iSizeY, eDT, iBandCount, pBandMap, 0, 0, 0);

		delete(pDataBuff);
	}
	else
	{
		// 其他类型的图像，与8bit类似，就是申请的缓存类型不同而已
	}

	delete(pBandMap);

	GDALClose((GDALDatasetH)pSrcDS);
	GDALClose((GDALDatasetH)pDstDS);

	//if(pProcess != NULL)
	//	pProcess->SetMessage("裁切完成！");

	//return RE_SUCCESS;
	return  ;

}


void QT48Test::opentif()

{

		QFileInfo fi;		  
		file_full = QFileDialog::getOpenFileName(this,"open the first picture","E:\\test");  
		fi = QFileInfo(file_full);  
		file_name = fi.fileName();  
		file_path = fi.absolutePath(); 	
		m_strFileName=fi.absoluteFilePath();
	
		BSTR bstr_str;
       		
		bstr_str = SysAllocString(m_strFileName.utf16());
		
		QString dir1=m_strFileName;
		const QByteArray text = dir1.toLocal8Bit();
		const char *dakaidetuxiang1 = text.data();

		BuildPyramids(dakaidetuxiang1);
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);

			
		m_pMapControl->AddLayer(pLyr,0);
		
		IActiveViewPtr pActiveView(m_pMapControl);
			

		
        m_pMapControl->Refresh(esriViewAll);  
		
		

		GDALAllRegister();
		GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(dakaidetuxiang1, GA_ReadOnly);
		
		int Width01 = pSrcDS->GetRasterXSize();
		int Height01=pSrcDS->GetRasterYSize();

		GDALClose((GDALDatasetH)pSrcDS);
		
		if( (Width01<=2000)&&(Height01<=2000 ))
		{
			ui.width->setText("300");
			ui.height->setText("300");
		}
		else if( 2000<Width01 && 2000<Height01 )
		{
			ui.width->setText("1500");
			ui.height->setText("1500");
		}
		else
		{
		ui.width->setText("1500");
		ui.height->setText("1500");
		QMessageBox::information(NULL, "Title", "You Can Input the needed Value of Width and Height!", QMessageBox::Yes, QMessageBox::Yes);
		}
      
}


void QT48Test::opentif2()

{

	/*QFileDialog* fd = new QFileDialog(this);//创建对话框
	fd->resize(600,600);    //设置显示的大小
    fd->setFilter( "ALLfiles(*.*);;TIFFfile(*.tif)"); //设置文件过滤器
    fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    QStringList namelist ;  
    if( fd->exec() == QDialog::Accepted)  
    {  
       
		namelist=fd->selectedFiles();
		m_strFileName2=namelist.first();
       
		  BSTR bstr_str;
          bstr_str = SysAllocString(m_strFileName2.utf16());
           HRESULT hr;
		   IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			hr=pRasterLy->CreateFromFilePath(bstr_str);
			if(FAILED(hr))
				return;
			ILayerPtr pLyr(pRasterLy);
			m_pMapControl->AddLayer(pLyr,0);
			IActiveViewPtr pActiveView(m_pMapControl);
			//pActiveView->Refresh();


        } */
		
	    //m_ipGlobeControl->Load3dFile(L"D:\Shp\0101.tif");
		

	    QFileInfo fi;		  
		file_full = QFileDialog::getOpenFileName(this,"open the second picture",file_path);  
		fi = QFileInfo(file_full);  
		//file_name = fi.fileName();  
		file_path2 = fi.absolutePath(); 	
		m_strFileName2=fi.absoluteFilePath();

		
		


	
	
	
		BSTR bstr_str;
       		
		bstr_str = SysAllocString(m_strFileName2.utf16());

		QString dir2=m_strFileName2;
		const QByteArray text2 = dir2.toLocal8Bit();
		const char *dakaidetuxiang2 = text2.data();

		BuildPyramids(dakaidetuxiang2);
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);
			
		m_pMapControl_3->AddLayer(pLyr,0);
			
		IActiveViewPtr pActiveView(m_pMapControl_3);
			
        m_pMapControl_3->Refresh(esriViewAll);  

		
      
}

void QT48Test::caijian()
{
//得到打开的图像的宽度和高度

//HugeMemImage* pImage=NULL;
//int xiaotuWidth=pImage->m_nWidth1;
//int xiaotuWidth=pImage->GetWidth();
//GDALDataset *poSrcDS;
//int xiaotuWidth = poSrcDS->GetRasterXSize();

//int xiaotuHeight=pImage->m_nHeight1;
	QString Gaodu=ui.height->text();
	QString Kuandu=ui.width->text();
	bool ok;
	h0=Gaodu.toInt(&ok,10);
    w0=Kuandu.toInt(&ok,10);

    QString dir_s=m_strFileName2;
	const QByteArray text = dir_s.toLocal8Bit();
	const char *m_dakaidetuxiang2 = text.data();

GDALAllRegister();

GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(m_dakaidetuxiang2, GA_ReadOnly);
int xiaotuWidth = pSrcDS->GetRasterXSize();
int xiaotuHeight=pSrcDS->GetRasterYSize();

//////判断是否有文件夹，若有，清空文件夹，若没有，自动创建//////////////
    QDir *temp = new QDir;
    //bool exist = temp->exists("E:\\fen2");
	fen2path=file_path2+"\\fen2";
	 bool exist = temp->exists(fen2path);
    if(exist)
	{
		QDir d(fen2path);//删除文件夹，以免上次过程裁剪的图像加入到此次运行
		int p=d.count()-1;
		for(int q=0;q<=p;q++)
			d.remove(d[q]);
	
	}
        
    else
    {
        bool ok = temp->mkdir(fen2path);
    }
//////////////////////////////////////////////////
	QString fenb1name=fen2path+"\\b1.jpg";
	const QByteArray textfenb1 = fenb1name.toLocal8Bit();
	const char *fen1nameb1 = textfenb1.data();

	/*QStirng fenb2name=fen2path+"\\b2.jpg";
	const QByteArray textfenb2 = fenb2name.toLocal8Bit();
	const char fen1nameb2 = textfenb2.data();*/

	QString fenb4name=fen2path+"\\b4.jpg";
	const QByteArray textfenb4 = fenb4name.toLocal8Bit();
	const char *fen1nameb4 = textfenb4.data();
//IProcessIt* pPro1=NULL;
ImageCut(m_dakaidetuxiang2,fen1nameb1,0,0,w0,h0,"GTiff");

//IProcessIt* pPro2=NULL;
//ImageCut(m_dakaidetuxiang2,"E:\\fen2\\b2.jpg",xiaotuWidth-w0,0,w0,h0,"GTiff");

///////////////////////ImageCut(m_dakaidetuxiang2,fen2path+"\\b2.jpg",xiaotuWidth-w0,0,w0,h0,"GTiff");
//IProcessIt* pPro4=NULL;
ImageCut(m_dakaidetuxiang2,fen1nameb4,0,xiaotuHeight-h0,w0,h0,"GTiff");

//IProcessIt* pPro3=NULL;
//////////////ImageCut(m_dakaidetuxiang2,fen2path+"\\b3.jpg",xiaotuWidth-w0,xiaotuHeight-h0,w0,h0,"GTiff");

//AfxMessageBox("完成",MB_OK, 0);
//AfxMessageBox(_T("四个角裁剪完成"), MB_OKCANCEL | MB_ICONQUESTION);
//QMessageBox::information(NULL, "Title", "cut 4 finished", QMessageBox::Yes, QMessageBox::Yes);

GDALClose((GDALDatasetH)pSrcDS);

}

void QT48Test::clearlayer()
{
	long count;
	m_pMapControl->get_LayerCount(&count);
	for(long i=0;i<count;i++)
	{
	m_pMapControl->DeleteLayer(i);
	m_pMapControl->DeleteLayer(i);
	}
	m_pMapControl_3->get_LayerCount(&count);
	for(long i=0;i<count;i++)
	{
	m_pMapControl_3->DeleteLayer(i);
	m_pMapControl_3->DeleteLayer(i);
	}
	m_pMapControl_4->get_LayerCount(&count);
	for(long i=0;i<count;i++)
	{
	m_pMapControl_4->DeleteLayer(i);
	m_pMapControl_4->DeleteLayer(i);
	}
}

void QT48Test::Onspeed()
{
	// TODO: 在此添加命令处理程序代码
	/*
	///开始计时
	LARGE_INTEGER litmp;
    LONGLONG Qpart1,Qpart2,Useingtime;
    double dfMinus,dfFreq,dfTime;
    //获得CPU计时器的时钟频率
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值   
    Qpart1 = litmp.QuadPart; //开始计时*/

	
	cv::initModule_nonfree();
	/**********************得到小图像的特征**************************************/
    extern double	m_ColorPow;
    extern double	m_CuvePow;
    extern double	m_ShapePow;

    extern int m_KeyMainColorSig[111]; // 查询小图像的特征
    extern double m_KeyCuve[15];
    extern double m_KeyShape[8];
    extern int m_Color[111];//检索图像特征
    extern double m_Cuve[15];
    extern double m_Shape[8];
	const char* strsmall;
	
	CvMat* H;
	CvMat* Hh;
	CvMat h;
	CvMat* H1=&h;
	double a[9];
	double px,py;
	double sfx,sfy;
	double R11,R12,R21,R22,R13,R23,R33;
	double Rrotate;

	char time[20]={""};

	double t=(double)cvGetTickCount();//开始计时

    //strsmall="E:\\fen2\\b1.jpg";//大图的一
	fen1path=file_path+"\\fen1";
	fen2path=file_path2+"\\fen2";
	QDir *temp = new QDir;
	bool exist = temp->exists(fen2path);
    if(!exist)
	{
		QMessageBox::information(NULL, "Title", "Please cut the images!!!", QMessageBox::Ok, QMessageBox::Ok);
		return;
	
	}
        
	
	
	QString fen2b1name=fen2path+"\\b1.jpg";
	const QByteArray textfen2b1 = fen2b1name.toLocal8Bit();
	const char *fen2nameb1 = textfen2b1.data();
	strsmall=fen2nameb1;

	CxImage m_imgLoaded;
	
	m_imgLoaded.Load(strsmall);
	h0=m_imgLoaded.GetHeight();
	w0=m_imgLoaded.GetWidth();

   IplImage* img1111 = cvLoadImage(strsmall, 1);
	int k;
	for(k=0; k<111; k++)
	{
		m_KeyMainColorSig[k] = 0;
	}
	for(k=0; k<15; k++)
	{
		m_KeyCuve[k]=0;
	}
	for(k=0;k<8;k++)
	{
		m_KeyShape[k]=0;
	}

	ColorSplit(m_imgLoaded);//转换成HSI空间  颜色
	CuveSplit(m_imgLoaded);    //转换成梯度   纹理
	ShapeSplit(m_imgLoaded);   //利用canny求出边缘  形状

	for(k=0;k<111;k++)
		m_KeyMainColorSig[k] = m_Color[k];
	for(k=0; k<15; k++)
	{
		m_KeyCuve[k]=m_Cuve[k];
	}
	for(k=0;k<8;k++)
	{
		m_KeyShape[k]=m_Shape[k];
	}
	///以上是大图的一个子图B1的特征

	/*********************得到小图像的特征***************************************/
	/***********************************************************************/

	ColorPow=m_ColorPow;
	CuvePow=m_CuvePow;
	ShapePow=m_ShapePow;
	if (ColorPow==0&&CuvePow==0&&ShapePow==0)
	{
		ColorPow=1;
		CuvePow=1;
		ShapePow=1;
	}
	double plus = ColorPow + CuvePow + ShapePow;
	ColorPow /= plus;
	CuvePow /= plus;
	ShapePow /= plus;

	//////////////////////可以改成全局变量
	QString m_strBeginPath;		//开始路径
	QString m_strExtension;     //查找文件夹中的文件类型
	m_strExtension = "*.jpg";
	//m_strBeginPath = "E:\\fen1";
	m_strBeginPath =fen1path;

	CariRecursive(m_strBeginPath, m_strExtension);//检索出最相似的




	int number=xishu.size();
	int minNum=0;
	double zuixiao;
	zuixiao=xishu[0];
	for (int i=0;i<number;i++)////找到最小的系数
	{

		if(zuixiao>xishu[i])
		{
			zuixiao=xishu[i];
			minNum=i;
		}			

	}


	QString tp;
	tp=lujing[minNum];

	QString dir_s=tp;
	const QByteArray text = dir_s.toLocal8Bit();
	const char *tp1 = text.data();


	IplImage* temp1=cvLoadImage(tp1,1);//系数最小相似度最大？

	int len1=strlen(tp1);

	QCharRef aaa=tp[len1-7];
	QCharRef bbb=tp[len1-5];
	QChar aaaa(aaa);
	char aaaaa=aaaa.toAscii();
	QChar bbbb(bbb);
	char bbbbb=bbbb.toAscii();
	int mm=aaaaa-'0';
	int nn=bbbbb-'0';

	/*cvSetImageROI(img[0], cvRect(nn*ww, mm*hh, ww, hh) );*/

	IplImage* img1=convert_to_gray8(/*img[0]*/temp1);//找到的小图
	IplImage* img2=convert_to_gray8(img1111);//B1

	CvSeq *PreKeypoints3 = 0, *PreDescriptors3 = 0;
	CvSeq *CurrentKeypoints3 = 0, *CurrentDescriptors3 = 0;

	////////////////////
	CvMemStorage* storage2=cvCreateMemStorage(0);
	CvSURFParams params11 = cvSURFParams(1000, 0);

	cvExtractSURF( img1, 0, &PreKeypoints3, &PreDescriptors3, storage2, params11);
	cvExtractSURF( img2, 0, &CurrentKeypoints3, &CurrentDescriptors3, storage2, params11);

	vector<int>ptpairs2;
	findPairs3( CurrentKeypoints3, CurrentDescriptors3, PreKeypoints3, PreDescriptors3, ptpairs2 );
	
	
	num1=ptpairs2.size()/2;
	H = GetH3(ptpairs2,CurrentKeypoints3,PreKeypoints3);
	/*cvResetImageROI( img[0] );*/
	
	if(h0>=1000&&num1<80)////////////分块较大时可能会错误匹配、、、、、、、、
		H=0;
	
	if( H )
	{


		/*QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
         Qpart2 = litmp.QuadPart; //终止计时
	     dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
         dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
		 QString s = QString::number(dfTime,'f',0);
	     ui.bigtime->setText(s);*/
		t=(double)(cvGetTickCount()-t)/(cvGetTickFrequency()*1000*1000.);
		QString s = QString::number(t,'f',3);
	    ui.bigtime->setText(s);

		const QByteArray text11 = m_strFileName2.toLocal8Bit();
		const char *m_strFileName22 = text11.data();
		//IplImage* img11=cvLoadImage(m_strFileName22);//////不能打开10000以上的图

		const QByteArray text01 = m_strFileName.toLocal8Bit();
		const char *m_strFileName01 = text01.data();
		//IplImage* img01=cvLoadImage(m_strFileName01);
		
		GDALAllRegister();

	    GDALDataset *pSrcDS1 = (GDALDataset*)GDALOpen(m_strFileName01, GA_ReadOnly);
		
		if(ww==0){
		int datuWidth = pSrcDS1->GetRasterXSize();
    
		int datuHeight=pSrcDS1->GetRasterYSize();
		
		int m=datuHeight/h0;
	    int n=datuWidth/w0;
	    if(datuHeight%h0>0.5*h0)
		   m++;
	    if(datuWidth%w0>0.5*w0)
		   n++;
	
	    ww=((double)datuWidth)/((double)n);
	    hh=((double)datuHeight)/((double)m);
		}//if(ww==0)
	    GDALDataset *pSrcDS2 = (GDALDataset*)GDALOpen(m_strFileName22, GA_ReadOnly);


		mese1=GetRMSE3(ptpairs2,CurrentKeypoints3,PreKeypoints3,H);
		H_1.clear();
		H_1.push_back(H);
		double ppx,ppy,RR02,RR12;
		ppx=nn*ww;
		ppy=mm*hh;
		RR02=cvmGet(H,0,2)+ppx;
		cvmSet(H,0,2,RR02);
		RR12=cvmGet(H,1,2)+ppy;
		cvmSet(H,1,2,RR12);

		cvInitMatHeader(H1,3,3,CV_64FC1,a,CV_AUTOSTEP);
		cvTranspose(H,H1);
		//QMatrix H2;
		CvMat *H2;
		H2=H1;
		R11=cvmGet(H1,0,0);
		R12=cvmGet(H1,0,1);
		R21=cvmGet(H1,1,0);
		R22=cvmGet(H1,1,1);
		R13=cvmGet(H1,0,2);
		R23=cvmGet(H1,1,2);
		R33=cvmGet(H1,2,2);
		px=cvmGet(H1,2,0);////平移
		py=cvmGet(H1,2,1);
		sfx=cvSqrt(R11*R11+R12*R12);///缩放
		sfy=cvSqrt(R21*R21+R22*R22);
		Rrotate=(180*atan(R12/R11))/3.1415;//////旋转角度
	
		
		int h1,h2;
		h1=abs(px)+0.5;
		h2=abs(py)+0.5;



		
		GDALDataType eDT1 = pSrcDS1->GetRasterBand(1)->GetRasterDataType();
		GDALDataType eDT2 = pSrcDS2->GetRasterBand(1)->GetRasterDataType();


		int iBandCount1 = pSrcDS1->GetRasterCount();
	
		int iBandCount2 = pSrcDS2->GetRasterCount();
	// 根据裁切范围确定裁切后的图像宽高
	//int iDstWidth  = iSizeX;
	//int iDstHeight = iSizeY;

	
		double adfGeoTransform[6] = {0};
	
		pSrcDS1->GetGeoTransform(adfGeoTransform);
	
		pSrcDS2->GetGeoTransform(adfGeoTransform);
	// 计算裁切后的图像的左上角坐标	
	//adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + iStartY*adfGeoTransform[2];
	//adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + iStartY*adfGeoTransform[5];

	// 创建输出文件并设置空间参考和坐标信息
	
		GDALDriver *poDriver = (GDALDriver *) GDALGetDriverByName("GTIFF");
		int ysize1=pSrcDS1->GetRasterYSize();
		int xsize1=pSrcDS1->GetRasterXSize();
		int ysize2=pSrcDS2->GetRasterYSize();
		int xsize2=pSrcDS2->GetRasterXSize();
	
		int iDstWidth=h1 +xsize2;
	
		int iDstHeight=h2+ ysize2;

	
		QString str1=file_path;
	
		QString str2("\\result.jpg");
	
		QString str=str1+str2;
	
		const QByteArray text = str.toLocal8Bit();
	
		const char *filename = text.data();

	    GDALDataset *pDstDS = poDriver->Create(filename, iDstWidth, iDstHeight, iBandCount1, eDT1, NULL);
	    pDstDS->SetGeoTransform(adfGeoTransform);
	    pDstDS->SetProjection(pSrcDS1->GetProjectionRef());

	    int *pBandMap = new int[iBandCount1];
	    for (int i=0; i<iBandCount1; i++)
		pBandMap[i] = i+1;

		cvReleaseImage( &temp1 );
		cvReleaseImage( &img1 );
		cvReleaseImage( &img1111 );
		cvReleaseImage( &img2 );
		cvReleaseMemStorage(&storage2);
		ptpairs2.clear();
		xishu.clear();
		lujing.clear();
		m_imgLoaded.Destroy();
	// 下面这里需要根据数据类型来判断，申请不同类型的缓存来进行处理，这里仅仅以8bit图像进行演示
	
		if (eDT1 == GDT_Byte)	// 如果是8bit图像
	
		{
		// 申请所有数据所需要的缓存，如果图像太大应该用分块处理
		
			//char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount1];	////////////////30000 30000内存申请不到了需要分块！！！！！10000*10000可以
			char *pDataBuff = new char[xsize1/2*ysize1/2*iBandCount1];
			
			pSrcDS1->RasterIO(GF_Read, 0,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write, 0, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

			pSrcDS1->RasterIO(GF_Read, 0,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write, 0, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
			
			pSrcDS1->RasterIO(GF_Read, xsize1/2,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write, xsize1/2, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

			pSrcDS1->RasterIO(GF_Read, xsize1/2,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write, xsize1/2, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    
			delete(pDataBuff);
			char *pDataBuff2 = new char[xsize2/2*ysize2/2*iBandCount2];
			
			pSrcDS2->RasterIO(GF_Read, 0,0,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write,h1,h2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

			pSrcDS2->RasterIO(GF_Read, 0,ysize2/2,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write,h1,h2+ysize2/2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

			pSrcDS2->RasterIO(GF_Read,xsize2/2,0,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write,h1+xsize2/2,h2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

			pSrcDS2->RasterIO(GF_Read,xsize2/2,ysize2/2,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		    pDstDS->RasterIO(GF_Write,h1+xsize2/2 ,h2+ysize2/2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		    delete(pDataBuff2);
	
		}
	
		else
	
		{
		// 其他类型的图像，与8bit类似，就是申请的缓存类型不同而已
	
		}

	
		delete(pBandMap);

	    GDALClose((GDALDatasetH)pSrcDS1);
	    GDALClose((GDALDatasetH)pSrcDS2);
	    GDALClose((GDALDatasetH)pDstDS);

	}	
		
	///////////////////////////////////////////b1不行//搜索b4/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(!H)
	{
		xishu.clear();	
		lujing.clear();

		QString fen2b4name=fen2path+"\\b4.jpg";
	   const QByteArray textfen2b4 = fen2b4name.toLocal8Bit();
	   const char *fen2nameb4 = textfen2b4.data();
	     strsmall=fen2nameb4;
		//strsmall="E:\\fen2\\b4.jpg";//大图的一块
	
	m_imgLoaded.Load(strsmall);
   img1111 = cvLoadImage(strsmall, 1);
	//int k;
	for(k=0; k<111; k++)
	{
		m_KeyMainColorSig[k] = 0;
	}
	for(k=0; k<15; k++)
	{
		m_KeyCuve[k]=0;
	}
	for(k=0;k<8;k++)
	{
		m_KeyShape[k]=0;
	}

	ColorSplit(m_imgLoaded);//转换成HSI空间  颜色
	CuveSplit(m_imgLoaded);    //转换成梯度   纹理
	ShapeSplit(m_imgLoaded);   //利用canny求出边缘  形状

	for(k=0;k<111;k++)
		m_KeyMainColorSig[k] = m_Color[k];
	for(k=0; k<15; k++)
	{
		m_KeyCuve[k]=m_Cuve[k];
	}
	for(k=0;k<8;k++)
	{
		m_KeyShape[k]=m_Shape[k];
	}
	///以上是大图的一个子图B1的特征

	/*********************得到小图像的特征***************************************/
	/***********************************************************************/

	ColorPow=m_ColorPow;
	CuvePow=m_CuvePow;
	ShapePow=m_ShapePow;
	if (ColorPow==0&&CuvePow==0&&ShapePow==0)
	{
		ColorPow=1;
		CuvePow=1;
		ShapePow=1;
	}
	plus = ColorPow + CuvePow + ShapePow;
	ColorPow /= plus;
	CuvePow /= plus;
	ShapePow /= plus;

	CariRecursive(m_strBeginPath, m_strExtension);//检索出最相似的


	number=xishu.size();///////////////////////////
	zuixiao=xishu[0];
	for (int i=0;i<number;i++)////找到最小的系数
	{
		
		if(zuixiao>xishu[i])
		{
			zuixiao=xishu[i];
			minNum=i;
		}			

	}


	QString tp2;
	tp2=lujing[minNum];

	QString dir_s2=tp2;
	const QByteArray text2 = dir_s2.toLocal8Bit();
	const char *tp3 = text2.data();


	temp1=cvLoadImage(tp3,1);//系数最小相似度最大？
	int len3=strlen(tp3);
	//QCharRef aaa2=tp2[8];
	QCharRef aaa2=tp2[len3-7];
	//QCharRef bbb2=tp2[10];
	QCharRef bbb2=tp2[len3-5];
	QChar aaaa2(aaa2);
	char aaaaa2=aaaa2.toAscii();
	QChar bbbb2(bbb2);
	char bbbbb2=bbbb2.toAscii();
	mm=aaaaa2-'0';
	nn=bbbbb2-'0';

	/*cvSetImageROI(img[0], cvRect(nn*ww, mm*hh, ww, hh) );*/

	img1=convert_to_gray8(/*img[0]*/temp1);//找到的小图
	img2=convert_to_gray8(img1111);//B1

	CvSeq *PreKeypoints33 = 0, *PreDescriptors33 = 0;
	CvSeq *CurrentKeypoints33 = 0, *CurrentDescriptors33 = 0;

	////////////////////
	CvMemStorage* storage22=cvCreateMemStorage(0);
	params11 = cvSURFParams(1000, 0);

	cvExtractSURF( img1, 0, &PreKeypoints33, &PreDescriptors33, storage22, params11);
	cvExtractSURF( img2, 0, &CurrentKeypoints33, &CurrentDescriptors33, storage22, params11);

	vector<int>ptpairs22;
	findPairs3( CurrentKeypoints33, CurrentDescriptors33, PreKeypoints33, PreDescriptors33, ptpairs22 );
	
	num1=ptpairs22.size()/2;
	H = GetH3(ptpairs22,CurrentKeypoints33,PreKeypoints33);
	/*cvResetImageROI( img[0] );*/



	

	if( H )
	{
		 /*QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
         Qpart2 = litmp.QuadPart; //终止计时
	     dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
         dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
		 QString s = QString::number(dfTime,'f',0);
	     ui.bigtime->setText(s);*/

		t=(double)(cvGetTickCount()-t)/(cvGetTickFrequency()*1000*1000.);
		QString s = QString::number(t,'f',3);
	    ui.bigtime->setText(s);

		const QByteArray text11 = m_strFileName2.toLocal8Bit();
		const char *m_strFileName22 = text11.data();
		//IplImage* img11=cvLoadImage(m_strFileName22);//////不能打开10000以上的图

		const QByteArray text01 = m_strFileName.toLocal8Bit();
		const char *m_strFileName01 = text01.data();
		//IplImage* img01=cvLoadImage(m_strFileName01);
		
		GDALAllRegister();

	    GDALDataset *pSrcDS1 = (GDALDataset*)GDALOpen(m_strFileName01, GA_ReadOnly);
		
		if(ww==0){
		int datuWidth = pSrcDS1->GetRasterXSize();
    
		int datuHeight=pSrcDS1->GetRasterYSize();
		
		int m=datuHeight/h0;
	    int n=datuWidth/w0;
	    if(datuHeight%h0>0.5*h0)
		   m++;
	    if(datuWidth%w0>0.5*w0)
		   n++;
	
	    ww=((double)datuWidth)/((double)n);
	    hh=((double)datuHeight)/((double)m);
		}//if(ww==0)
	    GDALDataset *pSrcDS2 = (GDALDataset*)GDALOpen(m_strFileName22, GA_ReadOnly);
		
		int r12=cvmGet(H,1,2);
		mese1=GetRMSE3(ptpairs22,CurrentKeypoints33,PreKeypoints33,H);
		H_1.clear();
		H_1.push_back(H);
		double ppx,ppy,RR02,RR12;
		ppx=nn*ww;
		ppy=mm*hh;
		RR02=cvmGet(H,0,2)+ppx;
		cvmSet(H,0,2,RR02);
		RR12=cvmGet(H,1,2)+ppy-(pSrcDS2->GetRasterYSize()-h0);
		cvmSet(H,1,2,RR12);

		cvInitMatHeader(H1,3,3,CV_64FC1,a,CV_AUTOSTEP);
		cvTranspose(H,H1);
		//QMatrix H2;
		CvMat *H2;
		H2=H1;
		R11=cvmGet(H1,0,0);
		R12=cvmGet(H1,0,1);
		R21=cvmGet(H1,1,0);
		R22=cvmGet(H1,1,1);
		R13=cvmGet(H1,0,2);
		R23=cvmGet(H1,1,2);
		R33=cvmGet(H1,2,2);
		px=cvmGet(H1,2,0);
		py=cvmGet(H1,2,1);//////////////////平移
		sfx=cvSqrt(R11*R11+R12*R12);
		sfy=cvSqrt(R21*R21+R22*R22);////////////////缩放
		Rrotate=(180*atan(R12/R11))/3.1415;//////旋转角度
		int h1,h2;
		h1=abs(px)+0.5;
		h2=abs(py)+0.5;



		
	    GDALDataType eDT1 = pSrcDS1->GetRasterBand(1)->GetRasterDataType();
	    GDALDataType eDT2 = pSrcDS2->GetRasterBand(1)->GetRasterDataType();

	    int iBandCount1 = pSrcDS1->GetRasterCount();
	    int iBandCount2 = pSrcDS2->GetRasterCount();
	// 根据裁切范围确定裁切后的图像宽高
	//int iDstWidth  = iSizeX;
	//int iDstHeight = iSizeY;

	    double adfGeoTransform[6] = {0};
	    pSrcDS1->GetGeoTransform(adfGeoTransform);
	    pSrcDS2->GetGeoTransform(adfGeoTransform);
	// 计算裁切后的图像的左上角坐标	
	//adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + iStartY*adfGeoTransform[2];
	//adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + iStartY*adfGeoTransform[5];

	// 创建输出文件并设置空间参考和坐标信息
	    GDALDriver *poDriver = (GDALDriver *) GDALGetDriverByName("GTIFF");
		int ysize1=pSrcDS1->GetRasterYSize();
		int xsize1=pSrcDS1->GetRasterXSize();
		int ysize2=pSrcDS2->GetRasterYSize();
		int xsize2=pSrcDS2->GetRasterXSize();
	    int iDstWidth=h1+xsize2;
	    int iDstHeight=h2+ysize1;

	    QString str1=file_path;
	    QString str2("\\result.jpg");
	    QString str=str1+str2;
	    const QByteArray text = str.toLocal8Bit();
	    const char *filename = text.data();

  
	    GDALDataset *pDstDS = poDriver->Create(filename, iDstWidth, iDstHeight, iBandCount1, eDT1, NULL);
	    pDstDS->SetGeoTransform(adfGeoTransform);
	    pDstDS->SetProjection(pSrcDS1->GetProjectionRef());

	    int *pBandMap = new int[iBandCount1];
	    for (int i=0; i<iBandCount1; i++)
		pBandMap[i] = i+1;
		cvReleaseImage( &temp1 );
		cvReleaseImage( &img1 );
		cvReleaseImage( &img1111 );
		cvReleaseImage( &img2 );
		cvReleaseMemStorage(&storage2);
		ptpairs2.clear();
		xishu.clear();
		lujing.clear();
		m_imgLoaded.Destroy();

	// 下面这里需要根据数据类型来判断，申请不同类型的缓存来进行处理，这里仅仅以8bit图像进行演示
	    if (eDT1 == GDT_Byte)	// 如果是8bit图像
	    {
		// 申请所有数据所需要的缓存，如果图像太大应该用分块处理
		//char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount1];	////////////////30000 30000内存申请不到了需要分块！！！！！10000*10000可以

		/*char *pDataBuff1 = new char[pSrcDS1->GetRasterXSize()*pSrcDS1->GetRasterYSize()/2*iBandCount1];
		pSrcDS1->RasterIO(GF_Read, 0,0,pSrcDS1->GetRasterXSize(), pSrcDS1->GetRasterYSize(), pDataBuff1, pSrcDS1->GetRasterXSize(),  pSrcDS1->GetRasterYSize(), eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, h2,  pSrcDS1->GetRasterXSize(),  pSrcDS1->GetRasterYSize(), pDataBuff1,  pSrcDS1->GetRasterXSize(),  pSrcDS1->GetRasterYSize(), eDT1, iBandCount1, pBandMap, 0, 0, 0);
		delete(pDataBuff1);*/
		
		char *pDataBuff1 = new char[xsize1/2*ysize1/2*iBandCount1];
		pSrcDS1->RasterIO(GF_Read, 0,0,xsize1/2, ysize1/2, pDataBuff1, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, h2,  xsize1/2,  ysize1/2, pDataBuff1,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS1->RasterIO(GF_Read, 0,ysize1/2,xsize1/2, ysize1/2, pDataBuff1, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, h2+ysize1/2,  xsize1/2,  ysize1/2, pDataBuff1,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS1->RasterIO(GF_Read, xsize1/2,0,xsize1/2, ysize1/2, pDataBuff1, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, h2,  xsize1/2,  ysize1/2, pDataBuff1,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS1->RasterIO(GF_Read, xsize1/2,ysize1/2,xsize1/2, ysize1/2, pDataBuff1, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, ysize1/2+h2,  xsize1/2,  ysize1/2, pDataBuff1,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		delete(pDataBuff1);
		
		/*char *pDataBuff2 = new char[pSrcDS2->GetRasterXSize()*pSrcDS2->GetRasterYSize()*iBandCount1];
		pSrcDS2->RasterIO(GF_Read, 0,0,pSrcDS2->GetRasterXSize(), pSrcDS2->GetRasterYSize(), pDataBuff2, pSrcDS2->GetRasterXSize(),  pSrcDS2->GetRasterYSize(), eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write,h1,0, pSrcDS2->GetRasterXSize(),  pSrcDS2->GetRasterYSize(), pDataBuff2,  pSrcDS2->GetRasterXSize(),  pSrcDS2->GetRasterYSize(), eDT1, iBandCount1, pBandMap, 0, 0, 0);
		delete(pDataBuff2);*/
		char *pDataBuff2 = new char[xsize2/2*ysize2/2*iBandCount1];
		pSrcDS2->RasterIO(GF_Read, 0,0,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write,h1,0, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS2->RasterIO(GF_Read, 0,ysize2/2,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write,h1,ysize2/2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS2->RasterIO(GF_Read,xsize2/2,0,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write,h1+xsize2/2,0, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pSrcDS2->RasterIO(GF_Read,xsize2/2,ysize2/2,xsize2/2, ysize2/2, pDataBuff2, xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write,h1+xsize2/2,ysize2/2, xsize2/2,  ysize2/2, pDataBuff2,  xsize2/2,  ysize2/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		delete(pDataBuff2);
	    }
	    else
	    {
		// 其他类型的图像，与8bit类似，就是申请的缓存类型不同而已
	     }

	    delete(pBandMap);

	    GDALClose((GDALDatasetH)pSrcDS1);
	    GDALClose((GDALDatasetH)pSrcDS2);
	    GDALClose((GDALDatasetH)pDstDS);

      }
	  else
	  {
		  QMessageBox::information(NULL, "Title", "Failed!! Please Input A Biger Width and Height!", QMessageBox::Yes, QMessageBox::Yes);

       }
	}
	//////////////////////////////////////b4完成//////////////////////////////////////
	cvReleaseImage( &temp1 );
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	cvReleaseMemStorage(&storage2);
	//cvReleaseImage( &temp );
	ptpairs2.clear();
	xishu.clear();
	lujing.clear();

	QString s = QString::number(t,'g',6);
	ui.bigtime->setText(s);
	QString mse = QString::number(mese1,'g',6);
	ui.fastmese->setText(mse);
	QString pxx = QString::number(px,'f',6);
	ui.fastpx->setText(pxx);
	QString pyy = QString::number(py,'f',6);
	ui.fastpy->setText(pyy);
	QString rota = QString::number(Rrotate,'f',6);
	ui.fastrotate->setText(rota);
	QString sfxx = QString::number(sfx,'f',6);
	QString sfyy = QString::number(sfy,'f',6);
	ui.fastsfx->setText(sfxx);
	ui.fastsfy->setText(sfyy);

	////显示
	    QString str1=file_path;
	    QString str2("\\result.jpg");
	    QString str=str1+str2;

		const QByteArray text4 = str.toLocal8Bit();
		const char *result4 = text4.data();

		BuildPyramids(result4);////////////////////////

        BSTR bstr_str;
       		
		bstr_str = SysAllocString(str.utf16());
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);
			
		m_pMapControl_4->AddLayer(pLyr,0);
			
		IActiveViewPtr pActiveView(m_pMapControl_4);
			
        m_pMapControl_4->Refresh(esriViewAll);  

		

    
}
void QT48Test::pinjie()
{

	LARGE_INTEGER litmp;
    LONGLONG Qpart1,Qpart2,Useingtime;
    double dfMinus,dfFreq,dfTime;
    //获得CPU计时器的时钟频率
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;
 
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值   
    Qpart1 = litmp.QuadPart; //开始计时
	
	fenkuai();
	caijian();
	Onspeed();

	/*
	    QString str1=file_path;
	    QString str2("\\result.jpg");
	    QString str=str1+str2;

		const QByteArray text = str.toLocal8Bit();
		const char *result = text.data();

		BuildPyramids(result);

        BSTR bstr_str;
       		
		bstr_str = SysAllocString(str.utf16());
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);
			
		m_pMapControl_4->AddLayer(pLyr,0);
			
		IActiveViewPtr pActiveView(m_pMapControl_4);
			
        m_pMapControl_4->Refresh(esriViewAll);  

		

*/

    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart2 = litmp.QuadPart; //终止计时
	dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
    dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
	QString s = QString::number(dfTime,'f',0);
	ui.bigtime->setText(s);
 
}

void QT48Test::linematching()
{
		
	LineSignature ls;
	IplImage *pImg11,*pImg12,*pImg21,*pImg22;

	const QByteArray text11 = m_strFileName2.toLocal8Bit();
		const char *m_strFileName22 = text11.data();
		
		
		const QByteArray text01 = m_strFileName.toLocal8Bit();
		const char *m_strFileName01 = text01.data();
	vector<IplImage* >img;
		img.push_back(cvLoadImage(m_strFileName01));
	img.push_back(cvLoadImage(m_strFileName22));
	
	pImg11=cvCreateImage( cvSize( img[1]->width ,img[1]->height ), IPL_DEPTH_8U, 3 );
	pImg12=cvCreateImage( cvSize( img[0]->width ,img[0]->height ), IPL_DEPTH_8U, 3 );
	pImg21=cvCreateImage( cvSize( img[1]->width ,img[1]->height ), IPL_DEPTH_8U, 3 );
	pImg22=cvCreateImage( cvSize( img[0]->width ,img[0]->height ), IPL_DEPTH_8U, 3 );

	cvCopy(img[1],pImg11);
	cvCopy(img[0],pImg12);
	cvCopy(img[1],pImg21);
	cvCopy(img[0],pImg22);



	double *pLineMatches = new double [MAXNUM * 8];
	int nLineMatches;
	double t;
	t=(double)cvGetTickCount();
	ls.MatchImage(img[1], img[0], MAXNUM, pLineMatches, nLineMatches);
	t=(double)(cvGetTickCount()-t)/(cvGetTickFrequency()*1000*1000.);
	t1=t;
	CvMat* warp_mat = cvCreateMat (3, 3, CV_32FC1); 
	CvMemStorage* storage11 = cvCreateMemStorage(0);//开辟16K的存储空间
	CvSeq* seq11 = cvCreateSeq( CV_32SC2,  
		sizeof(CvSeq),
		sizeof(CvPoint),
		storage11 );//创建序列，定义格式
	CvMemStorage* storage21 = cvCreateMemStorage(0);//开辟16K的存储空间
	CvSeq* seq21 = cvCreateSeq( CV_32SC2,  
		sizeof(CvSeq),
		sizeof(CvPoint),
		storage21 );//创建序列，定义格式
	//display
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5f, 0.5f, 0, 1, 8);
	char *text=new char[nLineMatches];
	CvPoint org, point1, point2;
	CvSize text_size;
	int baseline;
	int width1 = pImg11->width, height1 = pImg11->height;
	int width2 = pImg12->width, height2 = pImg12->height;
	int width3 = pImg21->width, height3 = pImg21->height;
	int width4 = pImg22->width, height4 = pImg22->height;
	unsigned char *pData1 = (unsigned char *)pImg11->imageData;
	unsigned char *pData2 = (unsigned char *)pImg12->imageData;
	unsigned char *pData3 = (unsigned char *)pImg21->imageData;
	unsigned char *pData4 = (unsigned char *)pImg22->imageData;

	CvPoint2D32f *p5=new CvPoint2D32f[nLineMatches];
	CvPoint2D32f *p6=new CvPoint2D32f[nLineMatches];
	std::vector<Ipoint> ipts1;       //图1直线中点容器
	std::vector<Ipoint> ipts2;       //图2直线中点容器
	std::vector<Ipoint> ipts11;       //图1直线中点容器
	std::vector<Ipoint> ipts12;       //图2直线中点容器
	std::vector<Ipoint> ipts21;       //图1直线中点容器
	std::vector<Ipoint> ipts22;       //图2直线中点容器
	
	num1=nLineMatches;
	for(int i = 0; i < nLineMatches; i++)
	{
		point1.x = pLineMatches[8 * i];
		point1.y = pLineMatches[8 * i + 1];
		point2.x = pLineMatches[8 * i + 2];
		point2.y = pLineMatches[8 * i + 3];

		org.x = (point1.x + point2.x) / 2;
		org.y = (point1.y + point2.y) / 2;
		
		Ipoint ipt1;
		ipt1.x = (float(point1.x + point2.x)) / 2;
		ipt1.y = (float(point1.y + point2.y)) / 2;
		ipt1.scale = 1.2;
		ipts1.push_back(ipt1);

		Ipoint ipt11;
		ipt11.x = point1.x ;
		ipt11.y = point1.y ;
		ipt11.scale = 1.2;
		ipts11.push_back(ipt11);

		Ipoint ipt12;
		ipt12.x = point2.x ;
		ipt12.y = point2.y ;
		ipt12.scale = 1.2;
		ipts12.push_back(ipt12);

		cvLine(pImg11, point1, point2, cvScalar(0, 0, 255), 1, 8, 0);  //红色////检测出的直线
		sprintf(text, "%d", i);
		
		cvGetTextSize(text, &font, &text_size, &baseline );
		int x1 = text_size.width;
		int y1 = text_size.height;
		for(int k1 = 0; k1 < x1; k1++)
		{
			for(int k2 = -baseline; k2 < y1 + 2; k2++)
			{
				int x2 = org.x + k1;
				int y2 = org.y - k2;
				if(x2 >= 0 && x2 < width1 && y2 >= 0 && y2 < height1)
				{
					int index = y2 * pImg11->widthStep + 3 * x2;
					pData1[index] = 255;
					pData1[index + 1] = 255;
					pData1[index + 2] = 255;
				}
			}
		}
		cvPutText(pImg11, text, org, &font, cvScalar(0, 0, 0) );

		point1.x = pLineMatches[8 * i + 4];
		point1.y = pLineMatches[8 * i + 5];
		point2.x = pLineMatches[8 * i + 6];
		point2.y = pLineMatches[8 * i + 7];

		org.x = (point1.x + point2.x) / 2;
		org.y = (point1.y + point2.y) / 2;
		
		Ipoint ipt2;
		ipt2.x = (float(point1.x + point2.x)) / 2;
		ipt2.y = (float(point1.y + point2.y)) / 2;
		ipt2.scale = 1.2;
		ipts2.push_back(ipt2);

		Ipoint ipt21;
		ipt21.x = point1.x ;
		ipt21.y = point1.y ;
		ipt21.scale = 1.2;
		ipts21.push_back(ipt21);

		Ipoint ipt22;
		ipt22.x = point2.x ;
		ipt22.y = point2.y ;
		ipt22.scale = 1.2;
		ipts22.push_back(ipt22);

		cvLine(pImg12, point1, point2, cvScalar(0, 0, 255), 1, 8, 0);
		sprintf(text, "%d", i);
		cvGetTextSize(text, &font, &text_size, &baseline );
		x1 = text_size.width;
		y1 = text_size.height;
		for(int k1 = 0; k1 < x1; k1++)
		{
			for(int k2 = -baseline; k2 < y1 + 2; k2++)
			{
				int x2 = org.x + k1;
				int y2 = org.y - k2;
				if(x2 >= 0 && x2 < width2 && y2 >= 0 && y2 < height2)
				{
					int index = y2 * pImg12->widthStep + 3 * x2;
					pData2[index] = 255;
					pData2[index + 1] = 255;
					pData2[index + 2] = 255;
				}
			}
		}
		cvPutText(pImg12, text, org, &font, cvScalar(0, 0, 0) );
	}

	cvSaveImage("E:\\test\\line\\K H\\line3\\aa.jpg", pImg11);
	cvSaveImage("E:\\test\\line\\K H\\line3\\bb.jpg", pImg12);


	/********************直线中点和端点surf匹配*************************************/
	IplImage *int_img1= Integral(/*img[1]*/ pImg11);
	IplImage *int_img2= Integral(pImg12);

	Surf11 des1(int_img1,ipts1);
	des1.getDescriptors(false);
	Surf11 des11(int_img1,ipts11);
	des11.getDescriptors(false);
	Surf11 des12(int_img1,ipts12);
	des12.getDescriptors(false);

	Surf11 des2(int_img2,ipts2);
	des2.getDescriptors(false);
	Surf11 des21(int_img2,ipts21);
	des21.getDescriptors(false);
	Surf11 des22(int_img2,ipts22);
	des22.getDescriptors(false);

	vector<int> pair1;
	vector<int> pair2;
	vector<int> pair11;
	vector<int> pair12;
	vector<int> pair21;
	vector<int> pair22;
	vector<int> pair4;
	vector<int> pair5;
	vector<int> pair6;

	getMatches(ipts1,ipts2,pair1,pair2);
	getMatches(ipts11,ipts21,pair11,pair21);
	getMatches(ipts12,ipts22,pair12,pair22);

	for(int i=0;i<pair1.size();i++)
	{
		if(pair1[i]==pair2[i])
		{
			pair4.push_back(pair1[i]);
		}
	}
	for(int i=0;i<pair4.size();i++)
	{
		point1.x = pLineMatches[8 * (pair4[i])];
		point1.y = pLineMatches[8 * (pair4[i]) + 1];
		point2.x = pLineMatches[8 * (pair4[i]) + 2];
		point2.y = pLineMatches[8 * (pair4[i]) + 3];
		p5[i].x=(float(point1.x + point2.x)) / 2;
		p5[i].y=(float(point1.y + point2.y)) / 2;       
		cvSeqPush( seq11,&p5[i]);//压栈，把数组指针指向的point点放入序列

		point1.x = pLineMatches[8 * (pair4[i]) + 4];
		point1.y = pLineMatches[8 * (pair4[i]) + 5];
		point2.x = pLineMatches[8 * (pair4[i]) + 6];
		point2.y = pLineMatches[8 * (pair4[i]) + 7];
		p6[i].x=(float(point1.x + point2.x)) / 2;
		p6[i].y=(float(point1.y + point2.y)) / 2;       
		cvSeqPush( seq21,&p6[i]);//压栈，把数组指针指向的point点放入序列
	}

	for(int i=0;i<pair11.size();i++)
	{
		if(pair11[i]==pair21[i])
		{
			pair5.push_back(pair11[i]);
		}
	}
	for(int i=0;i<pair5.size();i++)
	{
		point1.x = pLineMatches[8 * (pair5[i])];
		point1.y = pLineMatches[8 * (pair5[i]) + 1];
		p5[i].x=(float(point1.x )) ;
		p5[i].y=(float(point1.y )) ;       
		cvSeqPush( seq11,&p5[i]);//压栈，把数组指针指向的point点放入序列

		point1.x = pLineMatches[8 * (pair5[i]) + 4];
		point1.y = pLineMatches[8 * (pair5[i]) + 5];
		p6[i].x=(float(point1.x )) ;
		p6[i].y=(float(point1.y )) ;       
		cvSeqPush( seq21,&p6[i]);//压栈，把数组指针指向的point点放入序列
	}

	for(int i=0;i<pair12.size();i++)
	{
		if(pair12[i]==pair22[i])
		{
			pair6.push_back(pair12[i]);
		}
	}
	for(int i=0;i<pair6.size();i++)
	{
		point2.x = pLineMatches[8 * (pair6[i]) + 2];
		point2.y = pLineMatches[8 * (pair6[i]) + 3];
		p5[i].x=(float(point2.x));
		p5[i].y=(float(point2.y));       
		cvSeqPush( seq11,&p5[i]);//压栈，把数组指针指向的point点放入序列

		point2.x = pLineMatches[8 * (pair6[i]) + 6];
		point2.y = pLineMatches[8 * (pair6[i]) + 7];
		p6[i].x=(float(point2.x)) ;
		p6[i].y=(float(point2.y)) ;       
		cvSeqPush( seq21,&p6[i]);//压栈，把数组指针指向的point点放入序列
	}

	if(pair4.size()+pair5.size()+pair6.size()>=4)
	{
		CvMat* H;
		int innernum1=0;
		vector<int> ptpairs1;
		for(int i=0;i<pair4.size()+pair5.size()+pair6.size();i++)
		{
			ptpairs1.push_back(i);       
			ptpairs1.push_back(i);
		}
		H = GetH2(ptpairs1,seq11,seq21,innernum1);//小到大
		if(H)
		{
			
			mese1=GetRMSE2(ptpairs1,seq11,seq21,H);
			H_1.clear();
			H_1.push_back(H);
			double px,py;
			int h1,h2;
			px=cvmGet(H,0,2);
			py=cvmGet(H,1,2);
			h1=abs(px)+0.5;
			h2=abs(py)+0.5;
			IplImage* xformed;
			xformed = cvCreateImage( cvSize(  img[0]->width + h1,
				img[0]->height+h2 ), IPL_DEPTH_8U, 3 );
			cvWarpPerspective( img[1], xformed, H, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,cvScalarAll( 0 ) );
			//透视投影
			cvSetImageROI(xformed, cvRect(0, 0, img[0]->width, img[0]->height) );
			cvAddWeighted(img[0], 1,  xformed,0, 0,  xformed);
			//权重函数，参数含义分别是：第一组数组，权值，第二组数组，权值，输出时候添加常数项，输出数组
			cvResetImageROI( xformed );

			QString str1=file_path;
			QString str2("\\result.jpg");
			QString str=str1+str2;
			
			const QByteArray text = str.toLocal8Bit();
			const char *filename = text.data();

			cvSaveImage(filename,xformed);
			//theApp.OpenDocumentFile(filename);   //显示拼合结果图
			 BSTR bstr_str;


			 	QString s = QString::number(t1,'g',6);
	ui.surftime->setText(s);
	QString mse = QString::number(mese1,'g',6);
	ui.surfmese->setText(mse);
	QString pxx = QString::number( nLineMatches,'f',6);
	ui.surfpx->setText(pxx);/////这个是匹配的直线对数不是平移，借用一下显示框
	//QString pyy = QString::number(py,'f',6);
	//ui.surfpy->setText(pyy);
	//QString rota = QString::number(rotate,'f',6);
	//ui.surfrotate->setText(rota);
	//QString sfxx = QString::number(sfx,'f',6);
	//QString sfyy = QString::number(sfy,'f',6);
	//ui.surfsfx->setText(sfxx);
	//ui.surfsfy->setText(sfyy);
       		
		bstr_str = SysAllocString(str.utf16());
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);
			
		m_pMapControl_4->AddLayer(pLyr,0);
			
		IActiveViewPtr pActiveView(m_pMapControl_4);
			
        m_pMapControl_4->Refresh(esriViewAll);  

			///////////////////////////
			cvReleaseImage(&xformed);
		}
		else
			{
				//MessageBox("直线匹配算法失败！");
				t1=0;
				mese1=0;
				num1=0;
				return ;
		    }
		ptpairs1.clear();
		/*cvSaveImage("image/31/pin3.jpg", xformed);*/
	}
	else
		{
			//MessageBox("直线匹配算法失败！");
			t1=0;
			mese1=0;
			num1=0;
			return ;
	    }


	delete pLineMatches;
	ipts1.clear();
	ipts2.clear();
	ipts11.clear();
	ipts12.clear();
	ipts21.clear();
	ipts22.clear();
	pair1.clear();
	pair2.clear();
	pair11.clear();
	pair12.clear();
	pair21.clear();
	pair22.clear();
	pair4.clear();
	pair5.clear();
	pair6.clear();
	
	cvReleaseImage(&pImg11);
	cvReleaseImage(&pImg12);
	cvReleaseImage(&pImg21);
	cvReleaseImage(&pImg22);
	cvReleaseImage(&int_img1);
	cvReleaseImage(&int_img2);
	cvReleaseMemStorage(&storage21);
	cvReleaseMemStorage(&storage11);
	img.clear();





}

void QT48Test::surf()
{
	// TODO: 在此添加命令处理程序代码
	vector<IplImage* >img;
	const QByteArray text11 = m_strFileName2.toLocal8Bit();
		const char *m_strFileName22 = text11.data();
		
		
		const QByteArray text01 = m_strFileName.toLocal8Bit();
		const char *m_strFileName01 = text01.data();
	img.push_back(cvLoadImage(m_strFileName01));
	img.push_back(cvLoadImage(m_strFileName22));
	CvMat* H;
	CvMat h;
	CvMat* H1=&h;
	double a[9];
	double px,py;
	
	double sfx,sfy;
	double rotate;
	double R11,R12,R21,R22;
	char PX[20]={""},PY[20]={""};
	char SFX[20]={""},SFY[20]={""};
	char ROTATE[20]={""};
	char TIME[20]={""};
	QString d=",";
	int dian;
	char dot[20]={""};
	char time[20]={""};
	vector<int>ptpairs;
	
	if(!img[0]||!img[1])
	{ //QMessageBox("Please open another image",0,0);
	return;
	}
	CvMemStorage* storage = cvCreateMemStorage(0);//内存存储器
	static CvScalar colors[] = 
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}},
		{{255,255,255}}
	};//建立类似于调色版的东西
	//double t=(double)cvGetTickCount();
	//CvSURFParams params = cvSURFParams(1000, 0);
	IplImage* img1=convert_to_gray8(img[0]);
	IplImage* img2=convert_to_gray8(img[1]);
	
	CvSURFParams params = cvSURFParams(1000, 1);
	cv::initModule_nonfree();
	double t=(double)cvGetTickCount();//计时
	cvExtractSURF( img1,0,&objectKeypoints, &objectDescriptors, storage, params);//出错了
	cvExtractSURF( img2,0,&imageKeypoints, &imageDescriptors, storage, params);
	findPairs3(imageKeypoints,imageDescriptors,objectKeypoints,objectDescriptors,ptpairs);
	
	if (ptpairs.size()/2<4)
	{
		//MessageBox("SURF配准失败,请尝试其他方法！");
		t2=0;
		mese2=0;
		num2=0;
		return;
	}
	else
	{

		num2=ptpairs.size()/2;
		H=GetH3(ptpairs,imageKeypoints,objectKeypoints);
		
		if (H)
		{
			t=(double)(cvGetTickCount()-t)/(cvGetTickFrequency()*1000*1000.);//搜索的时间，所谓帧率每秒钟能够更新的次数
			mese2=GetRMSE3(ptpairs,imageKeypoints,objectKeypoints,H);
			H_2.clear();
			H_2.push_back(H);
			
			int h1,h2;
			px=cvmGet(H,0,2);
			py=cvmGet(H,1,2);

			cvInitMatHeader(H1,3,3,CV_64FC1,a,CV_AUTOSTEP);
		
			cvTranspose(H,H1);

			double R11,R12,R21,R22,R13,R23,R33;
			R11=cvmGet(H1,0,0);
		
			R12=cvmGet(H1,0,1);
		
			R21=cvmGet(H1,1,0);
		
			R22=cvmGet(H1,1,1);
		
			R13=cvmGet(H1,0,2);
		
			R23=cvmGet(H1,1,2);
		
			R33=cvmGet(H1,2,2);
			sfx=cvSqrt(R11*R11+R12*R12);///缩放
		
			sfy=cvSqrt(R21*R21+R22*R22);
		
			rotate=(180*atan(R12/R11))/3.1415;//////旋转角度

			h1=abs(px)+0.5;
			h2=abs(py)+0.5;
			IplImage* xformed;
			xformed = cvCreateImage( cvSize(  h1 + img[0]->width,
				h2+img[0]->height ), IPL_DEPTH_8U, 3 );
			cvWarpPerspective( img[1], xformed, H, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,cvScalarAll( 0 ) );
			//透视投影
			cvSetImageROI(xformed, cvRect(0, 0, img[0]->width, img[0]->height) );
			cvAddWeighted(img[0], 1,  xformed,0, 0,  xformed);
			//权重函数，参数含义分别是：第一组数组，权值，第二组数组，权值，输出时候添加常数项，输出数组
			cvResetImageROI( xformed );

			QString str1=file_path;
			QString str2("\\SURFresult.jpg");
			QString str=str1+str2;
			
			const QByteArray text = str.toLocal8Bit();
			const char *filename = text.data();

			cvSaveImage(filename,xformed);

			BSTR bstr_str;
       		
		bstr_str = SysAllocString(str.utf16());
            
		HRESULT hr;
			
		IRasterLayerPtr pRasterLy(CLSID_RasterLayer);
			
		hr=pRasterLy->CreateFromFilePath(bstr_str);
			
		if(FAILED(hr))
				
			return;
			
		ILayerPtr pLyr(pRasterLy);
			
		m_pMapControl_4->AddLayer(pLyr,0);
			
		IActiveViewPtr pActiveView(m_pMapControl_4);
			
        m_pMapControl_4->Refresh(esriViewAll);  

			//theApp.OpenDocumentFile(filename);   //显示拼合结果图
			///////////////////////////
			cvReleaseImage(&xformed);

		}
		else
		{
			//MessageBox("SURF配准失败,请尝试其他方法！");
			t2=0;
			mese2=0;
			num2=0;
			return ;
		}

	}

	QString s = QString::number(t,'g',6);
	ui.surftime->setText(s);
	QString mse = QString::number(mese2,'g',6);
	ui.surfmese->setText(mse);
	QString pxx = QString::number(px,'f',6);
	ui.surfpx->setText(pxx);
	QString pyy = QString::number(py,'f',6);
	ui.surfpy->setText(pyy);
	QString rota = QString::number(rotate,'f',6);
	ui.surfrotate->setText(rota);
	QString sfxx = QString::number(sfx,'f',6);
	QString sfyy = QString::number(sfy,'f',6);
	ui.surfsfx->setText(sfxx);
	ui.surfsfy->setText(sfyy);

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	ptpairs.clear();
	cvReleaseMemStorage(&storage);
}


void QT48Test::addlayertoglobe(QString filePath,QString fileName,IGlobeControlPtr GlobeControl)
{
//QString filePath = "E:\\test\\3d1";//待加载纹理所在文件夹
 BSTR bstr_str;	
 bstr_str = SysAllocString(filePath.utf16());
//  QString fileName = "5.tif";     //纹理名称
	 	
 BSTR bstr_str2;
 bstr_str2 = SysAllocString(fileName.utf16());

 IWorkspacePtr ipWS;

 IWorkspaceFactoryPtr ipWSF(CLSID_RasterWorkspaceFactory);
//If Not pWSF.IsWorkspace(sPath) Then Exit Sub

 ipWSF->OpenFromFile(bstr_str, 0, &ipWS);

 IRasterWorkspace2Ptr ipRWS(ipWS);

 IRasterDatasetPtr ipRasterDS;

 ipRWS->OpenRasterDataset(bstr_str2, &ipRasterDS);

//IRasterPtr ipRaster;
//ipRasterDS->CreateDefaultRaster(&ipRaster);


 IRasterLayerPtr pRasterLayer(CLSID_RasterLayer);

 pRasterLayer->CreateFromDataset(ipRasterDS);
 ILayerPtr pLayer(pRasterLayer);	 
 IGlobePtr globe;
 GlobeControl->get_Globe(&globe);
 IGlobeDisplayPtr pGlobeDispaly;

 GlobeControl->get_GlobeDisplay(&pGlobeDispaly);
 globe->AddLayerType(pLayer,esriGlobeLayerTypeDraped,0);
 pGlobeDispaly->RefreshViewers();	
}

void QT48Test::adddemtoglobe(QString filePath,QString fileName,IGlobeControlPtr GlobeControl )
{
//QString filePath = "E:\\test\\3d1";//待加载dem所在文件夹
 BSTR bstr_str;	
 bstr_str = SysAllocString(filePath.utf16());
//  QString fileName = "5.dem";     //dem名称
	 	
 BSTR bstr_str2;
 bstr_str2 = SysAllocString(fileName.utf16());

 IWorkspacePtr ipWS;

 IWorkspaceFactoryPtr ipWSF(CLSID_RasterWorkspaceFactory);
//If Not pWSF.IsWorkspace(sPath) Then Exit Sub

 ipWSF->OpenFromFile(bstr_str, 0, &ipWS);

 IRasterWorkspace2Ptr ipRWS(ipWS);

 IRasterDatasetPtr ipRasterDS;

 ipRWS->OpenRasterDataset(bstr_str2, &ipRasterDS);

//IRasterPtr ipRaster;
//ipRasterDS->CreateDefaultRaster(&ipRaster);

 IRasterLayerPtr pRasterLayer(CLSID_RasterLayer);

 pRasterLayer->CreateFromDataset(ipRasterDS);
 ILayerPtr pLayer(pRasterLayer);	 
 IGlobePtr globe;
 GlobeControl->get_Globe(&globe);
 IGlobeDisplayPtr pGlobeDispaly;

 GlobeControl->get_GlobeDisplay(&pGlobeDispaly);
 globe->AddLayerType(pLayer,esriGlobeLayerTypeElevation,0);
 pGlobeDispaly->RefreshViewers();	
}


/*void QT48Test::addtiftoglobe()
{


	QFileInfo fi;		  
		file_full2 = QFileDialog::getOpenFileName(this,"open tif","E:\\test","*.tif");  
		fi = QFileInfo(file_full2);  
		file_name2 = fi.fileName();  
		file_path2= fi.absolutePath(); 	
   addlayertoglobe(file_path2,file_name2,m_pGlobeControl);

}

void QT48Test::adddemtoglobe()
{
	QString file_full3, file_name3, file_path3; 
	QFileInfo fi;		  
		file_full3 = QFileDialog::getOpenFileName(this,"open dem",file_path2,"*.dem");
		fi = QFileInfo(file_full3);  
		file_name3 = fi.fileName();  
		file_path3= fi.absolutePath(); 	
   adddemtoglobe(file_path3,file_name3,m_pGlobeControl);

}

void QT48Test::zoomtolayer()
{
IScenePtr scene;
IGlobePtr globe;
m_pGlobeControl->get_Globe(&globe);
scene=globe;
ILayerPtr layer ;

scene->get_Layer(0,&layer);

IEnvelopePtr envelope;
layer->get_AreaOfInterest(&envelope);

IGlobeDisplayPtr pGlobeDispaly;
m_pGlobeControl->get_GlobeDisplay(&pGlobeDispaly);
ICameraPtr camera;
ISceneViewerPtr ppViewer;
pGlobeDispaly->get_ActiveViewer(&ppViewer);
ppViewer->get_Camera(&camera);

IGlobeCameraPtr globeCamera;
globeCamera=camera;
globeCamera->SetToZoomToExtents(envelope, globe, ppViewer); 

}

/*void QT48Test::open1()
{
	PyramidBase pyramid1;
	QFileInfo fi;		  
	//file_full1 = QFileDialog::getOpenFileName(this,"open the second picture",file_path1);  
	//fi = QFileInfo(file_full1);  
	
	file_full = QFileDialog::getOpenFileName(this,"open the first picture","E:\\test");  
		fi = QFileInfo(file_full);  

	//file_name = fi.fileName();  
	//file_path = fi.absolutePath(); 	
	QString m_strFileName1=fi.absoluteFilePath();

	String str1 = m_strFileName1.toStdString();
	int po = str1.find_last_of('/');
	string str2 = str1.substr( 0,po+1);
	QString path1 = QString::fromStdString(str2);

	//下面将QString转换为const char*类型
	QByteArray aByteArray1 = m_strFileName1.toAscii();
	pyramid1.InFilePath = aByteArray1.constData();//获取文件的完整路径

	QByteArray aByteArray2 = path1.toAscii();
	pyramid1.Path = aByteArray2.constData();	//获取文件夹的路径，用以保存金字塔文件

	pyramid1.CheckPyramid();

	for (int i = 0;i < pyramid1.iOverViewCount; i++)
	{
		pyramid1.ReadPyramidFile(1,i);
		i++;
	}



	BSTR bstr_str;

	bstr_str = SysAllocString(m_strFileName1.utf16());

	HRESULT hr;

	IRasterLayerPtr pRasterLy(CLSID_RasterLayer);

	hr=pRasterLy->CreateFromFilePath(bstr_str);

	if(FAILED(hr))

		return;

	ILayerPtr pLyr(pRasterLy);

	m_pMapControl->AddLayer(pLyr,0);

	IActiveViewPtr pActiveView(m_pMapControl);

	m_pMapControl->Refresh(esriViewAll);  

	QMessageBox::information(this, tr("Information"),tr("王文"));

}

void QT48Test::open2()
{
PyramidBase pyramid2;
	QFileInfo fi;		  
	file_full2 = QFileDialog::getOpenFileName(this,"open the second picture",file_path2);  
	fi = QFileInfo(file_full2);  
	m_strFileName2=fi.absoluteFilePath();

	//将Qstring转换为String，进而利用String类中的函数：find_last_of()间接获得文件夹的路径，用以保存金字塔图像
	String str1 = m_strFileName2.toStdString();
	int po = str1.find_last_of('/');
	string str2 = str1.substr( 0, po + 1 );
	QString path1 = QString::fromStdString(str2);

	//下面将QString转换为const char*类型
	QByteArray aByteArray1 = m_strFileName2.toAscii();
	pyramid2.InFilePath = aByteArray1.constData();//获取文件的完整路径

	QByteArray aByteArray2 = path1.toAscii();
	pyramid2.Path = aByteArray2.constData();	//获取文件夹的路径，用以保存金字塔文件

	pyramid2.CheckPyramid();

	for (int i = 0;i < pyramid2.iOverViewCount; i++)
	{
		pyramid2.ReadPyramidFile(1,i);
		i++;
	}

	m_strFileName2=fi.absoluteFilePath();

	BSTR bstr_str;

	bstr_str = SysAllocString(m_strFileName2.utf16());

	HRESULT hr;

	IRasterLayerPtr pRasterLy(CLSID_RasterLayer);

	hr=pRasterLy->CreateFromFilePath(bstr_str);

	if(FAILED(hr))

		return;

	ILayerPtr pLyr(pRasterLy);

	m_pMapControl_3->AddLayer(pLyr,0);

	IActiveViewPtr pActiveView(m_pMapControl_3);

	m_pMapControl_3->Refresh(esriViewAll);  

	QMessageBox::information(this, tr("Information"),tr("宋蕴"));

}

/*void QT48Test::JCYpeizhun()
{
	QString jibie1= ui.jibie->currentText();
	int level=jibie1.toInt();


}*/