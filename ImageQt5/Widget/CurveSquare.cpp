#include "CurveSquare.h"

#include <QPainter>
#include "../GlobalFunc.h"

CurveSquare::CurveSquare(QWidget* parent)
	: QWidget(parent)
	, _rectSquare(30, 0, AREAWIDTH, AREAWIDTH)
	, _channel(0)
	, _activePegIndex(0)
{
	_heightArray = new uint[AREAWIDTH];
	memset(_heightArray, 0, sizeof(uint) * AREAWIDTH);

	_ownerPegs.append(Peg(0, AREAWIDTH));
	_ownerPegs.append(Peg(AREAWIDTH, 0));
	_activePegs = &_ownerPegs;

	// Initialize array
	for (int i = 0; i < AREAWIDTH; i++)
	{
		_arrayIntensity[i] = _arrayRed[i] = _arrayGreen[i] = _arrayBlue[i] = i;
	}
	_activeArray = _arrayIntensity;
}

CurveSquare::~CurveSquare()
{
	if (_heightArray)
	{
		delete[] _heightArray;
	}
}

void CurveSquare::init()
{
	BaseImage* image = getGlobalImage();

	// 根据活动通道更新绘制直方图
	switch (_channel)
	{
	case CURVE_CHANNEL_GRAY:
	{
	//	setActivePegArray(m_pegsIntensity);
	//	setActiveCurveArray(pWidget->GetIntensityArray());
	//	generateHistogram(image->getGrayPixelArray());	// 更新直方图
	}
	break;
	case CURVE_CHANNEL_RED:
	{
	//	setActivePegArray(m_pegsRed);
	//	setActiveCurveArray(pWidget->GetRedArray());
	//	generateHistogram(image->getRedPixelArray());
	}
	break;
	case CURVE_CHANNEL_GREEN:
	{
	//	setActivePegArray(m_pegsGreen);
	//	setActiveCurveArray(pWidget->GetGreenArray());
	//	generateHistogram(image->getGreenPixelArray());
	}
	break;
	case CURVE_CHANNEL_BLUE:
	{
	//	setActivePegArray(m_pegsBlue);
	//	setActiveCurveArray(pWidget->GetBlueArray());
	//	generateHistogram(image->getBluePixelArray());
	}
	break;
	}
}

void CurveSquare::reset()
{

}

QSize CurveSquare::sizeHint() const
{
	return QSize(256, 256);
}

QSize CurveSquare::minimumSizeHint() const
{
	return QSize(256, 256);
}

void CurveSquare::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);

	paintHistogram();
	paintBackground();
}

void CurveSquare::paintHistogram()
{
	if (getGlobalDocument() == nullptr)
		return;

	if (_maxHeight == 0)
		return;

	QPen pen(Qt::blue);
	
	QPainter painter(this);
	painter.setPen(pen);

	for (int i = 0; i < AREAWIDTH; i++)
	{
		painter.drawLine(i + _rectSquare.left(), _rectSquare.bottom(), i + _rectSquare.left(), _rectSquare.bottom() - _heightArray[i]);
	}
}

