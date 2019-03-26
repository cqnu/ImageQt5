#ifndef TEMPLATEIMAGE_H
#define TEMPLATEIMAGE_H

#include "baseimage.h"
#include <QMessageBox>
#include <cmath>
#include "GlobalFunc.h"

#ifdef _MSC_VER
#pragma execution_character_set("UTF-8")
#endif

template <class Type>
class TemplateImage : public BaseImage
{
public:
	TemplateImage();
	virtual ~TemplateImage();

public:
	// 返回原始数据指针
	Type* getOriginalData();

	// 返回正在处理的数据指针
	Type* getProcessingData();

	// 遍历查找数组最大最小值
	bool findTopAndBottom(Type* pData, int num);

	// 返回数据中最小值
	Type getMinimumValue() const { return _minValue; }

	// 设置数据中最小值
	void setMinimumValue(Type minValue) { _minValue = minValue; }

	// 返回数据中最大值
	Type getMaximumValue()	const { return _maxValue; }

	// 设置数据中最大值
	void setMaximumValue(Type maxValue) { _maxValue = maxValue; }



	// 返回量化处理后的数组
	uchar* getBYTEImage() { return _byteImage; }

	// 分配内存空间
	bool allocateMemory();

	// 量化图像
	bool convertToByte();

	// 拷贝到图像
	bool copyToImage();

public:
    virtual float getValue(const QPoint& position) const;

protected:
	TemplateImage(const QString& pathName);

public:
	virtual int slice() const			{ return _slice; }

protected:
	Type* _originalData;

	Type* _processingData;

	Type _minValue, _maxValue;

	uchar* _byteImage;

	int _slice;

	int _currentSlice;
};

template <class Type>
TemplateImage<Type>::TemplateImage()
{

}

template <class Type>
TemplateImage<Type>::TemplateImage(const QString& pathName) :
	BaseImage(pathName)
{

}

template <class Type>
TemplateImage<Type>::~TemplateImage()
{
	if (_originalData)
	{
		delete [] _originalData;
		_originalData = nullptr;
	}
	if (_processingData)
	{
		delete [] _processingData;
		_processingData = nullptr;
	}
	if (_byteImage)
	{
		delete [] _byteImage;
		_byteImage = nullptr;
	}
}

// Get original data pointer
template <typename Type>
Type* TemplateImage<Type>::getOriginalData()
{
	return _originalData;
}

// Get processing data pointer
template <typename Type>
Type* TemplateImage<Type>::getProcessingData()
{
	return _processingData;
}

// Traverse the max and min values in array
template <class Type>
bool TemplateImage<Type>::findTopAndBottom(Type* pData, int num)
{
	Q_ASSERT(pData);
	_minValue = _maxValue = pData[0];
	for (int i = 1; i < num; i++)
	{
		if (std::isnan(pData[i]) || std::isinf(pData[i]))
		{
			QMessageBox::critical(nullptr, "Error in traversing data", "Invalid value in data!", QMessageBox::Ok);
			return false;
		}

		if (_minValue > pData[i])
		{
			_minValue = pData[i];
		}
		if (_maxValue < pData[i])
		{
			_maxValue = pData[i];
		}
	}

	return true;
}

// Allocate memory
template <class Type>
bool TemplateImage<Type>::allocateMemory()
{
//	try
	{
		_processingData = new Type[_width * _height];
		memcpy(_processingData, _originalData, sizeof(Type) * _width * _height);

		// 3通道
		_byteImage = new uchar[_width * _height * 3];

		_pImage = new QImage(_width, _height, QImage::Format_RGB888);
	}
//	catch ()
	{

	}

	return true;
}

// Convert data to byte
template <class Type>
bool TemplateImage<Type>::convertToByte()
{
	if (_processingData == nullptr)
		return false;

	float variable;
	if (_minValue != _maxValue)
	{
		variable = 255.0f / (_maxValue - _minValue);
	}
	else
	{
		variable = 0.0f;
	}

	for (int i = 0; i < _width * _height; i++)
	{
		_byteImage[3 * i] = _byteImage[3 * i + 1] = _byteImage[3 * i + 2] =
				uchar((_processingData[i] - _minValue) * variable);
	}

	return true;
}

// 拷贝到图像
template <class Type>
bool TemplateImage<Type>::copyToImage()
{
	return copyByteToImage(_byteImage, _width, _height, _pImage);
}

template <class Type>
float TemplateImage<Type>::getValue(const QPoint& position) const
{
    int index = position.y() * _width + position.x();
    return float(_processingData[index]);
}

#endif // TEMPLATEIMAGE_H
