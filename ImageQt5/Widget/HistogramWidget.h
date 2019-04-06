#pragma once

#include <QWidget>

#define HS_MARGIN				10
#define CURSOR_SIZE				9

class HistogramWidget : public QWidget
{
	Q_OBJECT

public:
	HistogramWidget(QWidget* parent = nullptr);
	virtual ~HistogramWidget();

public:
	virtual QSize sizeHint() const;

	virtual QSize minimumSizeHint() const;

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

private:
	int _width, _height;

	// 其中存放的是量化后的每条线对应相对的高度
	uint* m_pHeightArray;

	// m_pHeightArray中最小值和最大值
	uint m_nMinHeight, m_nMaxHeight;

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
};