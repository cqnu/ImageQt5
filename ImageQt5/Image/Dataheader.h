#ifndef DATAHEADER_H
#define DATAHEADER_H

#ifndef DATA_HEADER_SIZE
#define DATA_HEADER_SIZE	1024
#endif

#include <memory>

class DataHeader
{
public:
	DataHeader()
	{
		memset(this, 0, sizeof(DataHeader));
	}

public:
	int Attribute;
    unsigned short Width;
    unsigned short Height;
    unsigned short Slice;
};

#endif // DATAHEADER_H
