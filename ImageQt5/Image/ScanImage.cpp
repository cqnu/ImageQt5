#include "scanimage.h"
#include <QFile>

ScanImage::ScanImage()
{

}

ScanImage::ScanImage(const QString& pathName) :
	TemplateImage(pathName)
{
	// 读取数据头
	if (readDataHeader() == false)
	{
		_openSucceed = false;
		return;
	}
	// 读取数据
	if (readData() == false)
	{
		_openSucceed = false;
		return;
	}
	// 分配内存空间
	if (allocateMemory() == false)
	{
		_openSucceed = false;
		return;
	}
	// 遍历查找最大最小值
	if (findTopAndBottom(_originalData, _width * _height) == false)
	{
		_openSucceed = false;
		return;
	}
	// 量化图像
	if (convertToByte() == false)
	{
		_openSucceed = false;
		return;
	}
	// 拷贝到图像
	if (copyToImage() == false)
	{
		_openSucceed = false;
		return;
	}

	_openSucceed = true;
}

ScanImage::~ScanImage()
{

}

// 读数据头
bool ScanImage::readDataHeader()
{
	QFile file(_pathName);
	if (!file.open(QFile::ReadOnly))
		return false;

	qint64 size = file.size();

	file.read((char*)(&_dh), sizeof(DataHeader));
	file.close();

	_width = _dh.Width;
	_height = _dh.Height;
	_slice = _dh.Slice == 0 ? 1 : _dh.Slice;
	if (_width * _height == 0)
		return false;

	qint64 expectSize = _width * _height * _slice * sizeof(float) + DATA_HEADER_SIZE;
	if (expectSize > size)
	{
		QMessageBox::critical(NULL, "打开文件错误", "数据尺寸不符合文件信息描述，请确认数据合法性！", QMessageBox::Ok);
		return false;
	}

	return true;
}

// 读数据
bool ScanImage::readData()
{
	_originalData = new float[_width * _height];

	QFile file(_pathName);
	if (!file.open(QFile::ReadOnly))
		return false;

	file.seek(DATA_HEADER_SIZE);
	qint64 readSize = file.read((char*)_originalData, sizeof(float) * _width * _height);
	file.close();

	if (readSize != sizeof(float) * _width * _height)
	{
		QMessageBox::critical(NULL, "打开文件错误", "数据尺寸不符合文件信息描述，请确认数据合法性！", QMessageBox::Ok);
		return false;
	}

	return true;
}
