#pragma once

#include <QLabel>

#include "BaseWidget.h"

class CurveSquare;
class CurveProcessor;

class CurveWidget : public BaseWidget
{
	Q_OBJECT

public:
	CurveWidget(QWidget* parent = nullptr);
	virtual ~CurveWidget();

public:
	virtual void init();

	virtual void reset();

public slots:
	void channelChanged(int value);

//	void contrastValueChanged(int value);

protected slots:
	void renewSquare();

private:
//	void SetBrightnessAndContrast();

private:
	QLabel* _labelInput;
	QLabel* _labelOutput;

	CurveSquare* _square;

	// Image processor
	CurveProcessor* _processor;
};