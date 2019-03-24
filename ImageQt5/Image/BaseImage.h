#ifndef BASEIMAGE_H
#define BASEIMAGE_H

#include <QString>
#include <QImage>

class BaseImage
{
public:
	BaseImage();
	BaseImage(const QString& pathName);
	virtual ~BaseImage();

public:
	QImage* getImageEntity() const	{ return _pImage; }

	int width() const				{ return _width; }

	int height() const				{ return _height; }

	virtual int slice() const		{ return 1; }

	bool isOpenSucceed()			{ return _openSucceed; }

    QRgb getPixel(const QPoint& position) const;

    virtual float getValue(const QPoint& position) const = 0;

    void copyToArray(uchar* array);

    bool copyFromArray(uchar* byteImage, int width, int height);

protected:
	QImage* _pImage;

	int _width, _height;

	QString _pathName;

	bool _openSucceed;
};

#endif // BASEIMAGE_H
