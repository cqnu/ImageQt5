#include "CommonWidget.h"

#include <QGridLayout>

#include "CommonProcessor.h"
#include "GlobalFunc.h"

CommonWidget::CommonWidget(QWidget* parent)
	: BaseWidget(parent)
{
	_processor = new CommonProcessor;

	QLabel* labelBright = new QLabel("Bright");
	QLabel* labelContrast = new QLabel("Contrast");
	_sliderBright = new QSlider(Qt::Orientation::Horizontal);
	_sliderBright->setMinimum(-100);
	_sliderBright->setMaximum(100);
	connect(_sliderBright, SIGNAL(valueChanged(int)), SLOT(brightValueChanged(int)));
	_sliderContrast = new QSlider(Qt::Orientation::Horizontal);
	_sliderContrast->setMinimum(-100);
	_sliderContrast->setMaximum(100);
	connect(_sliderContrast, SIGNAL(valueChanged(int)), SLOT(contrastValueChanged(int)));
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
}

CommonWidget::~CommonWidget()
{
	if (_processor)
	{
		delete _processor;
	}
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
		_processor->SetBrightnessAndContrast(_sliderBright->value(), _sliderContrast->value());
		_processor->Process(image);

		repaintView();
	}
}

void CommonWidget::reset()
{
	_sliderBright->setValue(0);
	_sliderContrast->setValue(0);
	_labelBrightNum->setText(QString::number(0));
	_labelContrastNum->setText(QString::number(0));
}