// Copyright 2012 ESRI
// 
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
// 
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
// 
// See the use restrictions at <your ArcGIS install location>/DeveloperKit10.1/userestrictions.txt.
// 

 
 
#include "BuildPyramids.h"

/*
int main(int argc, char** argv)
{
	int argc=2;
  cout << "BuildPyramidsRasterDataset - " 
       << "Environmental Systems Research Institute" << endl << endl;
  
  if (argc != 2)
  {
    cout << "Usage: BuildPyrami dsRasterDataset [input raster]" << endl;

    AoExit(0);
  }

  char* input("E:\\test\\5\\result.jpg"); //argv[1]
  
  if (!InitializeApp())
  {
    AoExit(0);
  }

  HRESULT hr = BuildPyramids(input);
  if (FAILED(hr))
    cerr << "Building pyramids failed." << endl;

  ShutdownApp();

  AoExit(0);
}*/

HRESULT BuildPyramids(const char* input)
{
  // data location 
  CComBSTR dataPath;
  CComBSTR dataFile;

  HRESULT hr = GetParentDirFromFullPath(input, &dataPath);
  if (FAILED(hr) || dataPath.Length() <= 0)
  {
    cerr << "Invalid data path." << endl;
    return E_FAIL;
  }
  hr = GetFileFromFullPath(input, &dataFile);
  if (FAILED(hr) || dataFile.Length() <= 0)
  {
    cerr << "Invalid data file." << endl;
    return E_FAIL;
  }

  // Get the raster workspace through the workspace factory.
  IWorkspaceFactoryPtr ipRasWkspFac(CLSID_RasterWorkspaceFactory);
  IWorkspacePtr ipWksp;
  hr = ipRasWkspFac->OpenFromFile(dataPath, 0, &ipWksp);
  if (FAILED(hr) || ipWksp == 0)
  {
    cout << "Could not open workspace." << endl;
    return hr;
  }

  IRasterDatasetPtr ipRasDataset;
  hr = ((IRasterWorkspacePtr) ipWksp)->OpenRasterDataset(dataFile, &ipRasDataset);
  if (FAILED(hr) || ipRasDataset == 0)
  {
    cout << "Couldn't open dataset." << endl;
    return hr;
  }
  // If there are not already pyramids, create them
  IRasterPyramidPtr ipRasPyr(ipRasDataset);  
  short pyrPresent;
  ipRasPyr->get_Present(&pyrPresent);
  if (!pyrPresent)
  {
    cerr << "... working ..." << endl;
    ipRasPyr->Create();
    wcerr << L"Done creating pyramids on " << (BSTR) dataFile << endl;
  }
  else
  {
    wcerr << L"Pyramids already exist for " << (BSTR) dataFile << endl;
  }
  return S_OK;
}




