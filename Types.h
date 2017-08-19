#ifndef _TYPES
#define _TYPES
//http://wiki.vg/index.php?title=Protocol&oldid=6003#Data_types

#include<string>
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

		varint(long);
		unsigned short decode(char*);
		unsigned short encode(char*) const;
		varint& read(const ServiceTypes::Buffer&);
		varint & write(ServiceTypes::Buffer & buff);
		const varint & write(ServiceTypes::Buffer & buff) const;
		const varint operator=(long);
		operator long();
	};

	struct varlong
	{
		long long _val;
		mutable unsigned char _bytes;

		varlong(long long);
		unsigned short decode(char*);
		unsigned short encode(char*) const;
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
		unsigned int _bytes;
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
		unsigned int bytes() const;
		void setString(const char* const);
		void setString(const std::string&);
	};

	class ByteArray
	{
	private:
		char* _allocator;
		static const unsigned short _len = 1024;
	public:
		ByteArray();
		ByteArray(const char* const, unsigned short len);
		ByteArray(const ByteArray&);
		ByteArray& operator=(const ByteArray&);
		~ByteArray();

		inline unsigned short length() const;
		inline char* data();
		inline const char* data() const;
		void clear();
		void setData(const char* const, unsigned short len, unsigned short offset = 0);
	};
}
#endif