#ifndef QT48TEST_H
#define QT48TEST_H

#include <QtGui/QMainWindow>
#include "ui_qt48test.h"
#include<ArcSDK.h>

class QT48Test : public QMainWindow
{
	Q_OBJECT

public:
	QT48Test(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QT48Test();

private:
	Ui::QT48TestClass ui;

public:
	IGlobeControlPtr m_pGlobeControl;
	IMapControl3Ptr m_pMapControl;
	IMapControl3Ptr m_pMapControl_3;
	IMapControl3Ptr m_pMapControl_4;
	ISceneControlPtr m_pSceneControl;

	IToolbarControlPtr m_pToolbarControl;
	IToolbarControlPtr m_pToolbarControl2;
	IToolbarControlPtr m_pToolbarControl2_3;
	IToolbarControlPtr m_pToolbarControl2_4;
	IToolbarControlPtr m_pToolbarControl3;
	ITOCControlPtr m_pTOCControl;

	ITOCControlPtr m_pTOCControl2;
	ITOCControlPtr m_pTOCControl2_3;
	ITOCControlPtr m_pTOCControl2_4;
	ITOCControlPtr m_pTOCControl3;
	//GDALDataset *pSrcDS;
	QString m_strFileName;

	QString m_strFileName2;
	

	void AddToolBarCommand(IToolbarControlPtr ipToolBarControl);
	void add_toolbar_items(IToolbarControlPtr pToolbar);
	void AddToolbarItems(IToolbarControlPtr g_ipToolbarControl);
	void QT48Test::ImageCut(const char* pszSrcFile, const char* pszDstFile, int iStartX, int iStartY, int iSizeX, int iSizeY,const char* pszFormat);
	int ImageMosaicing(char** papszSrcFiles, const char* pszDstFilename,  int eResampleMethod, 
				   double dResX, double dResY, const char *pszFormat/*, CProcessBase* pProcess*/ );
	void addlayertoglobe(QString filePath,QString fileName,IGlobeControlPtr GlobeControl);
	void adddemtoglobe(QString filePath,QString fileName ,IGlobeControlPtr GlobeControl);
private slots:

	void fenkuai();
	void opentif();
	void opentif2();
	void caijian();
	void clearlayer();
	void Onspeed();
	void pinjie();
	void linematching();
	void surf();
	//void addtiftoglobe();
	//void adddemtoglobe();
	//void zoomtolayer();
	//void open1();
	//void open2();
	//void JCYpeizhun();
	
	
};

#endif // QT48TEST_H
