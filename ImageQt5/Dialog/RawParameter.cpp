#include "RawParameter.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QPainter>
#include "../Image/TemplateImage.h"

RawParameter::RawParameter(QWidget* parent, QString fileName)
	: QDialog(parent)
	, _fileName(fileName)
	, _offset(0)
	, _width(0)
	, _height(0)
	, _pixelDepth(1)
	, _image(nullptr)
{
	QLabel* labelSize = new QLabel(tr("File size:"));
	_editFileSize = new QLineEdit();
	_editFileSize->setReadOnly(true);
	QLabel* label1 = new QLabel(tr("byte"));
	QLabel* labelExpectSize = new QLabel(tr("Expect size:"));
	_editExpectSize = new QLineEdit();
	_editExpectSize->setReadOnly(true);
	QLabel* label2 = new QLabel(tr("byte"));
	QGridLayout* grid1 = new QGridLayout();
	grid1->addWidget(labelSize, 0, 0);
	grid1->addWidget(_editFileSize, 0, 1);
	grid1->addWidget(label1, 0, 2);
	grid1->addWidget(labelExpectSize, 1, 0);
	grid1->addWidget(_editExpectSize, 1, 1);
	grid1->addWidget(label2, 1, 2);

	QGroupBox* groupBox1 = new QGroupBox(tr("Information"));
	groupBox1->setLayout(grid1);

	QLabel* labelOffset = new QLabel(tr("Offset:"));
	_editOffset = new QLineEdit();
	connect(_editOffset, &QLineEdit::editingFinished, this, &RawParameter::updateOffset);
	QLabel* label3 = new QLabel(tr("byte"));
	QLabel* labelX = new QLabel(tr("X:"));
	_editX = new QLineEdit();
	connect(_editX, &QLineEdit::editingFinished, this, &RawParameter::updateX);
	QLabel* label4 = new QLabel(tr("pixel"));
	QLabel* labelY = new QLabel(tr("Y:"));
	_editY = new QLineEdit();
	connect(_editY, &QLineEdit::editingFinished, this, &RawParameter::updateY);
	QLabel* label5 = new QLabel(tr("pixel"));
	QLabel* labelType = new QLabel(tr("Data type:"));
	_comboboxType = new QComboBox();
	_comboboxType->addItem(tr("8-bit Unsigned char"));
	_comboboxType->addItem(tr("16-bit Signed short"));
	_comboboxType->addItem(tr("16-bit Unsigned short"));
	_comboboxType->addItem(tr("32-bit Signed int"));
	_comboboxType->addItem(tr("32-bit Unsigned int"));
	_comboboxType->addItem(tr("32-bit Float"));
	_comboboxType->addItem(tr("64-bit Double"));
	connect(_comboboxType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RawParameter::pixelDepthChanged);
	QGridLayout* grid2 = new QGridLayout();
	grid2->addWidget(labelOffset, 0, 0);
	grid2->addWidget(_editOffset, 0, 1);
	grid2->addWidget(label3, 0, 2);
	grid2->addWidget(labelX, 1, 0);
	grid2->addWidget(_editX, 1, 1);
	grid2->addWidget(label4, 1, 2);
	grid2->addWidget(labelY, 2, 0);
	grid2->addWidget(_editY, 2, 1);
	grid2->addWidget(label5, 2, 2);
	grid2->addWidget(labelType, 3, 0);
	grid2->addWidget(_comboboxType, 3, 1);
	QGroupBox* groupBox2 = new QGroupBox(tr("Size"));
	groupBox2->setLayout(grid2);

	QVBoxLayout* vbox = new QVBoxLayout();
	vbox->addWidget(groupBox1);
	vbox->addWidget(groupBox2);
	vbox->addStretch();

	_imageBox = new QGroupBox(tr("Image"));
	_imageBox->setMinimumWidth(600);
	_imageBox->setMinimumHeight(600);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addLayout(vbox);
	hbox->addWidget(_imageBox);
	hbox->setStretch(0, 0);
	hbox->setStretch(1, 1);

	QPushButton* buttonOK = new QPushButton(tr("&OK"));
	connect(buttonOK, &QPushButton::clicked, this, &RawParameter::accept);
	QPushButton* buttonReset = new QPushButton(tr("&Cancel"));
	connect(buttonReset, &QPushButton::clicked, this, &RawParameter::reject);
	QHBoxLayout* bottom = new QHBoxLayout();
	bottom->addStretch(0);
	bottom->addWidget(buttonOK);
	bottom->addWidget(buttonReset);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(hbox);
	layout->addLayout(bottom);

	setLayout(layout);

	setWindowTitle("Import Raw File");

	initialize();
}

