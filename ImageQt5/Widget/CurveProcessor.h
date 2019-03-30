#pragma once

#include "../Image/BaseProcessor.h"

#ifndef CURVE_CHANNEL
#define CURVE_CHANNEL
#define CURVE_CHANNEL_GRAY		0
#define CURVE_CHANNEL_RED		1
#define CURVE_CHANNEL_GREEN		2
#define CURVE_CHANNEL_BLUE		3
#endif

class CurveProcessor : public BaseProcessor
{
	DECLARE_TEMPLATE_INTERFACE

public:
	CurveProcessor();
	~CurveProcessor();

protected:
	virtual void processGeneralImage(GeneralImage* pImage);

	template<typename Type>
	void processTemplate(TemplateImage<Type>* pImage);

	// Process float array
	virtual void processArray(float* pArray, int width, int height, float minValue, float maxValue, uchar* pByte);

public:
	void setChannel(int channel) { _channel = channel; }

	void setArray(int arrayNum, uint* arrayIntensity, uint* arrayRed, uint* arrayGreen, uint* arrayBlue);

private:
	// ≤Â÷µº∆À„
	uchar interpolation(uchar target, uint* array, int arrayNum, float variable);

private:
	int _channel;

	int _arrayNum;
	uint* _arrayIntensity;
	uint* _arrayRed;
	uint* _arrayGreen;
	uint* _arrayBlue;
};