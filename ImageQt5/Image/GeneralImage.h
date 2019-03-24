#ifndef GENERALIMAGE_H
#define GENERALIMAGE_H

#include "baseimage.h"

class GeneralImage : public BaseImage
{
public:
	GeneralImage();
	GeneralImage(const QString& pathName);
	virtual ~GeneralImage();

public:
	// Get backup QImage pointer
	QImage* getBackupImage() const { return _backupImage; }

    virtual float getValue(const QPoint& position) const;

private:
	// 得到图像中最大最小的像素值
	void getImageBottomAndTop();

	// Backup origin QImage
	void backupImage();

private:
	// Backup origin QImage
	QImage* _backupImage;
};

#endif // GENERALIMAGE_H
