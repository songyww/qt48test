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
 *	@brief Process�����ṩ����������ӿڣ����ڷ�ӳ��ǰ�㷨�Ľ���ֵ
 */

class CProcessBase
{

public:
	//��������

	/*! ������Ϣ */
	string m_strMessage;
	/*! ����ֵ */
	double m_dPosition;  
	/*! ���ȸ��� */
	int m_iStepCount;  
	/*! ���ȵ�ǰ���� */
	int m_iCurStep;   
	/*! �Ƿ�ȡ����ֵΪfalseʱ��ʾ����ȡ�� */
	bool m_bIsContinue;  


public:
	//���캯��
	CProcessBase()
	{
		m_dPosition = 0.0;
		m_iStepCount = 100;
		m_iCurStep = 0;
		m_bIsContinue = true;

	}
	//��������
	virtual ~CProcessBase() {}

	/**
	 * @brief ���ý�����Ϣ
	 * @param pszMsg   ������Ϣ
	 */
	 virtual void SetMessage(const char* pszMsg) = 0;


	 /**
	 * @brief ���ý���ֵ
	 * @param dPosition  ����ֵ
	 * @return �����Ƿ�ȡ����״̬��trueΪ��ȡ����falseΪȡ��
	 */
	 virtual bool SetPosition(double dPosition) = 0;

	/**
	 * @brief ������ǰ��һ��������true��ʾ������false��ʾȡ��
	 * @return �����Ƿ�ȡ����״̬��trueΪ��ȡ����falseΪȡ��
	 */
	 virtual bool StepIt() = 0;

	/**
	 * @brief ���ý��ȸ���
	 * @param iStepCount  ���ȸ���
	 */
	 virtual void SetStepCount(int iStepCount)
	 {
	  ReSetProcess(); 
	  m_iStepCount = iStepCount;
	 }

	 /**
	 * @brief ��ȡ������Ϣ
	 * @return ���ص�ǰ������Ϣ
	 */
	 string GetMessage()
	 {
	  return m_strMessage;
	 }

	 /**
	 * @brief ��ȡ����ֵ
	 * @return ���ص�ǰ����ֵ
	 */
	 double GetPosition()
	 {
	  return m_dPosition;
	 }

	 /**
	 * @brief ���ý�����
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
 * @brief ���캯��
 */
 CConsoleProcess() 
 {
  m_dPosition = 0.0;
  m_iStepCount = 100;
  m_iCurStep = 0;
 };

 /**
 * @brief ��������
 */
 ~CConsoleProcess() 
 {
  //remove(m_pszFile);
 };

 /**
 * @brief ���ý�����Ϣ
 * @param pszMsg   ������Ϣ
 */
 void SetMessage(const char* pszMsg);
 

 /**
 * @brief ���ý���ֵ
 * @param dPosition  ����ֵ
 * @return �����Ƿ�ȡ����״̬��trueΪ��ȡ����falseΪȡ��
 */
 bool SetPosition(double dPosition);
 

 /**
 * @brief ������ǰ��һ��
 * @return �����Ƿ�ȡ����״̬��trueΪ��ȡ����falseΪȡ��
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