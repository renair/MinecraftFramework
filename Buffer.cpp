#include<cstring>
#include<cstdio>
#include"Buffer.h"
#include"Types.h"

using namespace ServiceTypes;

Buffer::Buffer(unsigned int len):
	_offset(0), _size(0), _maxSize(len), _allocator(new char[_maxSize])
{
	memset(_allocator, 0, _maxSize);
}

Buffer::Buffer(const Buffer& buff):
	_offset(buff.offset()), _size(buff.size()), _maxSize(buff._maxSize), _allocator(new char[_maxSize])
{
	memcpy(_allocator, buff.data(), _maxSize);
}

Buffer::~Buffer()
{
	delete[] _allocator;
}

Buffer& Buffer::operator=(const Buffer& buff)
{
	if(this != &buff)
	{
		delete[] _allocator;
		_allocator = new char[buff._maxSize];
		_maxSize = buff._maxSize;
		_size = buff._size;
		memcpy(_allocator, buff.data(), _maxSize);
	}
	return *this;
}

void Buffer::allocateMore(unsigned int bytesToAlloc)
{
	//TODO nothrow
	//save old data
	char* tmp = new char[_maxSize + bytesToAlloc];
	memset(tmp+_maxSize, 0, bytesToAlloc);
	memcpy(tmp, data(), _maxSize);
	//replace old buffer with new one
	delete[] _allocator;
	_allocator = tmp;
	_maxSize += bytesToAlloc;
}

unsigned int& Buffer::offset() const
{
	return _offset;
}

void Buffer::writeData(void* src, unsigned int len)
{
	if(offset()+len > _maxSize)
	{
		allocateMore(len*2);
	}
	memcpy(_allocator+offset(), src, len);
	offset() += len;
	if(offset() > size())
	{
		_size = offset();
	}
}

unsigned int Buffer::readData(void* dest, unsigned int len) const
{
	if(len > _maxSize)
	{
		len = _maxSize;
		offset() = 0;
	}
	else if(offset() + len > size())
	{
		offset() = size() - len;
	}
	memcpy(dest, data()+offset(), len);
	offset() += len;
	return len;
}

void Buffer::writeString(const MinecraftTypes::String& str)
{
	MinecraftTypes::VarInt len(str.length());
	len.write(*this);
	writeData(str.cstring(), str.length());
}

MinecraftTypes::String Buffer::readString() const
{
	MinecraftTypes::VarInt len(0);
	len.read(*this);
	MinecraftTypes::String str(len._val);
	memcpy(str.cstring(), data()+offset(), len._val);
	offset() += len._val;
	return str;
}

char* Buffer::data()
{
	return _allocator;
}

const char* Buffer::data() const
{
	return _allocator;
}

unsigned int Buffer::size() const
{
	return _size;
}

void Buffer::printBytes(std::ostream& os, unsigned char col, char separator) const
{
	unsigned char* allocator = (unsigned char*)data();
	const short buffSize = 20;
	char tmpBuff[buffSize];
	for(unsigned int line = 0; line <= size()/col; ++line)
	{
		for(unsigned int column = 0; column < col && (line*col + column) < size(); ++column)
		{
			sprintf_s<buffSize>(tmpBuff, "0x%02X%c",*(allocator+(line*col+column)),separator);
			os << tmpBuff;
		}
		os << std::endl;
	}
	os.flush();
}

void Buffer::clear()
{
	_size = 0;
	offset() = 0;
}
