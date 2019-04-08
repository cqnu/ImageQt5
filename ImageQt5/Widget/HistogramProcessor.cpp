
#include "HistogramProcessor.h"

HistogramProcessor::HistogramProcessor()
	: _array(nullptr)
{

}

HistogramProcessor::~HistogramProcessor()
{

}

void HistogramProcessor::processGeneralImage(GeneralImage* image)
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

	// 统计非零个数
	int count = 0;
	int min = _arrayNum - 1;
	int max = 0;
	for (int i = 0; i < _arrayNum; i++)
	{
		if (_array[i] == true)
		{
			if (min > i)
			{
				min = i;
			}
			if (max < i)
			{
				max = i;
			}
			count++;
		}
	}
	if (count == 0)
	{
		// Restore image by using backup image
		image->restoreImage();
		return;
	}

	uchar actualMin = round(min * 255.0f / (_arrayNum - 1));
	uchar actualMax = round(max * 255.0f / (_arrayNum - 1));

	float variable = float(_arrayNum - 1) / 255.0f;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width * depth; i++)
		{
			uchar* pPixel = pImageData + j * pitch + i;
			uchar* pBackupPixel = pBackupImageData + j * pitch + i;

			if (*(pBackupPixel) >= actualMax)
			{
				*(pPixel) = 255;
			}
			else if (*(pBackupPixel) <= actualMin)
			{
				*(pPixel) = 0;
			}
			else
			{
				int index = round(*(pBackupPixel) * variable);
				if (_array[index])
				{
					*(pPixel) = (*(pBackupPixel) - actualMin) * 255 / (actualMax - actualMin);
				}
				else
				{
					*(pPixel) = 0;
				}
			}
		}
	}
}

template<typename Type>
void HistogramProcessor::processTemplate(TemplateImage<Type>* image)
{
	assert(image);

	int width = image->width();
	int height = image->height();
	Type* pProcessingData = image->getProcessingData();
	uchar* pBYTEImage = image->getBYTEImage();
	Type maxValue = image->getMaximumValue();
	Type minValue = image->getMinimumValue();

}

// Process float array
void HistogramProcessor::processArray(float* array, int width, int height, float minValue, float maxValue, uchar* pByte)
{
	assert(array && pByte);

}

void HistogramProcessor::setWindowArray(bool* array, int arrayNum)
{
	_array = array;
	_arrayNum = arrayNum;
}