#include "HistogramWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "../GlobalFunc.h"
#include "HistogramProcessor.h"

#define DRAG_NONE		-1
#define DRAG_CURSOR0	0
#define DRAG_CURSOR1	1
#define DRAG_CURSOR2	2
#define DRAG_HISTOGRAM	3

HistogramWidget::HistogramWidget(QWidget* parent)
	: QWidget(parent)
	, _heightArray(nullptr)
	, _histogramWidth(180)
	, _select(nullptr)
	, _selectTemp(nullptr)
	, _drag(DRAG_NONE)
{
	allocateMemory();

	// Initialize cursor position
	_cursorPos[0] = 0;
	_cursorPos[1] = _histogramWidth / 2;
	_cursorPos[2] = _histogramWidth;
}

HistogramWidget::~HistogramWidget()
{
	if (_heightArray)
	{
		delete _heightArray;
	}
	if (_select)
	{
		delete _select;
	}
	if (_selectTemp)
	{
		delete _selectTemp;
	}
}

void HistogramWidget::init()
{
	generateHistogram();
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
	_histogramWidth = size.width() - HS_MARGIN * 2;

	allocateMemory();

	generateHistogram();

	if (_bottom != _top)
	{
		float factor = (_bottom - _minValue) / (_maxValue - _minValue);
		factor = factor < 0 ? 0 : factor;
		_cursorPos[0] = round(factor * _histogramWidth);

		factor = (_top - _minValue) / (_maxValue - _minValue);
		factor = factor > 1 ? 1 : factor;
		_cursorPos[2] = round(factor * _histogramWidth);

		_cursorPos[1] = round((_cursorPos[2] - _cursorPos[0]) / (1.0f + _mid)) + _cursorPos[0];
	}
	
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
	int height = rect().height();

	QPoint pt[3];
	pt[0].setX(_cursorPos[0] + HS_MARGIN);
	pt[0].setY(height - 20);
	pt[1].setX(_cursorPos[0] + HS_MARGIN - CURSOR_SIZE);
	pt[1].setY(pt[0].y() + CURSOR_SIZE);
	pt[2].setX(_cursorPos[0] + HS_MARGIN + CURSOR_SIZE);
	pt[2].setY(pt[0].y() + CURSOR_SIZE);
	QPolygon polygon;
	polygon << pt[0] << pt[1] << pt[2];
	QPainter painter(this);
	painter.drawPolygon(polygon);

	pt[0].setX(_cursorPos[1] + HS_MARGIN);
	pt[0].setY(height - 20);
	pt[1].setX(_cursorPos[1] + HS_MARGIN - CURSOR_SIZE);
	pt[1].setY(pt[0].y() + CURSOR_SIZE);
	pt[2].setX(_cursorPos[1] + HS_MARGIN + CURSOR_SIZE);
	pt[2].setY(pt[0].y() + CURSOR_SIZE);
	polygon.clear();
	polygon << pt[0] << pt[1] << pt[2];
	painter.drawPolygon(polygon);

	pt[0].setX(_cursorPos[2] + HS_MARGIN);
	pt[0].setY(height - 20);
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
	
	// 绘制直方图
	if (_maxHeight == 0)
		return;

	QPainter painter(this);
	painter.setPen(QPen(Qt::blue));

	QRect rect = this->rect();

	// 绘制背景
	QPen newHighlightPen(qRgb(92, 92, 92));
	painter.setPen(newHighlightPen);
	for (int i = 0; i < _histogramWidth; i++)
	{
		if (_select[i] || _selectTemp[i])
		{
			painter.drawLine(i + rect.left(), rect.top() + HS_HEIGHT + 20 - 1, i + rect.left(), rect.top() + 10);
		}
	}

	// 绘制前景
	QPen newPen(qRgb(0, 255, 0));
	QPen newPen2(qRgb(81, 183, 255));
	for (int i = 0; i < _histogramWidth; i++)
	{
		if (_select[i] || _selectTemp[i])
		{
			painter.setPen(newPen2);
		}
		else
		{
			painter.setPen(newPen);
		}

		painter.drawLine(i + rect.left(), rect.top() + HS_HEIGHT + HS_MARGIN * 2 - 2,
						i + rect.left(), rect.top() + HS_HEIGHT + HS_MARGIN * 2 - indexToHeight(i) - 2);
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

void HistogramWidget::allocateMemory()
{
	if (_heightArray)
	{
		delete _heightArray;
	}
	if (_select)
	{
		delete _select;
	}
	if (_selectTemp)
	{
		delete _selectTemp;
	}

	_heightArray = new uint[256];
	_select = new bool[_histogramWidth];
	_selectTemp = new bool[_histogramWidth];
	memset(_select, 0, sizeof(bool) * _histogramWidth);
	memset(_selectTemp, 0, sizeof(bool) * _histogramWidth);

//	if (m_pWindowProcessor)
//	{
//		m_pWindowProcessor->SetWindowArray(m_pSelect, &m_nHistogramWidth);
//	}
}

void HistogramWidget::generateHistogram()
{
	BaseImage* image = getGlobalImage();
	if (image == nullptr)
		return;

	memcpy(_heightArray, image->getGrayPixelArray(), sizeof(uint) * 256);

	_minHeight = _maxHeight = _heightArray[0];
	// 查找m_pHeightArray中的最大值和最小值
	for (int i = 0; i < 256; i++)
	{
		if (_maxHeight < _heightArray[i])
		{
			_maxHeight = _heightArray[i];
		}
		if (_minHeight > _heightArray[i])
		{
			_minHeight = _heightArray[i];
		}
	}
	// 防止图像中所有数据均为0的情况出错
	if (_maxHeight == 0 && _minHeight == 0)
		return;

	// 相对高度量化为绝对高度
	for (int i = 0; i < 256; i++)
	{
		_heightArray[i] = (_heightArray[i] - _minHeight) * (HS_HEIGHT - 1) / (_maxHeight - _minHeight) + 1;
	}

	repaint();
}

// 索引号转为高度
int HistogramWidget::indexToHeight(int i)
{
	float pos = float(i) * (256.0f - 1.0f) / (_histogramWidth - 1);
	int integer = int(floor(pos));
	float fraction = pos - floor(pos);

	if (integer == 255)
	{
		return _heightArray[255];
	}
	else
	{
		float fHeight = (1.0f - fraction) * _heightArray[integer] + fraction * _heightArray[integer + 1];
		return round(fHeight);
	}
}