#pragma once

#include "BaseWidget.h"

class LevelsProcessor;
class HistogramWidget;
class QLineEdit;

class LevelsWidget : public BaseWidget
{
	Q_OBJECT

public:
	LevelsWidget(QWidget* parent = nullptr);
	virtual ~LevelsWidget();

public:
	virtual void init();

	virtual void reset();

public slots:
	void updateHistogram();

	void updateBottom(float bottom);

	void updateMid(float mid);

	void updateTop(float top);

private:
	// Levels adjust
	void levelsAdjust();

private:
	HistogramWidget* _histogram;
	QLineEdit* _editMin;
	QLineEdit* _editMid;
	QLineEdit* _editMax;

	// Image processor
	LevelsProcessor* _processor;
};