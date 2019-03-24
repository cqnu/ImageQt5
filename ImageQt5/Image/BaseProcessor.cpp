
#include "BaseProcessor.h"

#include <typeinfo.h>
#include "GeneralImage.h"
//#include "FloatScanImage.h"
//#include "ShortScanImage.h"
//#include "RegionImage.h"

BaseProcessor* BaseProcessor::_currentProcessor = NULL;

BaseProcessor::BaseProcessor()
{
	_currentProcessor = this;
}

BaseProcessor::~BaseProcessor()
{

}

BaseProcessor* BaseProcessor::GetProcessor()
{
	return _currentProcessor;
}

void BaseProcessor::Process(BaseImage* pImage)
{
	SetCurrentProcessor();
	
	if (typeid(*pImage) == typeid(GeneralImage))
	{
		GeneralImage* pGeneralImage = dynamic_cast<GeneralImage*>(pImage);
		ProcessGeneralImage(pGeneralImage);
	}
	else if (dynamic_cast<TemplateImage<float>*>(pImage))
	{
		TemplateImage<float>* pFloatImage = dynamic_cast<TemplateImage<float>*>(pImage);
		assert(pFloatImage);
		ProcessFloatImage(pFloatImage);
	}
	else if (dynamic_cast<TemplateImage<unsigned short>*>(pImage))
	{
		TemplateImage<unsigned short>* pUShortImage = dynamic_cast<TemplateImage<unsigned short>*>(pImage);
		assert(pUShortImage);
		ProcessUShortImage(pUShortImage);
	}
	else if (dynamic_cast<TemplateImage<unsigned char>*>(pImage))
	{
		TemplateImage<unsigned char>* pUCharImage = dynamic_cast<TemplateImage<unsigned char>*>(pImage);
		assert(pUCharImage);
		ProcessUCharImage(pUCharImage);
	}
	else if (dynamic_cast<TemplateImage<short>*>(pImage))
	{
		TemplateImage<short>* pShortImage = dynamic_cast<TemplateImage<short>*>(pImage);
		assert(pShortImage);
		ProcessShortImage(pShortImage);
	}
	else if (dynamic_cast<TemplateImage<int>*>(pImage))
	{
		TemplateImage<int>* pIntImage = dynamic_cast<TemplateImage<int>*>(pImage);
		assert(pIntImage);
		ProcessIntImage(pIntImage);
	}
	else if (dynamic_cast<TemplateImage<unsigned int>*>(pImage))
	{
		TemplateImage<unsigned int>* pUIntImage = dynamic_cast<TemplateImage<unsigned int>*>(pImage);
		assert(pUIntImage);
		ProcessUIntImage(pUIntImage);
	}
	else if (dynamic_cast<TemplateImage<double>*>(pImage))
	{
		TemplateImage<double>* pDoubleImage = dynamic_cast<TemplateImage<double>*>(pImage);
		assert(pDoubleImage);
		ProcessDoubleImage(pDoubleImage);
	}
/*	else if (typeid(*pImage) == typeid(RegionImage))
	{
		RegionImage* pRegionImage = dynamic_cast<RegionImage*>(pImage);
		assert(pRegionImage);
		ProcessRegionImage(pRegionImage);
	}*/
}
/* TODO
void BaseProcessor::ProcessRegionImage(RegionImage* pImage)
{
	RegionImage* pRegionImage = dynamic_cast<RegionImage*>(pImage);
	assert(pRegionImage);

	Process(pRegionImage->GetImplImage());
}*/

BaseProcessor* BaseProcessor::SetCurrentProcessor()
{
	BaseProcessor* oldProcessor = _currentProcessor;
	_currentProcessor = this;
	return oldProcessor;
}

void BaseProcessor::ConvertToByte(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, unsigned char* pByte)
{
	assert(pArray && pByte);

	// 常数, 作为一个临时变量拿到for循环外
	float fVariable;
	if (fMaxValue != fMinValue)
	{
		fVariable = 255.0f / float(fMaxValue - fMinValue);
	}
	else
	{
		fVariable = 0.0f;
	}

	for (int i = 0; i < nWidth * nHeight; i++)
	{
		pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = unsigned char((pArray[i] - fMinValue) * fVariable);
	}
}