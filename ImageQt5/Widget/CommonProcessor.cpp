
#include "CommonProcessor.h"

//#include "../Image/BaseImage.h"

CommonProcessor::CommonProcessor()
	: _brightness(0)
	, _contrast(0)
{

}

CommonProcessor::~CommonProcessor()
{

}

void CommonProcessor::ProcessGeneralImage(GeneralImage* image)
{
	assert(image);

	int width = image->width();
	int height = image->height();
	QImage* entityImage = image->getImageEntity();
	QImage* backupImageEntity = image->getBackupImage();
	uchar* pImageData = (uchar*)entityImage->bits();
	uchar* pBackupImageData = (uchar*)backupImageEntity->bits();
	int pitch = entityImage->bytesPerLine();
	int depth = entityImage->depth() / 8;

//	PIProgressInit(VS_PROGRESS_STATUS_BAR, _T("亮度&对比度"));

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width * depth; i++)
		{
			uchar* pPixel = pImageData + j * pitch + i;
			uchar* pBackupPixel = pBackupImageData + j * pitch + i;
			float fResult = (*(pBackupPixel)-127.0f) * (_contrast + 100) / 100.0f + 127.0f;
			fResult *= (100.0f + _brightness / 2.0f) / 100.0f;
			if (fResult >= 255)
			{
				*(pPixel) = 255;
			}
			else if (fResult <= 0)
			{
				*(pPixel) = 0;
			}
			else
			{
				*(pPixel) = round(fResult);
			}
		}

	//	PIProgressSetPercent((j + 1), nHeight);
	}

//	PIProgressDone();*/
}

template<typename Type>
void CommonProcessor::ProcessTemplate(TemplateImage<Type>* pImage)
{
	assert(pImage);

/*	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	Type* pProcessingData = pImage->GetProcessingData();
	BYTE* pBYTEImage = pImage->GetBYTEImage();
	Type fMaxValue = pImage->GetMaximumValue();
	Type fMinValue = pImage->GetMinimumValue();

	float fAverage = float(fMinValue + fMaxValue) / 2.0f;
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
		float fResult = float(pProcessingData[i] - fAverage) * (m_nContrast + 100) / 100.0f + fAverage;
		fResult *= (100.0f + m_nBrightness / 2.0f) / 100.0f;
		if (fResult >= fMaxValue)
		{
			pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] = 255;
		}
		else if (fResult <= fMinValue)
		{
			pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] = 0;
		}
		else
		{
			pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] = BYTE((fResult - fMinValue) * fVariable);
		}
	}

	// 拷贝到图像
	pImage->CopyToImage();*/
}

// 处理float数组
void CommonProcessor::ProcessArray(float* pArray, int width, int height, float minValue, float maxValue, unsigned char* pByte)
{
	assert(pArray && pByte);

/*	float fAverage = float(minValue + maxValue) / 2.0f;
	float fVariable;
	if (maxValue != minValue)
	{
		fVariable = 255.0f / float(maxValue - minValue);
	}
	else
	{
		fVariable = 0.0f;
	}

	for (int i = 0; i < width * height; i++)
	{
		float fResult = float(pArray[i] - fAverage) * (m_nContrast + 100) / 100.0f + fAverage;
		fResult *= (100.0f + m_nBrightness / 2.0f) / 100.0f;
		if (fResult >= maxValue)
		{
			pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = 255;
		}
		else if (fResult <= minValue)
		{
			pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = 0;
		}
		else
		{
			pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = BYTE((fResult - minValue) * fVariable);
		}
	}*/
}

void CommonProcessor::SetBrightnessAndContrast(int brightness, int contrast)
{
	_brightness = brightness;
	_contrast = contrast;
}