#include "globalfunc.h"

bool copyByteToImage(uchar* byteImage, int width, int height, QImage* pImage)
{
	if (byteImage == NULL || pImage == NULL)
		return false;

	if (width != pImage->width() || height != pImage->height())
		return false;

	uchar* pData = pImage->bits();
	int pitch = pImage->bytesPerLine();
	int depth = pImage->depth() / 8;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width * depth; i++)
		{
			uchar* pixel = pData + j * pitch + i;
			*pixel = byteImage[(j * width) * depth + i];
		}
	}

	return true;
}
