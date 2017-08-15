#ifndef _TYPES
#define _TYPES
//http://wiki.vg/index.php?title=Protocol&oldid=6003#Data_types

#include<string>
#include"Buffer.h"

namespace MinecraftTypes
{
	struct varint;
	struct varlong;

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

	struct varint
	{
		long _val;
		unsigned char _bytes;

		varint(long);
		unsigned short decode(char*);
		unsigned short encode(char*);
		varint& read(const ServiceTypes::Buffer&);
		varint& write(ServiceTypes::Buffer&);
		const varint operator=(long);
		operator long();
	};

	struct varlong
	{
		long long _val;
		unsigned char _bytes;

		varlong(long long);
		unsigned short decode(char*);
		unsigned short encode(char*);
		varlong& read(const ServiceTypes::Buffer&);
		varlong& write(ServiceTypes::Buffer&);
		const varlong operator=(long long);
		operator long long();
	};

	class String
	{
	private:
		char* _allocator;
		unsigned int _len;
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
		inline Byte length() const;
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