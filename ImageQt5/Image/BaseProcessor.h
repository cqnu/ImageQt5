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

// ͼ����������
class PLUGIN_EXT_CLASS CVSBaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	CVSBaseProcessor();
	~CVSBaseProcessor();

public:
	static CVSBaseProcessor* GetProcessor();

	CVSBaseProcessor* SetCurrentProcessor();

	// ����ͼ��
	void Process(CVSBaseImage* pImage);

	// ����float����
	virtual void ProcessArray(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, BYTE* pByte)	{}

protected:
	virtual void ProcessGeneralImage(CVSGeneralImage* pImage) {}

	virtual void ProcessRegionImage(CVSRegionImage* pImage);

	template<typename Type>
	void ProcessTemplate(CVSTemplateImage<Type>* pImage)	{}

	// ����ͼ��
	void ConvertToByte(float* pArray, int nWidth, int nHeight, float fMinValue, float fMaxValue, BYTE* pByte);

private:
	static CVSBaseProcessor* m_pCurrentProcessor;
};