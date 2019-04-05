
#include "LevelsProcessor.h"

LevelsProcessor::LevelsProcessor()
	: _bottom(0)
	, _mid(0)
	, _top(0)
{

}

LevelsProcessor::~LevelsProcessor()
{

}

void LevelsProcessor::ProcessGeneralImage(GeneralImage* image)
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

	float bottom = _bottom;
	float mid = _mid;
	float top = _top;
	int nChannel = 0;

	int nMinColor = 0;
	int nMaxColor = 255;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
		/*	uchar* pPixel = pImageData + j * pitch + i * depth;
			uchar* pBackupPixel = pBackupImageData + j * pitch + i * depth;
			switch (nChannel)
			{
			case 0:
				*(pPixel) = pImage->CalcNewColor(*(pBackupPixel), bottom, top, mid, nMinColor, nMaxColor);
				*(pPixel + 1) = pImage->CalcNewColor(*(pBackupPixel + 1), bottom, top, mid, nMinColor, nMaxColor);
				*(pPixel + 2) = pImage->CalcNewColor(*(pBackupPixel + 2), bottom, top, mid, nMinColor, nMaxColor);
				break;
			case 1:
				*(pPixel + 2) = pImage->CalcNewColor(*(pBackupPixel + 2), bottom, top, mid, nMinColor, nMaxColor);
				break;
			case 2:
				*(pPixel + 1) = pImage->CalcNewColor(*(pBackupPixel + 1), bottom, top, mid, nMinColor, nMaxColor);
				break;
			case 3:
				*(pPixel) = pImage->CalcNewColor(*(pBackupPixel), bottom, top, mid, nMinColor, nMaxColor);
				break;
			}*/
		}
	}
}

template<typename Type>
void LevelsProcessor::ProcessTemplate(TemplateImage<Type>* image)
{
	assert(pImage);

	int width = image->width();
	int height = image->height();
	Type* pProcessingData = image->GetProcessingData();
	uchar* pBYTEImage = image->getBYTEImage();
	Type maxValue = image->getMaximumValue();
	Type minValue = image->getMinimumValue();

	float bottom = _bottom;
	float mid = _mid;
	float top = _top;
	int channel = 0;

	// 常数, 作为一个临时变量拿到for循环外
	float variable1 = 255.0f / (float)(top - bottom);
	int midColor = round(255 * mid / (1 + mid));
	float variable2 = (float)(midColor) / (float)((bottom + top) / 2.0f - bottom);
	float variable3 = (float)(255.0f - midColor) / (float)(top - (bottom + top) / 2.0f);

/*	for (int i = 0; i < width * height; i++)
	{
		if (pProcessingData[i] <= fBottom)
		{
			switch (nChannel)
			{
			case 0:
				pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] = 0;
				break;
			case 1:
				pBYTEImage[3 * i + 2] = 0;
				break;
			case 2:
				pBYTEImage[3 * i + 1] = 0;
				break;
			case 3:
				pBYTEImage[3 * i] = 0;
				break;
			}
		}
		else if (pProcessingData[i] >= fTop)
		{
			switch (nChannel)
			{
			case 0:
				pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] = 255;
				break;
			case 1:
				pBYTEImage[3 * i + 2] = 255;
				break;
			case 2:
				pBYTEImage[3 * i + 1] = 255;
				break;
			case 3:
				pBYTEImage[3 * i] = 255;
				break;
			}
		}
		else
		{
			if (fMid == 1)
			{
				switch (nChannel)
				{
				case 0:
					pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] =
						BYTE((pProcessingData[i] - fBottom) * fVariable1);
					break;
				case 1:
					pBYTEImage[3 * i + 2] = BYTE((pProcessingData[i] - fBottom) * fVariable1);
					break;
				case 2:
					pBYTEImage[3 * i + 1] = BYTE((pProcessingData[i] - fBottom) * fVariable1);
					break;
				case 3:
					pBYTEImage[3 * i] = BYTE((pProcessingData[i] - fBottom) * fVariable1);
					break;
				}
			}
			else	// 参数fMid不为1的情况
			{
				if (pProcessingData[i] < (fBottom + fTop) / 2)
				{
					switch (nChannel)
					{
					case 0:
						pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] =
							BYTE((pProcessingData[i] - fBottom) * fVariable2);
						break;
					case 1:
						pBYTEImage[3 * i + 2] = BYTE((pProcessingData[i] - fBottom) * fVariable2);
						break;
					case 2:
						pBYTEImage[3 * i + 1] = BYTE((pProcessingData[i] - fBottom) * fVariable2);
						break;
					case 3:
						pBYTEImage[3 * i] = BYTE((pProcessingData[i] - fBottom) * fVariable2);
						break;
					}
				}
				else
				{
					switch (nChannel)
					{
					case 0:
						pBYTEImage[3 * i] = pBYTEImage[3 * i + 1] = pBYTEImage[3 * i + 2] =
							BYTE((pProcessingData[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 1:
						pBYTEImage[3 * i + 2] = BYTE((pProcessingData[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 2:
						pBYTEImage[3 * i + 1] = BYTE((pProcessingData[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 3:
						pBYTEImage[3 * i] = BYTE((pProcessingData[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					}
				}
			}
		}
	}

	// 拷贝到图像
	pImage->CopyToImage();*/
}

