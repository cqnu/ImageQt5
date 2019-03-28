#pragma once

#include <QPoint>
#include <QRect>

#define PEG_RADIUS	6

class Peg
{
public:
	Peg() {}

	Peg(QPoint point) { _point = point; }

	Peg(int x, int y) { _point = QPoint(x, y); }

public:
	QPoint getPoint() const { return _point; }

	// Get point with offset
	QPoint getPoint(int xOffset, int yOffset) const
	{
		return QPoint(_point.x() + xOffset, _point.y() + yOffset);
	}

	QPoint getPoint(QPoint point) const
	{
		return QPoint(_point.x() + point.x(), _point.y() + point.y());
	}

	// Get rect
	QRect getRect() const
	{
		return QRect(_point.x() - PEG_RADIUS, _point.y() - PEG_RADIUS, _point.x() + PEG_RADIUS, _point.y() + PEG_RADIUS);
	}

	QRect getRect(int xOffset, int yOffset) const
	{
		return QRect(_point.x() + xOffset - PEG_RADIUS, _point.y() + yOffset - PEG_RADIUS,
			_point.x() + xOffset + PEG_RADIUS, _point.y() + yOffset + PEG_RADIUS);
	}

	void setPoint(QPoint point)	{ _point = point; }

	void setPoint(QPoint point, int xOffset, int yOffset)
	{
		_point.setX(point.x() - xOffset);
		_point.setY(point.y() - yOffset);
	}

private:
	QPoint _point;
};