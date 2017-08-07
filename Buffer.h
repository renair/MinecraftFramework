#ifndef _BUFFER
#define _BUFFER

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
		void put(void*, unsigned int len);
		inline unsigned int& offset() const;
		unsigned int readData(char* dest, unsigned int size) const;
		inline char* data() const;
		inline unsigned int size() const;
		void printBytes(unsigned char col = 6, char separator = ' ') const;
		inline void clear();
	};
}

#endif