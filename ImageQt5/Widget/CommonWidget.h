#ifndef COMMONNWIDGET_H
#define COMMONNWIDGET_H

#include <QSlider>
#include <QLabel>

#include "BaseWidget.h"

class CommonProcessor;

class CommonWidget : public BaseWidget
{
	Q_OBJECT

public:
	CommonWidget(QWidget* parent = nullptr);
	virtual ~CommonWidget();

public:
	virtual void reset();

public slots:
	void brightValueChanged(int value);

	void contrastValueChanged(int value);

private:
	void SetBrightnessAndContrast();

private:
	QSlider* _sliderBright;
	QSlider* _sliderContrast;
	QLabel* _labelBrightNum;
	QLabel* _labelContrastNum;

	// Image processor
	CommonProcessor* _processor;
};

#endif	// COMMONNWIDGET_H
