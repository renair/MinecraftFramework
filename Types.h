#ifndef _TYPES
#define _TYPES
//http://wiki.vg/index.php?title=Protocol&oldid=6003#Data_types

#include<string>
#if defined(__unix__)
#include<cstring>
#endif
#include"Buffer.h"

namespace MinecraftTypes
{
	struct varint;
	struct varlong;
	union position;

	typedef bool Boolean;
	typedef unsigned char Byte;
	typedef char SByte;
	typedef short Short;
	typedef unsigned short UShort;
	typedef int Int;
	typedef long Long;
	typedef float Float;
	typedef double Double;
	typedef struct varint VarInt;
	typedef struct varlong VarLong;
	typedef union position Position;

	struct varint
	{
		long _val;
		mutable unsigned char _bytes;
		static const short _maxBytes = 5;

		varint(long);
		unsigned short decode(const char*);
		unsigned short encode(char*) const;
		bool decodeByte(char); // return true when reading done
		varint& read(const ServiceTypes::Buffer&);
		varint& write(ServiceTypes::Buffer& buff);
		const varint & write(ServiceTypes::Buffer& buff) const;
		const varint operator=(long);
		operator long();
	};

	struct varlong
	{
		long long _val;
		mutable unsigned char _bytes;
		static const short _maxBytes = 10;

		varlong(long long);
		unsigned short decode(const char*);
		unsigned short encode(char*) const;
		bool decodeByte(char); // return true when reading done
		varlong& read(const ServiceTypes::Buffer&);
		varlong& write(ServiceTypes::Buffer&);
		const varlong& write(ServiceTypes::Buffer&) const;
		const varlong operator=(long long);
		operator long long();
	};

	union position
	{
		long _rawValue;
		struct Coordinates
		{
			long _x : 26;
			long _y : 12;
			long _z : 26;
		} _coords;
	};

	class String
	{
	private:
		unsigned int _len;
		char* _allocator;
		void init(const char* const);
	public:
		String(unsigned int len);
		String(const char* const);
		String(const std::string&);
		String(const String&);
		String& operator=(const String&);
		~String();

		char* cstring() const;
		std::string string() const;
		unsigned int length() const;
		void setString(const char* const);
		void setString(const std::string&);
	};
}
#endif
