#include "BufferedReaderWriter.h"
#ifdef _DEBUG
#include <iostream>
#endif

using namespace NetworkEngine;

const unsigned int BufferedReaderWriter::_middleBufferSize = 1024;

BufferedReaderWriter::BufferedReaderWriter(TcpClientSocket& sock):
	_socket(sock), _buffer(1024)
{

}

MinecraftTypes::VarInt BufferedReaderWriter::readVarInt(unsigned int offset)
{
	_buffer.offset() = offset;
	MinecraftTypes::VarInt result = 0;
	_buffer.offset() += result.decode(_buffer.data());
	return result;
}

void BufferedReaderWriter::writeVarInt(MinecraftTypes::VarInt val, unsigned int offset)
{
	char bytes[5];
	_buffer.offset() = offset;
	unsigned int len = val.encode(bytes);
	_buffer.writeData(bytes, len);
}

ServiceTypes::Buffer& BufferedReaderWriter::readData()
{
	//TODO reimplement method to be ready if socket can't read whole VarInt at once
	_buffer.clear();
	char* buff = new char[_middleBufferSize];
	unsigned int readed = _socket.read(buff, _middleBufferSize);
	MinecraftTypes::VarInt dataLength(0);
	readed -= dataLength.decode(buff);
	_buffer.append(buff+dataLength._bytes, readed);
	while(readed < dataLength._val)
	{
		unsigned int len = _socket.read(buff, _middleBufferSize);
		_buffer.append(buff, len);
		readed += len;
	}
	delete[] buff;
#ifdef _DEBUG
	std::cout << "BufferedReaderWriter read:\n";
	_buffer.printBytes();
#endif
	return _buffer;
}

void BufferedReaderWriter::sendData(ServiceTypes::Buffer& buff)
{
	MinecraftTypes::VarInt packetSize = buff.size();
	char internalBuffer[5];
	packetSize.encode(internalBuffer);
	_socket.write(internalBuffer, packetSize._bytes);
	_socket.write(buff.data(), buff.size());
#ifdef _DEBUG
	std::cout << "BufferedReaderWriter writed " << buff.size()+packetSize._bytes << " bytes:\n";
	buff.printBytes();
#endif
}

const ServiceTypes::Buffer& BufferedReaderWriter::buffer()
{
	return _buffer;
}