#include "CurveWidget.h"

#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>

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
	vbox->addStretch(1);
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

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(layoutHead);
	layout->addStretch(1);
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

void CurveWidget::reset()
{

}