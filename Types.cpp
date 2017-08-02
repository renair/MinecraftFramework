#include"Types.h"

using namespace MinecraftTypes;


//String class

String::String(const char* const buff):
	_allocator(new char[_len+1])
{
	init(buff);
}

String::String(const std::string& str):
	_allocator(new char[_len+1])
{
	init(str.c_str());
}

String::String(const String& str):
	_allocator(new char[_len+1])
{
	init(str.cstring());
}

String& String::operator=(const String& str)
{
	if(this != &str)
	{
		memcpy(str.cstring(), _allocator, _len);
	}
	return *this;
}

String::~String()
{
	delete[] _allocator;
}

char* String::cstring() const
{
	return _allocator;
}

std::string String::string() const
{
	return std::string(_allocator);
}

void String::init(const char* const buff)
{
	Byte size = strlen(buff);
	size = size > 64 ? 64 : size;
	_allocator[_len] = '0x0'; //set 0 byte to mark end of line
	memset(_allocator, ' ', _len); //fill with spaces 0x20
	memcpy(_allocator, buff, size);
}

void String::setString(const char* const buff)
{
	init(buff);
}

void String::setString(const std::string& str)
{
	init(str.c_str());
}

inline Byte String::length() const
{
	return _len;
}


//ByteArray class

ByteArray::ByteArray():
	_allocator(new char[_len])
{
	clear();
}

ByteArray::ByteArray(const char*const buff, unsigned short len):
	_allocator(new char[_len])
{
	len = len > _len ? _len : len;
	clear();
	setData(buff, len);
}

ByteArray::ByteArray(const ByteArray& arr):
	_allocator(new char[_len])
{
	memcpy(_allocator, arr.data(), _len);
}

ByteArray& ByteArray::operator=(const ByteArray& arr)
{
	if(this != &arr)
	{
		memcpy(_allocator, arr.data(), _len);
	}
}

ByteArray::~ByteArray()
{
	delete[] _allocator;
}

inline unsigned short ByteArray::length() const
{
	return _len;
}

inline char* ByteArray::data()
{
	return _allocator;
}

inline const char* ByteArray::data() const
{
	return _allocator;
}

void ByteArray::clear()
{
	memset(_allocator, '0x0', _len);
}

void ByteArray::setData(const char* const buff, unsigned short len, unsigned short offset)
{
	clear();
	offset = len + offset > _len ? _len - len : offset;
	memcpy(_allocator+offset, buff, len);
}