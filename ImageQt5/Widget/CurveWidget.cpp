#include "CurveWidget.h"

#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>

#include "CurveSquare.h"
#include "CurveProcessor.h"

CurveWidget::CurveWidget(QWidget* parent)
	: BaseWidget(parent)
{
	setName("Curve");

	_processor = new CurveProcessor;

	QLabel* labelChannel = new QLabel(tr("Channel"));
	QComboBox* comboboxChannel = new QComboBox();
	comboboxChannel->addItem(tr("All"));
	comboboxChannel->addItem(tr("Red"));
	comboboxChannel->addItem(tr("Green"));
	comboboxChannel->addItem(tr("Red"));
	connect(comboboxChannel, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CurveWidget::channelChanged);
	QPushButton* buttonReset = new QPushButton(tr("&Reset"));
	QPushButton* buttonReverse = new QPushButton(tr("R&everse"));

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

	QRadioButton* radio1 = new QRadioButton(tr("&Curve"));
	QRadioButton* radio2 = new QRadioButton(tr("&Line"));
	radio1->setChecked(true);
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(radio1);
	vbox->addWidget(radio2);
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
	connect(_square, &CurveSquare::renew, this, &CurveWidget::renewSquare);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(layoutHead);
	layout->addWidget(_square);
	layout->addLayout(layoutBottom);

	setLayout(layout);
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
	_square->init();

	BaseImage* image = getGlobalImage();
	if (image == nullptr)
		return;

	// Generate histogram according to current channel
	switch (_square->getChannel())
	{
	case CURVE_CHANNEL_GRAY:
	{
		//	setActivePegArray(m_pegsIntensity);
		//	setActiveCurveArray(pWidget->GetIntensityArray());
		_square->generateHistogram(image->getGrayPixelArray());
	}
	break;
	case CURVE_CHANNEL_RED:
	{
		//	setActivePegArray(m_pegsRed);
		//	setActiveCurveArray(pWidget->GetRedArray());
		_square->generateHistogram(image->getRedPixelArray());
	}
	break;
	case CURVE_CHANNEL_GREEN:
	{
		//	setActivePegArray(m_pegsGreen);
		//	setActiveCurveArray(pWidget->GetGreenArray());
		_square->generateHistogram(image->getGreenPixelArray());
	}
	break;
	case CURVE_CHANNEL_BLUE:
	{
		//	setActivePegArray(m_pegsBlue);
		//	setActiveCurveArray(pWidget->GetBlueArray());
		_square->generateHistogram(image->getBluePixelArray());
	}
	break;
	}

	repaint();
}

void CurveWidget::reset()
{

}

void CurveWidget::channelChanged(int value)
{
	_square->setChannel(value);
}

void CurveWidget::renewSquare()
{
	init();
}