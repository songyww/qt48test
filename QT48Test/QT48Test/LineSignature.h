#pragma once
#include <cv.h>
#include <highgui.h>

class __declspec(dllexport) LineSignature
{
public:
	LineSignature(void);
	~LineSignature(void);
	void MatchImage(IplImage *pImg1, IplImage *pImg2, int numLimit, double *pLineMatches, int &nLineMatches);
};
