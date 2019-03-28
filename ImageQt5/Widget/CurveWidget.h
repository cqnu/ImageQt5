#pragma once

#include <QLabel>

#include "BaseWidget.h"

class CurveProcessor;

class CurveWidget : public BaseWidget
{
	Q_OBJECT

public:
	CurveWidget(QWidget* parent = nullptr);
	virtual ~CurveWidget();

public:
	virtual void reset();

public slots:
//	void brightValueChanged(int value);

//	void contrastValueChanged(int value);

private:
//	void SetBrightnessAndContrast();

private:
	QLabel* _labelInput;
	QLabel* _labelOutput;

	// Image processor
	CurveProcessor* _processor;
};