RawParameter::~RawParameter()
{

}

void RawParameter::initialize()
{
	QFileInfo fileInfo(_fileName);
	assert(fileInfo.exists());

	qint64 size = fileInfo.size();
	_editFileSize->setText(QString::number(size));
}

void RawParameter::updateSize()
{
	qint64 size = qint64(_width) * qint64(_height) * qint64(_pixelDepth) + _offset;
	_editExpectSize->setText(QString::number(size));

	if (_width == 0 ||  _height == 0)
		return;

	createTemplateImage();

	readRawData();

	repaint();
}

void RawParameter::createTemplateImage()
{
	if (_image)
	{
		delete _image;
	}
	
	switch (_comboboxType->currentIndex())
	{
	case 0:
		_image = new TemplateImage<unsigned char>(_fileName, _width, _height);
		break;
	case 1:
		_image = new TemplateImage<short>(_fileName, _width, _height);
		break;
	case 2:
		_image = new TemplateImage<unsigned short >(_fileName, _width, _height);
		break;
	case 3:
		_image = new TemplateImage<int>(_fileName, _width, _height);
		break;
	case 4:
		_image = new TemplateImage<unsigned int>(_fileName, _width, _height);
		break;
	case 5:
		_image = new TemplateImage<float>(_fileName, _width, _height);
		break;
	case 6:
		_image = new TemplateImage<double>(_fileName, _width, _height);
		break;
	default:
		assert(false);
		break;
	}
}

void RawParameter::readRawData()
{
	QFile file(_fileName);
	if (!file.open(QFile::ReadOnly))
		return;
	file.seek(_offset);

	int pixelNum = _width * _height;
	switch (_comboboxType->currentIndex())
	{
	case 0:
	{
		TemplateImage<unsigned char>* image = dynamic_cast<TemplateImage<unsigned char>*>(_image);
		unsigned char* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(unsigned char) * _width * _height);
		assert(readSize == sizeof(unsigned char) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 1:
	{
		TemplateImage<short>* image = dynamic_cast<TemplateImage<short>*>(_image);
		short* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(short) * _width * _height);
		assert(readSize == sizeof(short) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 2:
	{
		TemplateImage<unsigned short>* image = dynamic_cast<TemplateImage<unsigned short>*>(_image);
		unsigned short* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(unsigned short) * _width * _height);
		assert(readSize == sizeof(unsigned short) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 3:
	{
		TemplateImage<int>* image = dynamic_cast<TemplateImage<int>*>(_image);
		int* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(int) * _width * _height);
		assert(readSize == sizeof(int) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 4:
	{
		TemplateImage<unsigned int>* image = dynamic_cast<TemplateImage<unsigned int>*>(_image);
		unsigned int* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(unsigned int) * _width * _height);
		assert(readSize == sizeof(unsigned int) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 5:
	{
		TemplateImage<float>* image = dynamic_cast<TemplateImage<float>*>(_image);
		float* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(float) * _width * _height);
		assert(readSize == sizeof(float) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	case 6:
	{
		TemplateImage<double>* image = dynamic_cast<TemplateImage<double>*>(_image);
		double* originalData = image->getOriginalData();
		qint64 readSize = file.read((char*)originalData, sizeof(double) * _width * _height);
		assert(readSize == sizeof(double) * pixelNum);

		image->findTopAndBottom(originalData, pixelNum);
		image->allocateMemory();
		image->convertToByte();
		image->copyToImage();
	}
	break;
	}

	file.close();
}

void RawParameter::updateOffset()
{
	_offset = _editOffset->text().toInt();
	updateSize();
}

void RawParameter::updateX()
{
	_width = _editX->text().toInt();
	updateSize();
}

void RawParameter::updateY()
{
	_height = _editY->text().toInt();
	updateSize();
}

void RawParameter::pixelDepthChanged(int value)
{
	switch (value)
	{
	case 0:
		_pixelDepth = 1;
		break;
	case 1:
	case 2:
		_pixelDepth = 2;
		break;
	case 3:
	case 4:
	case 5:
		_pixelDepth = 4;
		break;
	case 6:
		_pixelDepth = 8;
		break;
	}
	updateSize();
}

void RawParameter::paintEvent(QPaintEvent*)
{
	if (_image)
	{
		QRect rect = _imageBox->geometry();
		rect.adjust(3, 20, -3, -3);
		QPainter draw(this);
		draw.drawImage(rect, *_image->getImageEntity());
	}
}