#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QVector>

class BaseWidget;

class WidgetManager
{
private:
	WidgetManager() {}
	~WidgetManager() {}

public:
	static WidgetManager* getInstance();
	static void cleanUp();

	void addWidget(BaseWidget* widget);

	void reset();

private:
	static WidgetManager* _instance;

	QVector<BaseWidget*> _vecWidget;
};

#endif	// WIDGETMANAGER_H
