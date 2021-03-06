#include "CommonWidget.h"

#include <QGridLayout>

#include "CommonProcessor.h"
#include "GlobalFunc.h"

CommonWidget::CommonWidget(QWidget* parent)
	: BaseWidget(parent)
{
	setName("Common");

	QLabel* labelBright = new QLabel("Bright");
	QLabel* labelContrast = new QLabel("Contrast");
	_sliderBright = new QSlider(Qt::Orientation::Horizontal);
	_sliderBright->setMinimum(-100);
	_sliderBright->setMaximum(100);
	connect(_sliderBright, &QSlider::valueChanged, this, &CommonWidget::brightValueChanged);
	_sliderContrast = new QSlider(Qt::Orientation::Horizontal);
	_sliderContrast->setMinimum(-100);
	_sliderContrast->setMaximum(100);
	connect(_sliderContrast, &QSlider::valueChanged, this, &CommonWidget::contrastValueChanged);
	_labelBrightNum = new QLabel("0");
	_labelContrastNum = new QLabel("0");

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(labelBright, 0, 0);
	layout->addWidget(_sliderBright, 0, 1);
	layout->addWidget(_labelBrightNum, 0, 2);
	layout->addWidget(labelContrast, 1, 0);
	layout->addWidget(_sliderContrast, 1, 1);
	layout->addWidget(_labelContrastNum, 1, 2);

	setLayout(layout);

	_processor = new CommonProcessor;
}

CommonWidget::~CommonWidget()
{
	if (_processor)
	{
		delete _processor;
	}
}

void CommonWidget::init()
{
	reset();
}

void CommonWidget::reset()
{
	_sliderBright->setValue(0);
	_sliderContrast->setValue(0);
	_labelBrightNum->setText(QString::number(0));
	_labelContrastNum->setText(QString::number(0));
}

void CommonWidget::brightValueChanged(int x)
{
	_labelBrightNum->setText(QString::number(x));

	SetBrightnessAndContrast();
}

void CommonWidget::contrastValueChanged(int x)
{
	_labelContrastNum->setText(QString::number(x));

	SetBrightnessAndContrast();
}

void CommonWidget::SetBrightnessAndContrast()
{
	BaseImage* image = getGlobalImage();
	if (image)
	{
		_processor->setBrightnessAndContrast(_sliderBright->value(), _sliderContrast->value());
		_processor->process(image);

		repaintView();
	}
}