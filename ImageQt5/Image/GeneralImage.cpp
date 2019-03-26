#include "generalimage.h"

GeneralImage::GeneralImage()
	: _backupImage(nullptr)
{

}

GeneralImage::GeneralImage(const QString& pathName)
	: BaseImage(pathName)
	, _backupImage(nullptr)
{
	_pImage = new QImage(pathName);
	_width = _pImage->width();
	_height = _pImage->height();
	_openSucceed = true;

	// Backup origin QImage
	backupImage();
}

GeneralImage::~GeneralImage()
{

}

// Histogram statistic
void GeneralImage::histogramStatistic()
{
	memset(_grayPixelNumber, 0, sizeof(uint) * 256);
	memset(_redPixelNumber, 0, sizeof(uint) * 256);
	memset(_greenPixelNumber, 0, sizeof(uint) * 256);
	memset(_bluePixelNumber, 0, sizeof(uint) * 256);

	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			QRgb value = getPixel(QPoint(i, j));
			_grayPixelNumber[(int)round(getValue(QPoint(i, j)))]++;
			_redPixelNumber[qRed(value)]++;
			_greenPixelNumber[qGreen(value)]++;
			_bluePixelNumber[qBlue(value)]++;
		}
	}

	// 灰度值0、1、2不统计, 置为0
	memset(_grayPixelNumber, 0, sizeof(uint) * 3);
	memset(_redPixelNumber, 0, sizeof(uint) * 3);
	memset(_greenPixelNumber, 0, sizeof(uint) * 3);
	memset(_bluePixelNumber, 0, sizeof(uint) * 3);
}

float GeneralImage::getValue(const QPoint& position) const
{
    QRgb pixel = getPixel(position);
    return 0.299f * qRed(pixel) + 0.587f * qGreen(pixel) + 0.114f * qBlue(pixel);
}

// Backup origin QImage
void GeneralImage::backupImage()
{
	if (_backupImage)
		delete _backupImage;

	_backupImage = new QImage(*_pImage);
}