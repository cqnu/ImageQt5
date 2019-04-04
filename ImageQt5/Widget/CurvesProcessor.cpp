
#include "CurvesProcessor.h"

CurvesProcessor::CurvesProcessor()
{

}

CurvesProcessor::~CurvesProcessor()
{

}

void CurvesProcessor::processGeneralImage(GeneralImage* image)
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

//	PIProgressInit(VS_PROGRESS_STATUS_BAR, _T("曲线调制"));

	float variable = 255.0f / float(_arrayNum - 1);

	// 根据曲线，映射像素值
	if (_channel == CURVE_CHANNEL_GRAY)
	{
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width * depth; i++)
			{
				uchar* pPixel = pImageData + j * pitch + i;
				uchar* pBackupPixel = pBackupImageData + j * pitch + i;
				// Interpolation
				*(pPixel) = interpolation(*pBackupPixel, _arrayIntensity, _arrayNum, variable);
			}

		//	PIProgressSetPercent((j + 1), nHeight);
		}
	}
	else
	{
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				uchar* pPixel = pImageData + j * pitch + i * depth;
				uchar* pBackupPixel = pBackupImageData + j * pitch + i * depth;
				// Interpolation
				*(pPixel) = interpolation(*(pBackupPixel), _arrayBlue, _arrayNum, variable);
				*(pPixel + 1) = interpolation(*(pBackupPixel + 1), _arrayGreen, _arrayNum, variable);
				*(pPixel + 2) = interpolation(*(pBackupPixel + 2), _arrayRed, _arrayNum, variable);
			}

		//	PIProgressSetPercent((j + 1), nHeight);
		}
	}

//	PIProgressDone();
}

template<typename Type>
void CurvesProcessor::processTemplate(TemplateImage<Type>* image)
{
	assert(image);

}

// Process float array
void CurvesProcessor::processArray(float* pArray, int width, int height, float minValue, float maxValue, uchar* pByte)
{
	assert(pArray && pByte);
}

void CurvesProcessor::setArray(int arrayNum, uint* arrayIntensity, uint* arrayRed, uint* arrayGreen, uint* arrayBlue)
{
	_arrayNum = arrayNum;

	_arrayIntensity = arrayIntensity;
	_arrayRed = arrayRed;
	_arrayGreen = arrayGreen;
	_arrayBlue = arrayBlue;
}

// Interpolation
uchar CurvesProcessor::interpolation(uchar target, uint* array, int arrayNum, float variable)
{
	float percentage = target / variable;
	int integer = int(percentage);
	float fraction = percentage - integer;
	if (integer == arrayNum - 1)
	{
		return uchar(round(array[integer] * variable));
	}
	else
	{
		return uchar(round((array[integer] * (1.0f - fraction) + array[integer + 1] * fraction) * variable));
	}
}