// Paint grid
void CurveSquare::paintBackground()
{
	QPainter painter(this);

	// Draw a horizontal ribbon and a vertical ribbon
	int gap = 6;
	QPoint point(_rectSquare.left() - gap, _rectSquare.top());
	int colorWidth = 15;
	for (int i = 0; i < AREAWIDTH; i++)
	{
		int j = 255 - i * 255 / (AREAWIDTH - 1);
		QPen pen(QColor(j, j, j));
		painter.setPen(pen);
		painter.drawLine(point.x() - colorWidth, point.y() + i, point.x(), point.y() + i);
	}

	point = QPoint(_rectSquare.left(), _rectSquare.bottom() + gap);
	for (int i = 0; i < AREAWIDTH; i++)
	{
		int j = i * 255 / (AREAWIDTH - 1);
		QPen pen(QColor(j, j, j));
		painter.setPen(pen);
		painter.drawLine(point.x() + i, point.y(), point.x() + i, point.y() + colorWidth);
	}

	// Draw square, three horizontal lines and three vertical lines
	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.drawLine(_rectSquare.topLeft(), _rectSquare.topRight());
	painter.drawLine(_rectSquare.topRight(), _rectSquare.bottomRight());
	painter.drawLine(_rectSquare.bottomLeft(), _rectSquare.bottomRight());
	painter.drawLine(_rectSquare.topLeft(), _rectSquare.bottomLeft());
	
	pen.setStyle(Qt::DashLine);
	painter.setPen(pen);
	painter.drawLine(QPoint(_rectSquare.left(), _rectSquare.top() + AREAWIDTH / 4),
		QPoint(_rectSquare.right(), _rectSquare.top() + AREAWIDTH / 4));
	painter.drawLine(QPoint(_rectSquare.left(), _rectSquare.top() + AREAWIDTH / 2),
		QPoint(_rectSquare.right(), _rectSquare.top() + AREAWIDTH / 2));
	painter.drawLine(QPoint(_rectSquare.left(), _rectSquare.top() + AREAWIDTH  * 3/ 4),
		QPoint(_rectSquare.right(), _rectSquare.top() + AREAWIDTH * 3 / 4));
	
	painter.drawLine(QPoint(_rectSquare.left() + AREAWIDTH / 4, _rectSquare.top()),
		QPoint(_rectSquare.left() + AREAWIDTH / 4, _rectSquare.bottom()));
	painter.drawLine(QPoint(_rectSquare.left() + AREAWIDTH / 2, _rectSquare.top()),
		QPoint(_rectSquare.left() + AREAWIDTH / 2, _rectSquare.bottom()));
	painter.drawLine(QPoint(_rectSquare.left() + AREAWIDTH * 3 / 4, _rectSquare.top()),
		QPoint(_rectSquare.left() + AREAWIDTH * 3 / 4, _rectSquare.bottom()));

	QColor color;
	switch (_channel)
	{
	case CURVE_CHANNEL_GRAY:
		color = QColor(0, 0, 0);
		break;
	case CURVE_CHANNEL_RED:
		color = QColor(255, 0, 0);
		break;
	case CURVE_CHANNEL_GREEN:
		color = QColor(0, 255, 0);
		break;
	case CURVE_CHANNEL_BLUE:
		color = QColor(0, 0, 255);
		break;
	default:
		color = QColor(0, 0, 0);
		break;
	}

	// Paint pegs
	paintPegs(color);

	// Paint connection
	paintConnection(color);
}

void CurveSquare::paintPegs(QColor color)
{
	// Traverse pegs array
	for (int i = 0; i < _activePegs->size(); i++)
	{
		paintSinglePeg(_activePegs->at(i));
	}

	// Paint active peg as a solid square
	if (_activePegIndex != NONE_PEG && _activePegIndex < _activePegs->size())
	{
		QPoint point = _activePegs->at(_activePegIndex).getPoint(_rectSquare.topLeft());

		int size = 2;
		QRect rect(point.x() - size, point.y() - size, size * 2, size * 2);
		QPainter painter(this);
		painter.setBrush(QBrush(color));
		painter.drawRect(rect);
	}
}

// Paint single peg
void CurveSquare::paintSinglePeg(const Peg& peg)
{
	QPoint point = peg.getPoint(_rectSquare.topLeft());

	QPainter painter(this);
	int size = 2;
	painter.drawLine(point.x() - size, point.y() - size, point.x() + size, point.y() - size);
	painter.drawLine(point.x() + size, point.y() - size, point.x() + size, point.y() + size);
	painter.drawLine(point.x() - size, point.y() - size, point.x() + size, point.y() + size);
}

// Paint connection
void CurveSquare::paintConnection(QColor color)
{
	if (_activeArray == nullptr)
		return;

	// Connect all pegs
	QVector<QLine> lines;
	for (int i = 0; i < AREAWIDTH - 1; i++)
	{
		lines.append(QLine(getCoordinate(i, _activeArray[i]), getCoordinate(i + 1, _activeArray[i])));
	}

	QPainter painter(this);
	painter.setPen(QPen(color));
	painter.drawLines(lines);
}

// 由x、y值计算出在控件客户区上的坐标
QPoint CurveSquare::getCoordinate(int x, int y)
{
	return QPoint(x + _rectSquare.left(), AREAWIDTH - y + _rectSquare.top());
}

int CurveSquare::ptInAnyPeg(QPoint point) const
{
	for (int i = 0; i < _activePegs->size(); i++)
	{
		if (_activePegs->at(i).getRect().contains(point))
		{
			return i;
		}
	}
	return NONE_PEG;
}

// Generate histogram
bool CurveSquare::generateHistogram(uint* pArray)
{
	memcpy(_heightArray, pArray, sizeof(uint) * 256);

	_minHeight = _maxHeight = _heightArray[0];
	// find max and min value in _heightArray
	for (int i = 1; i < 256; i++)
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
	// In case all pixels value are zero
	if (_minHeight == 0 && _maxHeight == 0)
		return false;

	// Calculate height
	for (int i = 0; i < AREAWIDTH; i++)
	{
		_heightArray[i] = (_heightArray[i] - _minHeight) * (AREAWIDTH - 1) / (_maxHeight - _minHeight) + 1;
	}

	repaint();

	return true;
}