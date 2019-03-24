#pragma once

#include "../Image/BaseProcessor.h"

class CommonProcessor : public BaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	CommonProcessor();
	~CommonProcessor();

protected:
	virtual void ProcessGeneralImage(GeneralImage* pImage);

	template<typename Type>
	void ProcessTemplate(TemplateImage<Type>* pImage);

	// ����float����
	virtual void ProcessArray(float* pArray, int width, int height, float minValue, float maxValue, unsigned char* pByte);

public:
	void SetBrightnessAndContrast(int brightness, int contrast);

private:
	int _brightness;
	int _contrast;
};