#pragma once

#include "..\PluginDefine.h"
#include "VSTemplateImage.h"

#define DECLARE_TEMPLATE_INTERFACE \
public: \
	virtual void ProcessUCharImage(CVSTemplateImage<unsigned char>* pImage) { ProcessTemplate<unsigned char>(pImage); } \
	virtual void ProcessShortImage(CVSTemplateImage<short>* pImage) { ProcessTemplate<short>(pImage); } \
	virtual void ProcessUShortImage(CVSTemplateImage<unsigned short>* pImage) { ProcessTemplate<unsigned short>(pImage); } \
	virtual void ProcessIntImage(CVSTemplateImage<int>* pImage) { ProcessTemplate<int>(pImage); } \
	virtual void ProcessUIntImage(CVSTemplateImage<unsigned int>* pImage) { ProcessTemplate<unsigned int>(pImage); } \
	virtual void ProcessFloatImage(CVSTemplateImage<float>* pImage) { ProcessTemplate<float>(pImage); } \
	virtual void ProcessDoubleImage(CVSTemplateImage<double>* pImage) { ProcessTemplate<double>(pImage); }

class CVSBaseImage;
class CVSGeneralImage;
class CVSRegionImage;

// 图像处理器基类
class PLUGIN_EXT_CLASS CVSBaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	CVSBaseProcessor();
	~CVSBaseProcessor();

public:
	static CVSBaseProcessor* GetProcessor();

	CVSBaseProcessor* SetCurrentProcessor();

	// 处理图像
	void Process(CVSBaseImage* pImage);

	// 处理float数组
	virtual void ProcessArray(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, BYTE* pByte)	{}

protected:
	virtual void ProcessGeneralImage(CVSGeneralImage* pImage) {}

	virtual void ProcessRegionImage(CVSRegionImage* pImage);

	template<typename Type>
	void ProcessTemplate(CVSTemplateImage<Type>* pImage)	{}

	// 量化图像
	void ConvertToByte(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, BYTE* pByte);

private:
	static CVSBaseProcessor* m_pCurrentProcessor;
};