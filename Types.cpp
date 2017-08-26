#include"Types.h"

using namespace MinecraftTypes;

//varint implementation

varint::varint(long val):
	_val(val)
{}

unsigned short varint::encode(char* destination) const
{
	unsigned char i = 0;
	long copy = _val;
	do
	{
		char byte = copy & 0b01111111;
		copy >>= 7;
		if (copy != 0)
		{
			byte |= 0b10000000;
		}
		*(destination + i) = byte;
		++i;
	}
	while (copy != 0);
	_bytes = i;
	return i;
}

unsigned short varint::decode(const char* source)
{
	unsigned char i = 0;
	char byte = 0;
	do
	{
		byte = *(source + i);
		char tmp = byte & 0b01111111;
		_val |= tmp << (7 * i);
		++i;
		//TODO exception if read value stored in more than 5 bytes
	}
	while((byte & 0b10000000) != 0);
	_bytes = i;
	return i;
}

varint& varint::read(const ServiceTypes::Buffer& buff)
{
	buff.offset() += decode(buff.data()+buff.offset());
	return *this;
}

varint& varint::write(ServiceTypes::Buffer& buff)
{
	char tmpBuff[5];
	encode(tmpBuff);
	buff.writeData(tmpBuff, _bytes);
	return *this;
}

const varint& varint::write(ServiceTypes::Buffer& buff) const
{
	char tmpBuff[5];
	encode(tmpBuff);
	buff.writeData(tmpBuff, _bytes);
	return *this;
}

const varint varint::operator=(long val)
{
	_val = val;
	return *this;
}

varint::operator long()
{
	return _val;
}


//varlong implementation

varlong::varlong(long long val) :
	_val(val)
{}

unsigned short varlong::encode(char* destination) const
{
	unsigned char i = 0;
	long long copy = _val;
	do
	{
		char byte = copy & 0b01111111;
		copy >>= 7;
		if (copy != 0)
		{
			byte |= 0b10000000;
		}
		*(destination + i) = byte;
		++i;
	} while (copy != 0);
	_bytes = i;
	return i;
}

unsigned short varlong::decode(const char* source)
{
	unsigned char i = 0;
	char byte = 0;
	do
	{
		byte = *(source + i);
		char tmp = byte & 0b01111111;
		_val |= tmp << (7 * i);
		++i;
		//TODO exception if read value stored in more than 10 bytes
	} while ((byte & 0b10000000) != 0);
	_bytes = i;
	return i;
}

varlong& varlong::read(const ServiceTypes::Buffer& buff)
{
	buff.offset() += decode(buff.data() + buff.offset());
	return *this;
}

varlong& varlong::write(ServiceTypes::Buffer& buff)
{
	char tmpBuff[10];
	encode(tmpBuff);
	buff.writeData(tmpBuff, _bytes);
	return *this;
}

const varlong& varlong::write(ServiceTypes::Buffer& buff) const
{
	char tmpBuff[10];
	encode(tmpBuff);
	buff.writeData(tmpBuff, _bytes);
	return *this;
}

const varlong varlong::operator=(long long val)
{
	_val = val;
	return *this;
}

varlong::operator long long()
{
	return _val;
}


//String class

String::String(unsigned int len):
	_len(len), _allocator(new char[_len + 1])
{
	_allocator[_len] = 0; //set 0 byte to mark end of line
	memset(_allocator, 0x0, _len); //fill with zeroes
}

String::String(const char* const buff):
	_len(strlen(buff)), _allocator(new char[_len+1])
{
	init(buff);
}

String::String(const std::string& str):
	_len(str.length()), _allocator(new char[_len+1])
{
	init(str.c_str());
}

String::String(const String& str):
	_len(str._len),
	_allocator(new char[str._len+1])
{
	init(str.cstring());
}

String& String::operator=(const String& str)
{
	if(this != &str)
	{
		delete[] _allocator;
		_allocator[str._len];
		memcpy(_allocator, str.cstring(), str._len);
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
	_allocator[_len] = 0; //set 0 byte to mark end of line
	memset(_allocator, 0x0, _len); //fill with spaces 0x20
	memcpy(_allocator, buff, strlen(buff));
}

void String::setString(const char* const buff)
{
	init(buff);
}

void String::setString(const std::string& str)
{
	init(str.c_str());
}

unsigned int String::length() const
{
	return _len;
}
