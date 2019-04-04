#pragma once

#include <QLabel>
#include <QRadioButton>

#include "BaseWidget.h"
#include "CurveSquare.h"

class CurvesProcessor;
class QTextStream;
class QComboBox;

class CurvesWidget : public BaseWidget
{
	Q_OBJECT

public:
	CurvesWidget(QWidget* parent = nullptr);
	virtual ~CurvesWidget();

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

	void savePegArray(QTextStream& stream, const PegArray& pegs);

	void loadPegArray(QTextStream& stream, PegArray& pegs);

private:
	QLabel* _labelInput;
	QLabel* _labelOutput;

	QComboBox* _comboboxChannel;
	QRadioButton* _radioCurve;
	QRadioButton* _radioLinear;

	CurveSquare* _square;

	// Image processor
	CurvesProcessor* _processor;
};