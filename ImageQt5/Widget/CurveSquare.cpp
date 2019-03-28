#include "CurveSquare.h"

#include <QPainter>
#include "../GlobalFunc.h"

CurveSquare::CurveSquare(QWidget* parent)
	: QWidget(parent)
	, _channel(0)
	, m_rectSquare(30, 45, 30 + AREAWIDTH, 45 + AREAWIDTH)
{
	_heightArray = new uint[COLOR_ARRAY_NUMBER];
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

	// ���ݻͨ�����»���ֱ��ͼ
	switch (_channel)
	{
	case CURVE_CHANNEL_GRAY:
	{
	//	setActivePegArray(m_pegsIntensity);
	//	setActiveCurveArray(pWidget->GetIntensityArray());
	//	generateHistogram(image->getGrayPixelArray());	// ����ֱ��ͼ
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
	return QSize(200, 200);
}

QSize CurveSquare::minimumSizeHint() const
{
	return QSize(100, 100);
}

void CurveSquare::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);

	QRect rect = this->rect();
	painter.drawLine(rect.bottomLeft(), rect.topRight());
	painter.drawLine(rect.bottomRight(), rect.topLeft());

	paintHistogram();
	paintBackground();
}

void CurveSquare::paintHistogram()
{
	if (getGlobalDocument() == nullptr)
		return;

	if (_maxHeight == 0)
		return;

	QPen pen(Qt::blue, 1);
	
	QPainter painter(this);
	painter.setPen(pen);

	for (int i = 0; i <= AREAWIDTH; i++)
	{
		painter.drawLine(i + m_rectSquare.left(), m_rectSquare.bottom(), i + m_rectSquare.left(), m_rectSquare.bottom() - _heightArray[i]);
	}
}

// Paint grid
void CurveSquare::paintBackground()
{
	QPainter painter(this);

	// ���ƺ��������ڰ׽���ɫ�� 
	QPoint point(m_rectSquare.left() - 17, m_rectSquare.top());
	// AREAWIDTHΪɫ���߶�
	for (int i = 0; i < AREAWIDTH; i++)
	{
		int j = 255 - i * 255 / (AREAWIDTH - 1);
		// 10Ϊɫ�����
		for (int k = 0; k < 10; k++)
		{
		//	painter.setPixelV(point, RGB(j, j, j));
		//	point.x++;
		}
	//	point.x = m_rectSquare.left - 17;
	//	point.y++;
	}

	// 6Ϊ�Լ�����
/*	point = CPoint(m_rectSquare.left, m_rectSquare.bottom + 6);
	// AREAWIDTHΪɫ������
	for (int i = 0; i < AREAWIDTH; i++)
	{
		int j = i * 255 / (AREAWIDTH - 1);
		// 10Ϊɫ�����
		for (int k = 0; k < 10; k++)
		{
			pDC->SetPixelV(point, RGB(j, j, j));
			point.y++;
		}
		point.y = m_rectSquare.bottom + 6;
		point.x++;
	}

	// �����κ����ڲ���3*3������
	point = m_rectSquare.TopLeft();
	pDC->MoveTo(point);
	pDC->LineTo(point.x + AREAWIDTH, point.y);
	pDC->LineTo(point.x + AREAWIDTH, point.y + AREAWIDTH);
	pDC->LineTo(point.x, point.y + AREAWIDTH);
	pDC->LineTo(point);

	CPen newPen(PS_DOT, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&newPen);
	// ������������
	pDC->MoveTo(point.x, point.y + AREAWIDTH / 4);
	pDC->LineTo(point.x + AREAWIDTH, point.y + AREAWIDTH / 4);
	pDC->MoveTo(point.x, point.y + AREAWIDTH / 2);
	pDC->LineTo(point.x + AREAWIDTH, point.y + AREAWIDTH / 2);
	pDC->MoveTo(point.x, point.y + AREAWIDTH * 3 / 4);
	pDC->LineTo(point.x + AREAWIDTH, point.y + AREAWIDTH * 3 / 4);

	// ������������
	pDC->MoveTo(point.x + AREAWIDTH / 4, point.y);
	pDC->LineTo(point.x + AREAWIDTH / 4, point.y + AREAWIDTH);
	pDC->MoveTo(point.x + AREAWIDTH / 2, point.y);
	pDC->LineTo(point.x + AREAWIDTH / 2, point.y + AREAWIDTH);
	pDC->MoveTo(point.x + AREAWIDTH * 3 / 4, point.y);
	pDC->LineTo(point.x + AREAWIDTH * 3 / 4, point.y + AREAWIDTH);
	pDC->SelectObject(pOldPen);

	COLORREF color;
	switch (m_nCurveChannel)
	{
	case CHANNEL_GRAY:
		color = RGB(0, 0, 0);
		break;
	case CHANNEL_RED:
		color = RGB(255, 0, 0);
		break;
	case CHANNEL_GREEN:
		color = RGB(0, 255, 0);
		break;
	case CHANNEL_BLUE:
		color = RGB(0, 0, 255);
		break;
	default:
		color = RGB(0, 0, 0);
		break;
	}
*/
	// ���ƿ��Ƶ�
//	DrawPegs(pDC, color);

	// ���Ƶ�֮������
//	ConnectCurvePegs(pDC, color);
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
	// ��ֹͼ�����������ݾ�Ϊ0���������
	if (_minHeight == 0 && _maxHeight == 0)
		return false;

	// ��Ը߶�����Ϊ���Ը߶�
	for (int i = 0; i < 256; i++)
	{
		_heightArray[i] = (_heightArray[i] - _minHeight) * (AREAWIDTH - 1) / (_maxHeight - _minHeight) + 1;
	}

	repaint();

	return true;
}