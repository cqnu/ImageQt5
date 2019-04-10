#pragma once

#include <QWidget>

#define HS_MARGIN				10
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

signals:
	void updateBottom(float bottom);

	void updateMid(float mid);

	void updateTop(float top);

protected:
	virtual void resizeEvent(QResizeEvent* event);

	virtual void paintEvent(QPaintEvent* event);

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	void paintCursor();

	void paintHistogram();

	// Set image window
	void setBottomAndTop(bool* pArray, int arrayNum);

	// Allocate memory
	void allocateMemory(int oldWidth = 0);

	void copySelectArray(bool* array, int arrayNum);

	void generateHistogram();

	// Calculate selected area
	void calcSelectArea();

	// Calculate temporary selected area
	void calcSelectTempArea();

	// Get rect of cursor
	QRect getCursorRect(int index);

	// Change index to height
	int indexToHeight(int i);

private:
	// Height array of each line
	uint* _heightArray;

	// Min and max value in _heightArray
	uint _minHeight, _maxHeight;

	// Selected start point and finish point
	int _start, _finish;

	// Selected array
	bool* _select;

	// Temporary selected array
	bool* _selectTemp;

	// Width and height of histogram
	QRect _rectHistogram;

	// Cursor position
	int _cursorPos[3];

	// Drag flag
	int _drag;

	// 色阶调整对应的控件
	float _bottom;
	float _mid;
	float _top;

	// Min and max value of image
	float _minValue, _maxValue;

	// Image processor
	HistogramProcessor* _processor;
};