#include "LevelsWidget.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include "LevelsProcessor.h"
#include "HistogramWidget.h"
#include "GlobalFunc.h"

LevelsWidget::LevelsWidget(QWidget* parent)
	: BaseWidget(parent)
{
	setName("Levels");

	_histogram = new HistogramWidget();
	connect(_histogram, &HistogramWidget::updateBottom, this, &LevelsWidget::updateBottom);
	connect(_histogram, &HistogramWidget::updateMid, this, &LevelsWidget::updateMid);
	connect(_histogram, &HistogramWidget::updateTop, this, &LevelsWidget::updateTop);

	_editMin = new QLineEdit();
	_editMin->setText("0");
	_editMid = new QLineEdit();
	_editMid->setText("1.0");
	_editMax = new QLineEdit();
	_editMax->setText("255");

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(_editMin);
	hbox->addStretch();
	hbox->addWidget(_editMid);
	hbox->addStretch();
	hbox->addWidget(_editMax);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(_histogram);
	layout->addLayout(hbox);

	setLayout(layout);

	_processor = new LevelsProcessor;
}

LevelsWidget::~LevelsWidget()
{
	if (_processor)
	{
		delete _processor;
	}
}

void LevelsWidget::init()
{
	BaseImage* image = getGlobalImage();
	assert(image);

	float minValue = image->getMinValue();
	float maxValue = image->getMaxValue();
	float mid = 1.0f;

	_editMin->setText(QString::number(minValue));
	_editMid->setText(QString::number(mid));
	_editMax->setText(QString::number(maxValue));

	_histogram->init();
}

void LevelsWidget::reset()
{
	_editMin->setText("0");
	_editMid->setText("1.0");
	_editMax->setText("255");

	_histogram->reset();
}

void LevelsWidget::updateBottom(float bottom)
{
	_editMin->setText(QString::number(bottom));

	levelsAdjust();
}

void LevelsWidget::updateMid(float mid)
{
	_editMid->setText(QString::number(mid));

	levelsAdjust();
}

void LevelsWidget::updateTop(float top)
{
	_editMax->setText(QString::number(top));

	levelsAdjust();
}

// Levels adjust
void LevelsWidget::levelsAdjust()
{
	BaseImage* image = getGlobalImage();
	if (image)
	{
		float bottom = _editMin->text().toFloat();
		float mid = _editMid->text().toFloat();
		float top = _editMax->text().toFloat();
		_processor->setPara(bottom, mid, top);
		_processor->process(image);

		repaintView();
	}
}