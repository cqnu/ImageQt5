
#include "CurveProcessor.h"

CurveProcessor::CurveProcessor()
{

}

CurveProcessor::~CurveProcessor()
{

}

void CurveProcessor::ProcessGeneralImage(GeneralImage* image)
{
	assert(image);

}

template<typename Type>
void CurveProcessor::ProcessTemplate(TemplateImage<Type>* image)
{
	assert(image);

}

// Process float array
void CurveProcessor::ProcessArray(float* pArray, int width, int height, float minValue, float maxValue, uchar* pByte)
{
	assert(pArray && pByte);
}