// Process float array
void LevelsProcessor::ProcessArray(float* pArray, int width, int height, float minValue, float maxValue, uchar* pByte)
{
	assert(pArray && pByte);

	float bottom = _bottom;
	float mid = _mid;
	float top = _top;
	int channel = 0;

/*	// 常数, 作为一个临时变量拿到for循环外
	float fVariable1 = 255.0f / (float)(fTop - fBottom);
	int nMidColor = FloatToInt(255 * fMid / (1 + fMid));
	float fVariable2 = (float)(nMidColor) / (float)((fBottom + fTop) / 2.0f - fBottom);
	float fVariable3 = (float)(255.0f - nMidColor) / (float)(fTop - (fBottom + fTop) / 2.0f);

	for (int i = 0; i < width * height; i++)
	{
		if (pArray[i] <= fBottom)
		{
			switch (nChannel)
			{
			case 0:
				pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = 0;
				break;
			case 1:
				pByte[3 * i + 2] = 0;
				break;
			case 2:
				pByte[3 * i + 1] = 0;
				break;
			case 3:
				pByte[3 * i] = 0;
				break;
			}
		}
		else if (pArray[i] >= fTop)
		{
			switch (nChannel)
			{
			case 0:
				pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] = 255;
				break;
			case 1:
				pByte[3 * i + 2] = 255;
				break;
			case 2:
				pByte[3 * i + 1] = 255;
				break;
			case 3:
				pByte[3 * i] = 255;
				break;
			}
		}
		else
		{
			if (fMid == 1)
			{
				switch (nChannel)
				{
				case 0:
					pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] =
						BYTE((pArray[i] - fBottom) * fVariable1);
					break;
				case 1:
					pByte[3 * i + 2] = BYTE((pArray[i] - fBottom) * fVariable1);
					break;
				case 2:
					pByte[3 * i + 1] = BYTE((pArray[i] - fBottom) * fVariable1);
					break;
				case 3:
					pByte[3 * i] = BYTE((pArray[i] - fBottom) * fVariable1);
					break;
				}
			}
			else	// 参数fMid不为1的情况
			{
				if (pArray[i] < (fBottom + fTop) / 2)
				{
					switch (nChannel)
					{
					case 0:
						pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] =
							BYTE((pArray[i] - fBottom) * fVariable2);
						break;
					case 1:
						pByte[3 * i + 2] = BYTE((pArray[i] - fBottom) * fVariable2);
						break;
					case 2:
						pByte[3 * i + 1] = BYTE((pArray[i] - fBottom) * fVariable2);
						break;
					case 3:
						pByte[3 * i] = BYTE((pArray[i] - fBottom) * fVariable2);
						break;
					}
				}
				else
				{
					switch (nChannel)
					{
					case 0:
						pByte[3 * i] = pByte[3 * i + 1] = pByte[3 * i + 2] =
							BYTE((pArray[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 1:
						pByte[3 * i + 2] = BYTE((pArray[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 2:
						pByte[3 * i + 1] = BYTE((pArray[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					case 3:
						pByte[3 * i] = BYTE((pArray[i] - (fBottom + fTop) / 2) * fVariable3 + nMidColor);
						break;
					}
				}
			}
		}
	}*/
}

void LevelsProcessor::setPara(float bottom, float mid, float top)
{
	_bottom = bottom;
	_mid = mid;
	_top = top;
}