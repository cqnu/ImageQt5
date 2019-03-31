#pragma once

#include <QWidget>
#include "Peg.h"

typedef QVector<Peg> PegArray;

#define NONE_PEG				-1
#define PEG_DISTANCE			3

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

	void reset();

	// Generate histogram
	bool generateHistogram(uint* pArray);

	int getSize() { return _size; }

	int getChannel() { return _channel; }

	void setChannel(int channel);

	uint* getIntensity() { return _arrayIntensity; }
	uint* getRed() { return _arrayRed; }
	uint* getGreen() { return _arrayGreen; }
	uint* getBlue() { return _arrayBlue; }

signals:
	void resize();

	void updateImage();

protected:
	virtual void resizeEvent(QResizeEvent* event);

	virtual void paintEvent(QPaintEvent* event);

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	void paintHistogram();

	// Paint grid
	void paintBackground();

	// Paint pegs
	void paintPegs(QColor color);

	// Paint single peg
	void paintSinglePeg(const Peg& peg, QColor color);

	// Paint connection
	void paintConnection(QColor color);

	void initPegsArray();

	// 由x、y值计算出在控件客户区上的坐标
	QPoint getCoordinate(int x, int y);

	// 点落在任意一个peg内(包括StartPeg和EndPeg)
	int ptInAnyPeg(QPoint point) const;

	// 增加peg前的预处理，判断是否允许在当前点插入peg; 参数为新插入点的x坐标
	bool prepareAddPeg(int xCoordinate);

	// Add peg
	int	addPeg(const QPoint& point);

	// Repaint
	void repaintPeg();

	// 插入一个新控制点时，根据控制点的横坐标进行排序
	int sortPegs(const Peg& peg);

	// 对数组的操作, 改变数组的值
	void setArrayValue(int index = -2, bool flag = true);

	// 线性的改变数组的值，其中，参数flag为true表示增加或移动peg, false表示删除peg
	void setLinearityArrayValue(int index, bool flag = true);

	// 改变一个线段的值，参数startIndex表示线段起始peg的index
	// 该函数只被setLinearityArrayValue()调用
	void setLineValue(int startIndex);

	// 返回peg所在的输入输出值
	QSize getCurrentValue(int index);

	// Remove one peg
	void removePeg(int index);

	// Remove all pegs
	void removeAllPegs();

private:
	int _size;

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

	PegArray _pegsIntensity;	// 用来记录RGB所有peg
	PegArray _pegsRed;			// 用来记录R所有peg
	PegArray _pegsGreen;		// 用来记录G所有peg
	PegArray _pegsBlue;			// 用来记录B所有peg

	// 指向当前活动的数组
	uint* _activeArray;

	// 用来存放曲线所对应的值
	uint* _arrayIntensity;
	uint* _arrayRed;
	uint* _arrayGreen;
	uint* _arrayBlue;
};