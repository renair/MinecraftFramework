#ifndef _TYPES
#define _TYPES

#include<string>

namespace MinecraftTypes
{
	typedef unsigned char Byte;
	typedef char SByte;
	typedef short Short;

	class String
	{
	private:
		char* _allocator;
		static const char _len = 64;
		void init(const char* const);
	public:
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