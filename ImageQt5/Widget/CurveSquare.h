#pragma once

#include <QWidget>
#include "Peg.h"

typedef QVector<Peg> PegArray;

#define NONE_PEG				-1
#define AREAWIDTH				256		// �������ߵ����������С
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

	void init();

	void reset();

	// Generate histogram
	bool generateHistogram(uint* pArray);

	int getChannel() { return _channel; }

protected:
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

	// �����Լ���pegs����
	PegArray _ownerPegs;

	// ָ��ǰ�������
	uchar* _activeArray;

	// ���������������Ӧ��ֵ
	uchar _arrayIntensity[AREAWIDTH];
	uchar _arrayRed[AREAWIDTH];
	uchar _arrayGreen[AREAWIDTH];
	uchar _arrayBlue[AREAWIDTH];
};