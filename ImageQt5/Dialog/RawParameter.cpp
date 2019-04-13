#include "RawParameter.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

RawParameter::RawParameter(QWidget* parent)
	: QDialog(parent)
{
	QLabel* labelSize = new QLabel(tr("File size:"));
	_editFileSize = new QLineEdit();
	_editFileSize->setReadOnly(true);
	QLabel* labelExpectSize = new QLabel(tr("Expect size:"));
	_editExpectSize = new QLineEdit();
	QGridLayout* grid1 = new QGridLayout();
	grid1->addWidget(labelSize, 0, 0);
	grid1->addWidget(_editFileSize, 0, 1);
	grid1->addWidget(labelExpectSize, 1, 0);
	grid1->addWidget(_editExpectSize, 1, 1);

	QGroupBox* groupBox1 = new QGroupBox(tr("Information"));
	groupBox1->setLayout(grid1);

	QLabel* labelOffset = new QLabel(tr("Offset:"));
	QLineEdit* editOffset = new QLineEdit();
	QLabel* labelX = new QLabel(tr("X:"));
	QLineEdit* editX = new QLineEdit();
	QLabel* labelY = new QLabel(tr("Y:"));
	QLineEdit* editY = new QLineEdit();
	QLabel* labelType = new QLabel(tr("Data type:"));
	_comboboxType = new QComboBox();
	_comboboxType->addItem(tr("8-bit Unsigned char"));
	_comboboxType->addItem(tr("16-bit Signed short"));
	_comboboxType->addItem(tr("16-bit Unsigned short"));
	_comboboxType->addItem(tr("32-bit Signed int"));
	_comboboxType->addItem(tr("32-bit Unsigned int"));
	_comboboxType->addItem(tr("32-bit Float"));
	_comboboxType->addItem(tr("64-bit Double"));
	QGridLayout* grid2 = new QGridLayout();
	grid2->addWidget(labelOffset, 0, 0);
	grid2->addWidget(editOffset, 0, 1);
	grid2->addWidget(labelX, 1, 0);
	grid2->addWidget(editX, 1, 1);
	grid2->addWidget(labelY, 2, 0);
	grid2->addWidget(editY, 2, 1);
	grid2->addWidget(labelType, 3, 0);
	grid2->addWidget(_comboboxType, 3, 1);
	QGroupBox* groupBox2 = new QGroupBox(tr("Size"));
	groupBox2->setLayout(grid2);

	QVBoxLayout* vbox = new QVBoxLayout();
	vbox->addWidget(groupBox1);
	vbox->addWidget(groupBox2);
	vbox->addStretch();

	QGroupBox* groupBox = new QGroupBox(tr("Image"));
	groupBox->setMinimumWidth(500);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addLayout(vbox);
	hbox->addWidget(groupBox);

	QPushButton* buttonOK = new QPushButton(tr("&OK"));
	QPushButton* buttonReset = new QPushButton(tr("&Cancel"));
	QHBoxLayout* bottom = new QHBoxLayout();
	bottom->addStretch(0);
	bottom->addWidget(buttonOK);
	bottom->addWidget(buttonReset);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(hbox);
	layout->addLayout(bottom);

	setLayout(layout);

	setWindowTitle("Import Raw File");
}

RawParameter::~RawParameter()
{

}
