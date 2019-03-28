#pragma once

#include <QWidget>

//typedef QVector<CVSPeg, CVSPeg&> PegArray;

#define AREAWIDTH				255		// 样条曲线调整的区域大小
#define COLOR_ARRAY_NUMBER		AREAWIDTH + 1

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

private:
	// 方形区域
	QRect m_rectSquare;

	// 其中存放的是量化后的每条线对应相对的高度
	uint* _heightArray;

	// m_pHeightArray中最小值和最大值
	uint _minHeight, _maxHeight;

	// 曲线或折线
	int m_nCurveOrLine;

	// Channel
	int _channel;

	// 表示当前被选中的peg的index
	int	m_nActivePegIndex;

	// 表明当前活动的pegs链表
//	PegArray* m_pActivePegs;

	// 属于自己的pegs链表
//	PegArray m_OwnerPegs;

	// 指向当前活动的数组
	uchar* m_pActiveArray;

	// 用来存放曲线所对应的值
	uchar m_arrayIntensity[COLOR_ARRAY_NUMBER];
	uchar m_arrayRed[COLOR_ARRAY_NUMBER];
	uchar m_arrayGreen[COLOR_ARRAY_NUMBER];
	uchar m_arrayBlue[COLOR_ARRAY_NUMBER];
};