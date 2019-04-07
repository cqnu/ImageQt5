#pragma once

#include <QWidget>

#define HS_MARGIN				10
#define HS_HEIGHT				110
#define CURSOR_SIZE				9

class HistogramProcessor;

class HistogramWidget : public QWidget
{
	Q_OBJECT

public:
	HistogramWidget(QWidget* parent = nullptr);
	virtual ~HistogramWidget();

public:
	virtual QSize sizeHint() const;

	virtual QSize minimumSizeHint() const;

	void init();

	void reset();

	void reverse();

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
	void paintCursor();

	void paintHistogram();

	// 调节窗宽
	void setBottomAndTop(bool* pArray, int arrayNum);

	// 色阶调整
	void levelAdjust(float bottom, float top, float mid);

	// 分配内存空间
	void allocateMemory();

	void generateHistogram();

	// 统计被选中的范围
	void calcSelectArea();

	// 统计临时被选中的范围
	void calcSelectTempArea();

	// 返回游标所在矩形
	QRect getCursorRect(int index);

	// Change index to height
	int indexToHeight(int i);

private:
	// 其中存放的是量化后的每条线对应相对的高度
	uint* _heightArray;

	// m_pHeightArray中最小值和最大值
	uint _minHeight, _maxHeight;

	// Selected start point and finish point
	int _start, _finish;

	// 被选中的范围数组
	bool* _select;

	// 临时被选中的范围数组
	bool* _selectTemp;

	// Width of histogram
	int _histogramWidth;

	// Cursor postion
	int _cursorPos[3];

	// Drag flag
	int _drag;

	// 色阶调整对应的控件
	float _bottom;
	float _top;
	float _mid;

	// 图像中的最大最小值
	float _minValue, _maxValue;

	// Image processor
	HistogramProcessor* _processor;
};