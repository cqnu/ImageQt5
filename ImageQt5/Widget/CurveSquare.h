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

	void reverse();

	// Generate histogram
	bool generateHistogram(uint* pArray);

	int getSize() { return _size; }

	int getChannel() { return _channel; }

	void setChannel(int channel);

	void setCurveOrLinear(bool curveOrLinear);

	uint* getIntensity() { return _arrayIntensity; }
	uint* getRed() { return _arrayRed; }
	uint* getGreen() { return _arrayGreen; }
	uint* getBlue() { return _arrayBlue; }

signals:
	void resize();

	void updateImage();

	void updateLabelText(QString input, QString output);

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

	// Use piecewise linear function to set array value, if flag equal true means adding or moving peg, false means deleting peg
	void setLinearityArrayValue(int index, bool flag = true);

	// 改变一个线段的值，参数startIndex表示线段起始peg的index
	// This function is only called by setLinearityArrayValue()
	void setLineValue(int startIndex);

	// Use spline function to set array value
	void setCurveArrayValue();

	// Get input&output value of current peg
	QSize getCurrentValue(int index);

	// Get input&output value of current position
	QSize getCurrentMouseValue(const QPoint& point);

	// Remove one peg
	void removePeg(int index);

	// Remove all pegs
	void removeAllPegs();

private:
	int _size;

	// Square rect
	QRect _rectSquare;

	// 其中存放的是量化后的每条线对应相对的高度
	uint* _heightArray;

	// min& max in _heightArray
	uint _minHeight, _maxHeight;

	// Curve or line
	bool _curveOrLinear;

	// Channel
	int _channel;

	// Index of active peg
	int	_activePegIndex;

	// Active peg array
	PegArray* _activePegs;

	// Record peg array of each channel
	PegArray _pegsIntensity;
	PegArray _pegsRed;
	PegArray _pegsGreen;
	PegArray _pegsBlue;

	// Point to active array
	uint* _activeArray;

	// Record array value of each channel
	uint* _arrayIntensity;
	uint* _arrayRed;
	uint* _arrayGreen;
	uint* _arrayBlue;
};