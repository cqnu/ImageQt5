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

	// ��x��yֵ������ڿؼ��ͻ����ϵ�����
	QPoint getCoordinate(int x, int y);

	// ����������һ��peg��(����StartPeg��EndPeg)
	int ptInAnyPeg(QPoint point) const;

	// ����pegǰ��Ԥ�����ж��Ƿ������ڵ�ǰ�����peg; ����Ϊ�²�����x����
	bool prepareAddPeg(int xCoordinate);

	// Add peg
	int	addPeg(const QPoint& point);

	// Repaint
	void repaintPeg();

	// ����һ���¿��Ƶ�ʱ�����ݿ��Ƶ�ĺ������������
	int sortPegs(const Peg& peg);

	// ������Ĳ���, �ı������ֵ
	void setArrayValue(int index = -2, bool flag = true);

	// ���Եĸı������ֵ�����У�����flagΪtrue��ʾ���ӻ��ƶ�peg, false��ʾɾ��peg
	void setLinearityArrayValue(int index, bool flag = true);

	// �ı�һ���߶ε�ֵ������startIndex��ʾ�߶���ʼpeg��index
	// �ú���ֻ��setLinearityArrayValue()����
	void setLineValue(int startIndex);

	// ����peg���ڵ��������ֵ
	QSize getCurrentValue(int index);

	// Remove one peg
	void removePeg(int index);

	// Remove all pegs
	void removeAllPegs();

private:
	int _size;

	// ��������
	QRect _rectSquare;

	// ���д�ŵ����������ÿ���߶�Ӧ��Եĸ߶�
	uint* _heightArray;

	// m_pHeightArray����Сֵ�����ֵ
	uint _minHeight, _maxHeight;

	// ���߻�����
	int _curveOrLine;

	// Channel
	int _channel;

	// Index of active peg
	int	_activePegIndex;

	// ������ǰ���pegs����
	PegArray* _activePegs;

	PegArray _pegsIntensity;	// ������¼RGB����peg
	PegArray _pegsRed;			// ������¼R����peg
	PegArray _pegsGreen;		// ������¼G����peg
	PegArray _pegsBlue;			// ������¼B����peg

	// ָ��ǰ�������
	uint* _activeArray;

	// ���������������Ӧ��ֵ
	uint* _arrayIntensity;
	uint* _arrayRed;
	uint* _arrayGreen;
	uint* _arrayBlue;
};