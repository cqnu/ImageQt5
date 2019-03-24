#include "generalimage.h"

GeneralImage::GeneralImage()
{

}

GeneralImage::GeneralImage(const QString& pathName) :
	BaseImage(pathName)
{
	_pImage = new QImage(pathName);
	_width = _pImage->width();
	_height = _pImage->height();
	_openSucceed = true;
}

GeneralImage::~GeneralImage()
{

}

float GeneralImage::getValue(const QPoint& position) const
{
    QRgb pixel = getPixel(position);
    return 0.299f * qRed(pixel) + 0.587f * qGreen(pixel) + 0.114f * qBlue(pixel);
}
