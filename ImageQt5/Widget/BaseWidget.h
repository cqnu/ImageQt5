#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
	Q_OBJECT

public:
	BaseWidget(QWidget* parent = nullptr);

public:
	virtual void reset() {}
};

#endif	// COMMONNWIDGET_H
