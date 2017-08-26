#ifndef _BUFFERED_READER_WRITER
#define _BUFFERED_READER_WRITER

#include "TcpClientSocket.h"
#include "Buffer.h"
#include "Types.h"

namespace NetworkEngine
{
	class BufferedReaderWriter
	{
	private:
		static const unsigned int _middleBufferSize;

		TcpClientSocket& _socket;
		ServiceTypes::Buffer _buffer;

		BufferedReaderWriter(const BufferedReaderWriter&) = delete;
		BufferedReaderWriter& operator=(const BufferedReaderWriter&) = delete;
		MinecraftTypes::VarInt readVarInt(unsigned int offset = 0);
		void writeVarInt(MinecraftTypes::VarInt, unsigned int offset = 0);
	public:
		BufferedReaderWriter(TcpClientSocket&);
		//~BufferedReaderWriter(); // nothing to do here
		ServiceTypes::Buffer& readData();
		void sendData(const ServiceTypes::Buffer&);
		const ServiceTypes::Buffer& buffer();
	};
}

#endif
