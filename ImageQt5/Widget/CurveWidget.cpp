#include "CurveWidget.h"

#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>

#include "CurveSquare.h"
#include "CurveProcessor.h"

CurveWidget::CurveWidget(QWidget* parent)
	: BaseWidget(parent)
	, _square(nullptr)
{
	setName("Curve");

	QLabel* labelChannel = new QLabel(tr("Channel"));
	QComboBox* comboboxChannel = new QComboBox();
	comboboxChannel->addItem(tr("All"));
	comboboxChannel->addItem(tr("Red"));
	comboboxChannel->addItem(tr("Green"));
	comboboxChannel->addItem(tr("Blue"));
	connect(comboboxChannel, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CurveWidget::channelChanged);
	QPushButton* buttonReset = new QPushButton(tr("&Reset"));
	connect(buttonReset, &QPushButton::clicked, this, &CurveWidget::clickReset);
	QPushButton* buttonReverse = new QPushButton(tr("R&everse"));
	connect(buttonReverse, &QPushButton::clicked, this, &CurveWidget::clickReverse);

	QHBoxLayout* layoutHead = new QHBoxLayout();
	layoutHead->addWidget(labelChannel);
	layoutHead->addWidget(comboboxChannel);
	layoutHead->addWidget(buttonReset);
	layoutHead->addWidget(buttonReverse);

	QLabel* labelInput = new QLabel(tr("Input:"));
	_labelInput = new QLabel();
	QLabel* labelOutput = new QLabel(tr("Output:"));
	_labelOutput = new QLabel(tr(""));
	QGridLayout* grid = new QGridLayout();
	grid->addWidget(labelInput, 0, 0);
	grid->addWidget(_labelInput, 0, 1);
	grid->addWidget(labelOutput, 1, 0);
	grid->addWidget(_labelOutput, 1, 1);
	QGroupBox* groupBox1 = new QGroupBox(tr(""));
	groupBox1->setLayout(grid);

	_radioCurve = new QRadioButton(tr("&Curve"));
	_radioLinear = new QRadioButton(tr("&Line"));
	connect(_radioCurve, &QRadioButton::toggled, this, &CurveWidget::toggleCurveRadio);
	connect(_radioLinear, &QRadioButton::toggled, this, &CurveWidget::toggleLinearRadio);
	_radioCurve->setChecked(true);
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(_radioCurve);
	vbox->addWidget(_radioLinear);
	QGroupBox* groupBox2 = new QGroupBox(tr(""));
	groupBox2->setLayout(vbox);

	QPushButton* buttonSave = new QPushButton(tr("&Save"));
	QPushButton* buttonLoad = new QPushButton(tr("L&oad"));
	QVBoxLayout* vbox2 = new QVBoxLayout;
	vbox2->addWidget(buttonSave);
	vbox2->addWidget(buttonLoad);
	QHBoxLayout* layoutBottom = new QHBoxLayout();
	layoutBottom->addWidget(groupBox1);
	layoutBottom->addWidget(groupBox2);
	layoutBottom->addLayout(vbox2);

	_square = new CurveSquare();
	connect(_square, &CurveSquare::resize, this, &CurveWidget::resizeSquare);
	connect(_square, &CurveSquare::updateImage, this, &CurveWidget::updateImage);
	connect(_square, &CurveSquare::updateLabelText, this, &CurveWidget::updateLabelText);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(layoutHead);
	layout->addWidget(_square);
	layout->addLayout(layoutBottom);

	setLayout(layout);

	_processor = new CurveProcessor;
	_processor->setArray(_square->getSize(), _square->getIntensity(), _square->getRed(), _square->getGreen(), _square->getBlue());
	_processor->setChannel(_square->getChannel());
}

CurveWidget::~CurveWidget()
{
	if (_processor)
	{
		delete _processor;
	}
}

void CurveWidget::init()
{
	generateHistogram();
}

void CurveWidget::reset()
{
	_square->reset();
	connectSqureWithProcessor();
}

void CurveWidget::channelChanged(int value)
{
	_square->setChannel(value);
	_processor->setChannel(value);

	generateHistogram();
}

void CurveWidget::clickReset()
{
	reset();

	updateImage();
}

void CurveWidget::clickReverse()
{
	_square->reverse();
}

void CurveWidget::toggleCurveRadio()
{
	if (_square && _radioCurve->isChecked())
	{
		_square->setCurveOrLinear(true);
	}
}

void CurveWidget::toggleLinearRadio()
{
	if (_square && _radioLinear->isChecked())
	{
		_square->setCurveOrLinear(false);
	}
}

void CurveWidget::resizeSquare()
{
	init();
	connectSqureWithProcessor();
}

void CurveWidget::updateImage()
{
//	_isProcessing = true;

	BaseImage* image = getGlobalImage();
	if (image)
	{
		_processor->process(image);

		repaintView();
	}
//	_isProcessing = false;
}

void CurveWidget::updateLabelText(QString input, QString output)
{
	_labelInput->setText(input);
	_labelOutput->setText(output);
}

void CurveWidget::generateHistogram()
{
	BaseImage* image = getGlobalImage();
	if (image == nullptr)
		return;

	// Generate histogram according to current channel
	switch (_square->getChannel())
	{
	case CURVE_CHANNEL_GRAY:
	{
		_square->generateHistogram(image->getGrayPixelArray());
	}
	break;
	case CURVE_CHANNEL_RED:
	{
		_square->generateHistogram(image->getRedPixelArray());
	}
	break;
	case CURVE_CHANNEL_GREEN:
	{
		_square->generateHistogram(image->getGreenPixelArray());
	}
	break;
	case CURVE_CHANNEL_BLUE:
	{
		_square->generateHistogram(image->getBluePixelArray());
	}
	break;
	}
}

void CurveWidget::connectSqureWithProcessor()
{
	_processor->setArray(_square->getSize(), _square->getIntensity(), _square->getRed(), _square->getGreen(), _square->getBlue());
	_processor->setChannel(_square->getChannel());
}