#pragma once

#include <QWidget>
#include "Peg.h"

typedef QVector<Peg> PegArray;

#define NONE_PEG				-1
#define AREAWIDTH				256		// 样条曲线调整的区域大小

#ifndef CURVE_CHANNEL
#define CURVE_CHANNEL
#define CURVE_CHANNEL_GRAY		0
#define CURVE_CHANNEL_RED		1
#define CURVE_CHANNEL_GREEN		2
#define CURVE_CHANNEL_BLUE		3
#endif

class CurveSquare : public QWidget
{
	Q_OBJECT

public:
	CurveSquare(QWidget* parent = nullptr);
	virtual ~CurveSquare();

public:
	virtual QSize sizeHint() const;

	virtual QSize minimumSizeHint() const;

	void init();

	void reset();

	// Generate histogram
	bool generateHistogram(uint* pArray);

	int getChannel() { return _channel; }

protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	void paintHistogram();

	// Paint grid
	void paintBackground();

	// Paint pegs
	void paintPegs(QColor color);

	// Paint single peg
	void paintSinglePeg(const Peg& peg);

	// Paint connection
	void paintConnection(QColor color);

	// 由x、y值计算出在控件客户区上的坐标
	QPoint getCoordinate(int x, int y);

	// 点落在任意一个peg内(包括StartPeg和EndPeg)
	int ptInAnyPeg(QPoint point) const;

private:
	// 方形区域
	QRect _rectSquare;

	// 其中存放的是量化后的每条线对应相对的高度
	uint* _heightArray;

	// m_pHeightArray中最小值和最大值
	uint _minHeight, _maxHeight;

	// 曲线或折线
	int _curveOrLine;

	// Channel
	int _channel;

	// Index of active peg
	int	_activePegIndex;

	// 表明当前活动的pegs链表
	PegArray* _activePegs;

	// 属于自己的pegs链表
	PegArray _ownerPegs;

	// 指向当前活动的数组
	uchar* _activeArray;

	// 用来存放曲线所对应的值
	uchar _arrayIntensity[AREAWIDTH];
	uchar _arrayRed[AREAWIDTH];
	uchar _arrayGreen[AREAWIDTH];
	uchar _arrayBlue[AREAWIDTH];
};