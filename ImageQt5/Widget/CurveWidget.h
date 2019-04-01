#pragma once

#include <QLabel>
#include <QRadioButton>

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

	void clickReset();

	void clickReverse();

	void toggleCurveRadio();
	void toggleLinearRadio();

	void clickSave();

	void clickLoad();

protected slots:
	void resizeSquare();

	void updateImage();

	void updateLabelText(QString input, QString output);

private:
	void generateHistogram();

	void connectSqureWithProcessor();

private:
	QLabel* _labelInput;
	QLabel* _labelOutput;

	QRadioButton* _radioCurve;
	QRadioButton* _radioLinear;

	CurveSquare* _square;

	// Image processor
	CurveProcessor* _processor;
};