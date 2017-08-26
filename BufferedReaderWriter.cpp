#include "BufferedReaderWriter.h"
#include <algorithm>

using namespace NetworkEngine;

const unsigned int BufferedReaderWriter::_middleBufferSize = 1024;

BufferedReaderWriter::BufferedReaderWriter(TcpClientSocket& sock):
	_socket(sock), _buffer(1024)
{}

MinecraftTypes::VarInt BufferedReaderWriter::readVarInt(unsigned int offset)
{
	_buffer.offset() = offset;
	MinecraftTypes::VarInt result(0);
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
	_buffer.clear();
	char buff[_middleBufferSize]; //binaries takes more space but it works faster
	unsigned long readed = _socket.read(buff, _middleBufferSize);
	while(readed < 5) //VarInt contain maximum 5 bytes
	{
		readed += _socket.read(buff + readed, _middleBufferSize - readed);
	}
	MinecraftTypes::VarInt dataLength(0);
	readed -= dataLength.decode(buff); //amount of VarInt bytes decoded
	_buffer.writeData(buff+dataLength._bytes, readed); //write data without VarInt
	while(readed < dataLength._val)
	{
		unsigned int len = _socket.read(buff, min(dataLength._val - readed, 1024)); //in prevent reading more than in packet bytes
		_buffer.writeData(buff, len);
		readed += len;
	}
	return _buffer;
}

void BufferedReaderWriter::sendData(const ServiceTypes::Buffer& buff)
{
	MinecraftTypes::VarInt packetSize(buff.size());
	char internalBuffer[5];
	packetSize.encode(internalBuffer);
	_socket.write(internalBuffer, packetSize._bytes);
	_socket.write(buff.data(), buff.size());
}

const ServiceTypes::Buffer& BufferedReaderWriter::buffer()
{
	return _buffer;
}
