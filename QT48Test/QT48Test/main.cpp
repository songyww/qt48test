#include "qt48test.h"
#include <QtGui/QApplication>
#include<ArcSDK.h>


int main(int argc, char *argv[])
{
	 ::CoInitialize(NULL);

#pragma region 绑定许可

    IArcGISVersionPtr ipVer(__uuidof(VersionManager));

    VARIANT_BOOL succeeded;

    if (FAILED(ipVer->LoadVersion(esriArcGISEngine , L"10.1",&succeeded)))

        return 0;

#pragma endregion

    //

#pragma region 初始化许可

    IAoInitializePtr ipInit(CLSID_AoInitialize);

    esriLicenseStatus status;

    ipInit->Initialize(esriLicenseProductCodeEngine, &status);

    if (status != esriLicenseCheckedOut)

    {

        AoExit(0);

        return 0;

    }

        

#pragma endregion
	esriLicenseExtensionCode ExtensionCode;
	esriLicenseStatus status1;
	ipInit->CheckOutExtension(esriLicenseExtensionCode3DAnalyst,&status1);


	
	QApplication a(argc, argv);
	QT48Test w;
	w.show();
	return a.exec();
}




