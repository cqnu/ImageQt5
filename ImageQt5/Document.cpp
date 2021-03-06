﻿#include "document.h"
#include "mainwindow.h"
#include "view.h"
#include "Image/baseimage.h"
#include "Image/generalimage.h"
#include "Image/scanimage.h"

Document::Document(MainWindow* pWindow) :
	pMainWindow(pWindow),
	_image(nullptr),
	_zoomFactor(1.0f)
{

}

Document::~Document()
{

}

bool Document::openFile(const QString& fileName)
{
	if (_image)
	{
		closeFile();
	}

	int type = findType(fileName);
	if (type == IMAGE_FORMAT_NDR || type == IMAGE_FORMAT_NCT)
	{
		_image = std::make_shared<ScanImage>(fileName);
	}
	else if (type != IMAGE_FORMAT_UNKNOWN)
	{
		_image = std::make_shared<GeneralImage>(fileName);
	}
	else
	{
		_image = nullptr;
		return false;
	}

	// Judge whether open file successfully
	if (_image->isOpenSucceed() == false)
		return false;

	_image->histogramStatistic();

	getView()->zoomFitWindow();
	getView()->repaint();

	return true;
}

int Document::findType(const QString &fileName)
{
	QString str = fileName.toLower();
	if (str.endsWith(".jpg") || str.endsWith(".jpeg"))
	{
		return IMAGE_FORMAT_JPG;
	}
	else if (str.endsWith(".png"))
	{
		return IMAGE_FORMAT_PNG;
	}
	else if (str.endsWith(".tif") || str.endsWith(".tiff"))
	{
		return IMAGE_FORMAT_TIF;
	}
	else if (str.endsWith(".bmp"))
	{
		return IMAGE_FORMAT_BMP;
	}
	else if (str.endsWith(".GIF"))
	{
		return IMAGE_FORMAT_GIF;
	}
	else if (str.endsWith(".dr"))
	{
		return IMAGE_FORMAT_NDR;
	}
	else if (str.endsWith(".ct"))
	{
		return IMAGE_FORMAT_NCT;
	}
	else if (str.endsWith(".raw"))
	{
		return IMAGE_FORMAT_RAW;
	}
	else if (str.endsWith(".dat"))
	{
		return IMAGE_FORMAT_DAT;
	}

	return IMAGE_FORMAT_UNKNOWN;
}

bool Document::saveAs(const QString& fileName)
{
	if (_image)
	{
		return _image->getImageEntity()->save(fileName);
	}
	else
	{
		return false;
	}
}

void Document::closeFile()
{
	_image.reset();

	getView()->resetImageCenter();
	getView()->repaint();
}

void Document::copyImage(const std::shared_ptr<BaseImage>& image)
{
	if (_image)
	{
		closeFile();
	}

	_image = image;

	_image->histogramStatistic();

	getView()->zoomFitWindow();
	getView()->repaint();
}

View* Document::getView() const
{
	return pMainWindow->getView();
}

void Document::setZoomFactor(float factor)
{
	float oldFactor = _zoomFactor;
	if (factor >= IMAGE_MAX_ZOOM)
	{
		_zoomFactor = IMAGE_MAX_ZOOM;
	}
	else if (factor <= IMAGE_MIN_ZOOM)
	{
		_zoomFactor = IMAGE_MIN_ZOOM;
	}
	else
	{
		_zoomFactor = factor;
	}

	getView()->zoomChanged(_zoomFactor, oldFactor);
}

// Repaint view
void Document::repaintView()
{
	getView()->repaint();
}