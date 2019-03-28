#pragma once

#include "../Image/BaseProcessor.h"

class CurveProcessor : public BaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	CurveProcessor();
	~CurveProcessor();

protected:
	virtual void ProcessGeneralImage(GeneralImage* pImage);

	template<typename Type>
	void ProcessTemplate(TemplateImage<Type>* pImage);

	// Process float array
	virtual void ProcessArray(float* pArray, int width, int height, float minValue, float maxValue, uchar* pByte);

public:
//	void SetBrightnessAndContrast(int brightness, int contrast);

private:
//	int _brightness;
//	int _contrast;
};