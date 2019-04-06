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

private:

private:
	HistogramWidget* _histogram;
	QLineEdit* _editMin;
	QLineEdit* _editMid;
	QLineEdit* _editMax;

	// Image processor
	LevelsProcessor* _processor;
};