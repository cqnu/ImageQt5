#ifndef SCANIMAGE_H
#define SCANIMAGE_H

#include "templateimage.h"
#include "dataheader.h"

class ScanImage : public TemplateImage<float>
{
public:
	ScanImage();
	ScanImage(const QString& pathName);
	~ScanImage();

public:
	// 返回头文件
	DataHeader& getDataHeader()		{ return _dh; }

private:
	// 读数据头
	bool readDataHeader();

	// 读数据
	bool readData();

private:
	DataHeader _dh;
};

#endif // SCANIMAGE_H
