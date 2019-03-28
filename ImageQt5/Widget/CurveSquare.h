#pragma once

#include <QWidget>

//typedef QVector<CVSPeg, CVSPeg&> PegArray;

#define AREAWIDTH				255		// �������ߵ����������С
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
	// ��������
	QRect m_rectSquare;

	// ���д�ŵ����������ÿ���߶�Ӧ��Եĸ߶�
	uint* _heightArray;

	// m_pHeightArray����Сֵ�����ֵ
	uint _minHeight, _maxHeight;

	// ���߻�����
	int m_nCurveOrLine;

	// Channel
	int _channel;

	// ��ʾ��ǰ��ѡ�е�peg��index
	int	m_nActivePegIndex;

	// ������ǰ���pegs����
//	PegArray* m_pActivePegs;

	// �����Լ���pegs����
//	PegArray m_OwnerPegs;

	// ָ��ǰ�������
	uchar* m_pActiveArray;

	// ���������������Ӧ��ֵ
	uchar m_arrayIntensity[COLOR_ARRAY_NUMBER];
	uchar m_arrayRed[COLOR_ARRAY_NUMBER];
	uchar m_arrayGreen[COLOR_ARRAY_NUMBER];
	uchar m_arrayBlue[COLOR_ARRAY_NUMBER];
};