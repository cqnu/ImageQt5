#pragma once

#include <QDialog>

class QLineEdit;
class QComboBox;
class QGroupBox;
class BaseImage;

class RawParameter : public QDialog
{
	Q_OBJECT

public:
	RawParameter(QWidget* parent, QString fileName);
	~RawParameter();

public:
	std::shared_ptr<BaseImage> getImage() { return _image; }

public slots:
	void updateOffset();

	void updateX();

	void updateY();

	void pixelDepthChanged(int value);

	void clickedOK();

protected:
	void paintEvent(QPaintEvent*);

private:
	void initialize();

	void updateSize();

	void createTemplateImage();

	void readRawData();

private:
	QString _fileName;

	int _offset;
	int _width;
	int _height;
	int _pixelDepth;
	std::shared_ptr<BaseImage> _image;

	QLineEdit* _editFileSize;
	QLineEdit* _editExpectSize;
	QLineEdit* _editOffset;
	QLineEdit* _editX;
	QLineEdit* _editY;
	QComboBox* _comboboxType;
	QGroupBox* _imageBox;
};

