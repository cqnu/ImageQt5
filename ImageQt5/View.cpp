#include "view.h"

#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "document.h"
#include "Image/baseimage.h"

View::View(QWidget *parent) :
	QWidget(parent),
	imageCenter(0, 0),
	dragImage(false)
{
	setMouseTracking(true);
}

// Fit to window
void View::zoomFitWindow()
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage)
	{
		if (pImage->width() <= width() && pImage->height() <= height())
		{
			getDocument()->setZoomFactor(1.0f);
		}
		else
		{
			float zoomFactor = std::min(float(width()) / float(pImage->width()), float(height()) / float(pImage->height()));
			getDocument()->setZoomFactor(zoomFactor);
		}
	}
}

void View::zoomChanged(float zoomFactor, float oldFactor)
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return;

	float zoomChange = zoomFactor / oldFactor;

	QPoint offset = imageCenter - QPoint(width() / 2, height() / 2);
	offset *= (zoomChange - 1.0f);
	imageCenter += offset;

	// 能显示全的情况下将图像居中
	QRect rect = getImageRect();
	if (rect.left() >= 0 && rect.right() < width())
	{
		imageCenter.setX(width() / 2);
	}
	if (rect.top() >= 0 && rect.bottom() < height())
	{
		imageCenter.setY(height() / 2);
	}

	// Restrict image edge
	restrictImageEdge();
}

QRect View::getImageRect()
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return QRect();

	float zoomFactor = getDocument()->getZoomFactor();

	QRect rect;
	rect.setLeft(imageCenter.x() - pImage->width() * zoomFactor / 2.0f);
	rect.setRight(imageCenter.x() + pImage->width() * zoomFactor / 2.0f);
	rect.setTop(imageCenter.y() - pImage->height() * zoomFactor / 2.0f);
	rect.setBottom(imageCenter.y() + pImage->height() * zoomFactor / 2.0f);

	return rect;
}

MainWindow* View::getMainWindow() const
{
	QWidget* centralWidget = parentWidget();
	Q_ASSERT(centralWidget);

	MainWindow* mainWindow = dynamic_cast<MainWindow*>(centralWidget->parentWidget());
	Q_ASSERT(mainWindow);
	return mainWindow;
}

Document* View::getDocument() const
{
	return getMainWindow()->getDocument();
}

void View::paintEvent(QPaintEvent*)
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage)
	{
		QPainter draw(this);
		// Draw image
		QRect rect = getImageRect();
		draw.drawImage(rect, *pImage->getImageEntity());
	}
}

void View::resizeEvent(QResizeEvent*)
{
	imageCenter.setX(width() / 2);
	imageCenter.setY(height() / 2);
}

void View::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			mousePos = event->pos();
			dragImage = true;
		}
	}
}

void View::mouseMoveEvent(QMouseEvent* event)
{
	if (dragImage)
	{
		imageCenter += event->pos() - mousePos;

		mousePos = event->pos();

		// Restrict image edge
		restrictImageEdge();

		update();
	}
	else
	{
		// Show pixel status
		showPixelStatus(event->pos());
	}
}

void View::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mousePos = event->pos();
		dragImage = false;
	}
}

void View::wheelEvent(QWheelEvent* event)
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return;

	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		float zoomFactor = getDocument()->getZoomFactor();

		int delta = event->delta();
		if (delta > 0)
		{
			//	zoomFactor *= (1.0f + float(delta) / 1500.0f);
			zoomFactor *= 1.1f;
		}
		else
		{
			//	zoomFactor /= (1.0f + float(-delta) / 1500.0f);
			zoomFactor /= 1.1f;
		}
		getDocument()->setZoomFactor(zoomFactor);

		repaint();
	}
}

// Logic point to Image point
QPoint View::LPtoIP(const QPoint& point)
{
	QPoint ptImage(-1, -1);
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return ptImage;

	float x = point.x() - imageCenter.x();
	float y = point.y() - imageCenter.y();
	float zoomFactor = getDocument()->getZoomFactor();
	ptImage.setX(x / zoomFactor + pImage->width() / 2);
	ptImage.setY(y / zoomFactor + pImage->height() / 2);

	if (ptImage.x() < 0 || ptImage.x() >= pImage->width())
	{
		ptImage.setX(-1);
	}
	if (ptImage.y() < 0 || ptImage.y() >= pImage->height())
	{
		ptImage.setY(-1);
	}

	return ptImage;
}

// Image point to Logic point
QPoint View::IPtoLP(const QPoint& point)
{
	QPoint ptLogic(-1, -1);
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return ptLogic;

	float zoomFactor = getDocument()->getZoomFactor();
	ptLogic.setX((point.x() - pImage->width() / 2) * zoomFactor + imageCenter.x());
	ptLogic.setY((point.y() - pImage->height() / 2) * zoomFactor + imageCenter.y());

	return ptLogic;
}

QPointF View::IPtoLP(const QPointF& point)
{
	QPointF ptLogic(-1, -1);
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return ptLogic;

	float zoomFactor = getDocument()->getZoomFactor();
	ptLogic.setX((point.x() - pImage->width() / 2) * zoomFactor + imageCenter.x());
	ptLogic.setY((point.y() - pImage->height() / 2) * zoomFactor + imageCenter.y());

	return ptLogic;
}

// Reset image center point
void View::resetImageCenter()
{
	imageCenter.setX(width() / 2);
	imageCenter.setY(height() / 2);
}

// Restrict image edge
void View::restrictImageEdge()
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return;

	float zoomFactor = getDocument()->getZoomFactor();

	QRect rect = getImageRect();
	if (rect.left() > width() - IMAGE_MARGIN)
	{
		imageCenter.setX(width() - IMAGE_MARGIN + pImage->width() * zoomFactor / 2.0f);
	}
	else if (rect.right() < IMAGE_MARGIN)
	{
		imageCenter.setX(IMAGE_MARGIN - pImage->width() * zoomFactor / 2.0f);
	}

	if (rect.top() > height() - IMAGE_MARGIN)
	{
		imageCenter.setY(height() - IMAGE_MARGIN + pImage->height() * zoomFactor / 2.0f);
	}
	else if (rect.bottom() < IMAGE_MARGIN)
	{
		imageCenter.setY(IMAGE_MARGIN - pImage->height() * zoomFactor / 2.0f);
	}
}

// Show pixel status
void View::showPixelStatus(const QPoint& point)
{
	BaseImage* pImage = getDocument()->getImage();
	if (pImage == nullptr)
		return;

	QPoint pixelPoint = LPtoIP(point);
	if (pixelPoint.x() < 0 || pixelPoint.x() >= pImage->width() || pixelPoint.y() < 0 || pixelPoint.y() >= pImage->height())
	{
		getMainWindow()->clearPixelValue();
	}
	else
	{
		QRgb rgb = pImage->getPixel(pixelPoint);
		getMainWindow()->showPixelValue(pixelPoint, rgb);
	}
}
