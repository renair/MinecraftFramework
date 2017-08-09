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
		TcpClientSocket& _socket;
		ServiceTypes::Buffer _buffer;

		BufferedReaderWriter(const BufferedReaderWriter&);
		MinecraftTypes::VarInt readVarInt();
		void writeVarInt(MinecraftTypes::VarInt);
	public:
		BufferedReaderWriter(TcpClientSocket&);
		~BufferedReaderWriter();
		ServiceTypes::Buffer& readData();
		void sendData(ServiceTypes::Buffer&);
		const ServiceTypes::Buffer& buffer();
	};
}

#endif