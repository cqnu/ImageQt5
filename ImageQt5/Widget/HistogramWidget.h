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

	// ���ڴ���
	void setBottomAndTop(bool* pArray, int arrayNum);

	// ɫ�׵���
	void levelAdjust(float bottom, float top, float mid);

	// Allocate memory
	void allocateMemory(int oldWidth = 0);

	void copySelectArray(bool* array, int arrayNum);

	void generateHistogram();

	// ͳ�Ʊ�ѡ�еķ�Χ
	void calcSelectArea();

	// ͳ����ʱ��ѡ�еķ�Χ
	void calcSelectTempArea();

	// �����α����ھ���
	QRect getCursorRect(int index);

	// Change index to height
	int indexToHeight(int i);

private:
	// ���д�ŵ����������ÿ���߶�Ӧ��Եĸ߶�
	uint* _heightArray;

	// m_pHeightArray����Сֵ�����ֵ
	uint _minHeight, _maxHeight;

	// Selected start point and finish point
	int _start, _finish;

	// ��ѡ�еķ�Χ����
	bool* _select;

	// ��ʱ��ѡ�еķ�Χ����
	bool* _selectTemp;

	// Width and height of histogram
	QRect _rectHistogram;

	// Cursor postion
	int _cursorPos[3];

	// Drag flag
	int _drag;

	// ɫ�׵�����Ӧ�Ŀؼ�
	float _bottom;
	float _top;
	float _mid;

	// Min and max value of image
	float _minValue, _maxValue;

	// Image processor
	HistogramProcessor* _processor;
};