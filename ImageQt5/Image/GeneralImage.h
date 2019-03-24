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
    virtual float getValue(const QPoint& position) const;
};

#endif // GENERALIMAGE_H
