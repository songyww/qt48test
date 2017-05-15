#include "ProcessBase.h"




bool CConsoleProcess::StepIt()
{
	m_iCurStep ++;
	m_dPosition = m_iCurStep*1.0 / m_iStepCount;

	TermProgress(m_dPosition);
	m_bIsContinue = true;
	return true;
}


bool CConsoleProcess::SetPosition(double dPosition)
{
	m_dPosition = dPosition;
	TermProgress(m_dPosition);
	m_bIsContinue = true;
	return true;
}


void CConsoleProcess::SetMessage(const char* pszMsg)
{
	m_strMessage = pszMsg;
	printf("%s\n", pszMsg);
}
