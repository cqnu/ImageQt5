#pragma once

#include <QWidget>

class BaseWidget : public QWidget
{
	Q_OBJECT

public:
	BaseWidget(QWidget* parent = nullptr);

public:
	virtual void reset() {}
};