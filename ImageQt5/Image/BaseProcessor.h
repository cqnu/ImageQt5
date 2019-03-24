#pragma once

//#include "..\PluginDefine.h"
#include "GeneralImage.h"
#include "TemplateImage.h"

#define DECLARE_TEMPLATE_INTERFACE \
public: \
	virtual void ProcessUCharImage(TemplateImage<unsigned char>* pImage) { ProcessTemplate<unsigned char>(pImage); } \
	virtual void ProcessShortImage(TemplateImage<short>* pImage) { ProcessTemplate<short>(pImage); } \
	virtual void ProcessUShortImage(TemplateImage<unsigned short>* pImage) { ProcessTemplate<unsigned short>(pImage); } \
	virtual void ProcessIntImage(TemplateImage<int>* pImage) { ProcessTemplate<int>(pImage); } \
	virtual void ProcessUIntImage(TemplateImage<unsigned int>* pImage) { ProcessTemplate<unsigned int>(pImage); } \
	virtual void ProcessFloatImage(TemplateImage<float>* pImage) { ProcessTemplate<float>(pImage); } \
	virtual void ProcessDoubleImage(TemplateImage<double>* pImage) { ProcessTemplate<double>(pImage); }

class BaseImage;
class GeneralImage;
class RegionImage;

// Base class of image processing algorithm
class BaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	BaseProcessor();
	~BaseProcessor();

public:
	static BaseProcessor* GetProcessor();

	BaseProcessor* SetCurrentProcessor();

	// Process image
	void Process(BaseImage* pImage);

	// Process float array
	virtual void ProcessArray(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, unsigned char* pByte)	{}

protected:
	virtual void ProcessGeneralImage(GeneralImage* pImage) {}

//	virtual void ProcessRegionImage(RegionImage* pImage);

	template<typename Type>
	void ProcessTemplate(TemplateImage<Type>* pImage)	{}

	// Á¿»¯Í¼Ïñ
	void ConvertToByte(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, unsigned char* pByte);

private:
	static BaseProcessor* _currentProcessor;
};