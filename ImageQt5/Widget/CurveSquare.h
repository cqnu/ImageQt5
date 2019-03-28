#pragma once

#include <QWidget>
#include "Peg.h"

typedef QVector<Peg> PegArray;

#define NONE_PEG				-1
#define AREAWIDTH				256		// �������ߵ����������С

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

	// ��x��yֵ������ڿؼ��ͻ����ϵ�����
	QPoint getCoordinate(int x, int y);

	// ����������һ��peg��(����StartPeg��EndPeg)
	int ptInAnyPeg(QPoint point) const;

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