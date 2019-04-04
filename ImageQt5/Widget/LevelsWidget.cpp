#include "LevelsWidget.h"

#include <QLineEdit>
#include <QHBoxLayout>
//#include "LevelsProcessor.h"
#include "GlobalFunc.h"

LevelsWidget::LevelsWidget(QWidget* parent)
	: BaseWidget(parent)
{
	setName("Levels");

	_editMin = new QLineEdit();
	_editMid = new QLineEdit();
	_editMax = new QLineEdit();

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(_editMin);
	hbox->addStretch();
	hbox->addWidget(_editMid);
	hbox->addStretch();
	hbox->addWidget(_editMax);

	setLayout(hbox);

//	_processor = new LevelsProcessor;
}

LevelsWidget::~LevelsWidget()
{
//	if (_processor)
	{
//		delete _processor;
	}
}

void LevelsWidget::init()
{

}

void LevelsWidget::reset()
{

}