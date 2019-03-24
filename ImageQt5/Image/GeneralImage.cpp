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