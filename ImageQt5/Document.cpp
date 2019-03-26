#include "document.h"
#include "mainwindow.h"
#include "view.h"
#include "Image/baseimage.h"
#include "Image/generalimage.h"
#include "Image/scanimage.h"

Document::Document(MainWindow* pWindow) :
	pMainWindow(pWindow),
	pBaseImage(nullptr),
	zoomFactor(1.0f)
{

}

Document::~Document()
{
	if (pBaseImage)
	{
		delete pBaseImage;
		pBaseImage = nullptr;
	}
}

bool Document::openFile(const QString& fileName)
{
	if (pBaseImage)
	{
		closeFile();
	}

	int type = findType(fileName);
	if (type == IMAGE_FORMAT_NDR || type == IMAGE_FORMAT_NCT)
	{
		pBaseImage = new ScanImage(fileName);
	}
	else if (type != IMAGE_FORMAT_UNKNOWN)
	{
		pBaseImage = new GeneralImage(fileName);
	}
	else
	{
		pBaseImage = nullptr;
		return false;
	}

	// Judge whether open file successfully
	if (pBaseImage->isOpenSucceed() == false)
		return false;

	pBaseImage->histogramStatistic();

	getView()->zoomFitWindow();
	getView()->repaint();

	return true;
}

int Document::findType(const QString &fileName)
{
	if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg"))
	{
		return IMAGE_FORMAT_JPG;
	}
	else if (fileName.endsWith(".png"))
	{
		return IMAGE_FORMAT_PNG;
	}
	else if (fileName.endsWith(".tif") || fileName.endsWith(".tiff"))
	{
		return IMAGE_FORMAT_TIF;
	}
	else if (fileName.endsWith(".bmp"))
	{
		return IMAGE_FORMAT_BMP;
	}
	else if (fileName.endsWith(".GIF"))
	{
		return IMAGE_FORMAT_GIF;
	}
	else if (fileName.endsWith(".dr"))
	{
		return IMAGE_FORMAT_NDR;
	}
	else if (fileName.endsWith(".ct"))
	{
		return IMAGE_FORMAT_NCT;
	}
	else if (fileName.endsWith(".raw"))
	{
		return IMAGE_FORMAT_RAW;
	}
	else if (fileName.endsWith(".dat"))
	{
		return IMAGE_FORMAT_DAT;
	}

	return IMAGE_FORMAT_UNKNOWN;
}

bool Document::saveAs(const QString& fileName)
{
	if (pBaseImage)
	{
		return pBaseImage->getImageEntity()->save(fileName);
	}
	else
	{
		return false;
	}
}

void Document::closeFile()
{
	if (pBaseImage)
	{
		delete pBaseImage;
		pBaseImage = nullptr;
	}

	getView()->resetImageCenter();
	getView()->repaint();
}

View* Document::getView() const
{
	return pMainWindow->getView();
}

void Document::setZoomFactor(float factor)
{
	float oldFactor = zoomFactor;
	if (factor >= IMAGE_MAX_ZOOM)
	{
		zoomFactor = IMAGE_MAX_ZOOM;
	}
	else if (factor <= IMAGE_MIN_ZOOM)
	{
		zoomFactor = IMAGE_MIN_ZOOM;
	}
	else
	{
		zoomFactor = factor;
	}

	getView()->zoomChanged(zoomFactor, oldFactor);
}

// Repaint view
void Document::repaintView()
{
	getView()->repaint();
}