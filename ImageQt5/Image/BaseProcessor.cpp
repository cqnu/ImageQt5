
#include "stdafx.h"
#include "VSBaseProcessor.h"

#include <typeinfo.h>
#include "VSGeneralImage.h"
#include "VSFloatScanImage.h"
#include "VSShortScanImage.h"
#include "VSRegionImage.h"

CVSBaseProcessor* CVSBaseProcessor::m_pCurrentProcessor = NULL;

CVSBaseProcessor::CVSBaseProcessor()
{
	m_pCurrentProcessor = this;
}

CVSBaseProcessor::~CVSBaseProcessor()
{

}

CVSBaseProcessor* CVSBaseProcessor::GetProcessor()
{
	return m_pCurrentProcessor;
}

void CVSBaseProcessor::Process(CVSBaseImage* pImage)
{
	SetCurrentProcessor();
	
	if (typeid(*pImage) == typeid(CVSGeneralImage))
	{
		CVSGeneralImage* pGeneralImage = dynamic_cast<CVSGeneralImage*>(pImage);
		ProcessGeneralImage(pGeneralImage);
	}
	else if (dynamic_cast<CVSTemplateImage<float>*>(pImage))
	{
		CVSTemplateImage<float>* pFloatImage = dynamic_cast<CVSTemplateImage<float>*>(pImage);
		ASSERT(pFloatImage);
		ProcessFloatImage(pFloatImage);
	}
	else if (dynamic_cast<CVSTemplateImage<unsigned short>*>(pImage))
	{
		CVSTemplateImage<unsigned short>* pUShortImage = dynamic_cast<CVSTemplateImage<unsigned short>*>(pImage);
		ASSERT(pUShortImage);
		ProcessUShortImage(pUShortImage);
	}
	else if (dynamic_cast<CVSTemplateImage<unsigned char>*>(pImage))
	{
		CVSTemplateImage<unsigned char>* pUCharImage = dynamic_cast<CVSTemplateImage<unsigned char>*>(pImage);
		ASSERT(pUCharImage);
		ProcessUCharImage(pUCharImage);
	}
	else if (dynamic_cast<CVSTemplateImage<short>*>(pImage))
	{
		CVSTemplateImage<short>* pShortImage = dynamic_cast<CVSTemplateImage<short>*>(pImage);
		ASSERT(pShortImage);
		ProcessShortImage(pShortImage);
	}
	else if (dynamic_cast<CVSTemplateImage<int>*>(pImage))
	{
		CVSTemplateImage<int>* pIntImage = dynamic_cast<CVSTemplateImage<int>*>(pImage);
		ASSERT(pIntImage);
		ProcessIntImage(pIntImage);
	}
	else if (dynamic_cast<CVSTemplateImage<unsigned int>*>(pImage))
	{
		CVSTemplateImage<unsigned int>* pUIntImage = dynamic_cast<CVSTemplateImage<unsigned int>*>(pImage);
		ASSERT(pUIntImage);
		ProcessUIntImage(pUIntImage);
	}
	else if (dynamic_cast<CVSTemplateImage<double>*>(pImage))
	{
		CVSTemplateImage<double>* pDoubleImage = dynamic_cast<CVSTemplateImage<double>*>(pImage);
		ASSERT(pDoubleImage);
		ProcessDoubleImage(pDoubleImage);
	}
	else if (typeid(*pImage) == typeid(CVSRegionImage))
	{
		CVSRegionImage* pRegionImage = dynamic_cast<CVSRegionImage*>(pImage);
		ASSERT(pRegionImage);
		ProcessRegionImage(pRegionImage);
	}
}

void CVSBaseProcessor::ProcessRegionImage(CVSRegionImage* pImage)
{
	CVSRegionImage* pRegionImage = dynamic_cast<CVSRegionImage*>(pImage);
	ASSERT(pRegionImage);

	Process(pRegionImage->GetImplImage());
}

CVSBaseProcessor* CVSBaseProcessor::SetCurrentProcessor()
{
	CVSBaseProcessor* pOldProcessor = m_pCurrentProcessor;
	m_pCurrentProcessor = this;
	return pOldProcessor;
}

void CVSBaseProcessor::ConvertToByte(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, BYTE* pByte)
{
	ASSERT(pArray && pByte);

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
		pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = BYTE((pArray[i] - fMinValue) * fVariable);
	}
}