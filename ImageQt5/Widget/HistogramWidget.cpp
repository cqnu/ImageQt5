#include "HistogramWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "../GlobalFunc.h"

HistogramWidget::HistogramWidget(QWidget* parent)
	: QWidget(parent)
	, _width(256)
	, _height(100)
	, _histogramWidth(200)
{
	// Initialize cursor position
	_cursorPos[0] = 0;
	_cursorPos[1] = _histogramWidth / 2;
	_cursorPos[2] = _histogramWidth;
}

HistogramWidget::~HistogramWidget()
{

}

void HistogramWidget::reset()
{
	repaint();
}

QSize HistogramWidget::sizeHint() const
{
	return QSize(200, 150);
}

QSize HistogramWidget::minimumSizeHint() const
{
	return QSize(200, 150);
}

void HistogramWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	QSize size = event->size();
	_width = size.width();
	_height = size.height();
	
	repaint();

	// Emit signal to parent widget
	emit resize();
}

void HistogramWidget::paintEvent(QPaintEvent* /*event*/)
{
	paintCursor();
	paintHistogram();
}

void HistogramWidget::paintCursor()
{
	QPoint pt[3];
	pt[0].setX(_cursorPos[0] + HS_MARGIN);
	pt[0].setY(_height - 20);
	pt[1].setX(_cursorPos[0] + HS_MARGIN - CURSOR_SIZE);
	pt[1].setY(pt[0].y() + CURSOR_SIZE);
	pt[2].setX(_cursorPos[0] + HS_MARGIN + CURSOR_SIZE);
	pt[2].setY(pt[0].y() + CURSOR_SIZE);
	QPolygon polygon;
	polygon << pt[0] << pt[1] << pt[2];
	QPainter painter(this);
	painter.drawPolygon(polygon);

	pt[0].setX(_cursorPos[1] + HS_MARGIN);
	pt[0].setY(_height - 20);
	pt[1].setX(_cursorPos[1] + HS_MARGIN - CURSOR_SIZE);
	pt[1].setY(pt[0].y() + CURSOR_SIZE);
	pt[2].setX(_cursorPos[1] + HS_MARGIN + CURSOR_SIZE);
	pt[2].setY(pt[0].y() + CURSOR_SIZE);
	polygon.clear();
	polygon << pt[0] << pt[1] << pt[2];
	painter.drawPolygon(polygon);

	pt[0].setX(_cursorPos[2] + HS_MARGIN);
	pt[0].setY(_height - 20);
	pt[1].setX(_cursorPos[2] + HS_MARGIN - CURSOR_SIZE);
	pt[1].setY(pt[0].y() + CURSOR_SIZE);
	pt[2].setX(_cursorPos[2] + HS_MARGIN + CURSOR_SIZE);
	pt[2].setY(pt[0].y() + CURSOR_SIZE);
	polygon.clear();
	polygon << pt[0] << pt[1] << pt[2];
	painter.drawPolygon(polygon);
}

void HistogramWidget::paintHistogram()
{
	if (getGlobalDocument() == nullptr)
		return;
	
	QPainter painter(this);
	painter.setPen(QPen(Qt::blue));

	for (int i = 0; i < _width; i++)
	{
	//	painter.drawLine(i + _rectSquare.left(), _rectSquare.bottom(), i + _rectSquare.left(), _rectSquare.bottom() - _heightArray[i]);
	}
}

void HistogramWidget::mousePressEvent(QMouseEvent* event)
{
	QPoint point = event->pos();
	if (event->button() == Qt::LeftButton)
	{
		
	}
}

void HistogramWidget::mouseMoveEvent(QMouseEvent* event)
{
	QPoint point = event->pos();

	if ((event->buttons() & Qt::LeftButton) == false)
		return;
	
}

void HistogramWidget::mouseReleaseEvent(QMouseEvent* event)
{
	setCursor(Qt::ArrowCursor);
	// Update image
//	AfxBeginThread(UpdateImageThread, this);

	emit updateImage();
}