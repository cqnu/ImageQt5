#include "globalfunc.h"

#include <QApplication>
#include "mainwindow.h"
#include "Document.h"

MainWindow* getGlobalWindow()
{
	foreach(QWidget* w, qApp->topLevelWidgets())
		if (MainWindow* mainWin = qobject_cast<MainWindow*>(w))
			return mainWin;
	return nullptr;
}

Document* getGlobalDocument()
{
	MainWindow* mainWindow = getGlobalWindow();
	return mainWindow->getDocument();
}

BaseImage* getGlobalImage()
{
	Document* document = getGlobalDocument();
	if (document)
	{
		return document->getImage();
	}
	else
	{
		return nullptr;
	}
}

void repaintView()
{
	Document* document = getGlobalDocument();
	if (document)
	{
		document->repaintView();
	}
}

bool copyByteToImage(uchar* byteImage, int width, int height, QImage* pImage)
{
	if (byteImage == nullptr || pImage == nullptr)
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
