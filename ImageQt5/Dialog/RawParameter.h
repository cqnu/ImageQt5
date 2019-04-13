#pragma once

#include <QDialog>

class QLineEdit;
class QComboBox;

class RawParameter : public QDialog
{
	Q_OBJECT

public:
	RawParameter(QWidget* parent);
	~RawParameter();

private:
	QLineEdit* _editFileSize;
	QLineEdit* _editExpectSize;
	QComboBox* _comboboxType;
};

