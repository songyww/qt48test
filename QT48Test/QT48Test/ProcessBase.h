#ifndef PROCESSBASE
#define PROCESSBASE

#define _AFXDLL
#pragma


#include "gdal.h"
#include "gdal_priv.h"
//#include "afx.h"
#pragma comment(lib,"gdal_i.lib")
using namespace std;
#pragma warning(disable: 4996)
#include <cstring>

/*
 *	@brief Process类中提供进度条基类接口，用于反映当前算法的进度值
 */

class CProcessBase
{

public:
	//变量定义

	/*! 进度信息 */
	string m_strMessage;
	/*! 进度值 */
	double m_dPosition;  
	/*! 进度个数 */
	int m_iStepCount;  
	/*! 进度当前个数 */
	int m_iCurStep;   
	/*! 是否取消，值为false时表示计算取消 */
	bool m_bIsContinue;  


public:
	//构造函数
	CProcessBase()
	{
		m_dPosition = 0.0;
		m_iStepCount = 100;
		m_iCurStep = 0;
		m_bIsContinue = true;

	}
	//析构函数
	virtual ~CProcessBase() {}

	/**
	 * @brief 设置进度信息
	 * @param pszMsg   进度信息
	 */
	 virtual void SetMessage(const char* pszMsg) = 0;


	 /**
	 * @brief 设置进度值
	 * @param dPosition  进度值
	 * @return 返回是否取消的状态，true为不取消，false为取消
	 */
	 virtual bool SetPosition(double dPosition) = 0;

	/**
	 * @brief 进度条前进一步，返回true表示继续，false表示取消
	 * @return 返回是否取消的状态，true为不取消，false为取消
	 */
	 virtual bool StepIt() = 0;

	/**
	 * @brief 设置进度个数
	 * @param iStepCount  进度个数
	 */
	 virtual void SetStepCount(int iStepCount)
	 {
	  ReSetProcess(); 
	  m_iStepCount = iStepCount;
	 }

	 /**
	 * @brief 获取进度信息
	 * @return 返回当前进度信息
	 */
	 string GetMessage()
	 {
	  return m_strMessage;
	 }

	 /**
	 * @brief 获取进度值
	 * @return 返回当前进度值
	 */
	 double GetPosition()
	 {
	  return m_dPosition;
	 }

	 /**
	 * @brief 重置进度条
	 */
	 void ReSetProcess()
	 {
	  m_dPosition = 0.0;
	  m_iStepCount = 100;
	  m_iCurStep = 0;
	  m_bIsContinue = true;
	 }

};



class CConsoleProcess : public CProcessBase
{
public:
 /**
 * @brief 构造函数
 */
 CConsoleProcess() 
 {
  m_dPosition = 0.0;
  m_iStepCount = 100;
  m_iCurStep = 0;
 };

 /**
 * @brief 析构函数
 */
 ~CConsoleProcess() 
 {
  //remove(m_pszFile);
 };

 /**
 * @brief 设置进度信息
 * @param pszMsg   进度信息
 */
 void SetMessage(const char* pszMsg);
 

 /**
 * @brief 设置进度值
 * @param dPosition  进度值
 * @return 返回是否取消的状态，true为不取消，false为取消
 */
 bool SetPosition(double dPosition);
 

 /**
 * @brief 进度条前进一步
 * @return 返回是否取消的状态，true为不取消，false为取消
 */
 bool StepIt();


private:
 void TermProgress(double dfComplete)
 {
  static int nLastTick = -1;
  int nThisTick = (int) (dfComplete * 40.0);

  nThisTick = MIN(40,MAX(0,nThisTick));

  // Have we started a new progress run?  
  if( nThisTick < nLastTick && nLastTick >= 39 )
   nLastTick = -1;

  if( nThisTick <= nLastTick )
   return ;

  while( nThisTick > nLastTick )
  {
   nLastTick++;
   if( nLastTick % 4 == 0 )
    fprintf( stdout, "%d", (nLastTick / 4) * 10 );
   else
    fprintf( stdout, "." );
  }

  if( nThisTick == 40 )
   fprintf( stdout, " - done.\n" );
  else
   fflush( stdout );
 }
};



#endif