#ifndef _BUFFER
#define _BUFFER

namespace MinecraftTypes
{
	class String;
	struct varint;
}

namespace ServiceTypes
{
	class Buffer
	{
	private:
		mutable unsigned int _offset;
		unsigned int _size;
		unsigned int _maxSize;
		char* _allocator;
		void allocateMore(unsigned int bytesToAlloc);
	public:
		Buffer(unsigned int size = 1024);
		Buffer(const Buffer&);
		~Buffer();
		Buffer& operator=(const Buffer&);
		unsigned int& offset() const;
		void writeData(void * src, unsigned int len);
		unsigned int readData(void* dest, unsigned int size) const;
		void writeString(const MinecraftTypes::String&);
		MinecraftTypes::String readString() const;
		char* data();
		const char* data() const;
		unsigned int size() const;
		void printBytes(unsigned char col = 6, char separator = ' ') const;
		void clear();
	};
}

#endif
