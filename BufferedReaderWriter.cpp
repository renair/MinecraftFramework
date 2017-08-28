#include "BufferedReaderWriter.h"
#include <algorithm>
#include <iostream>

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
	MinecraftTypes::VarInt dataLength(0);
	char buff[_middleBufferSize];
	long readed = 0;
	do
	{
		readed = _socket.read(buff, 1);
		if(readed == 1)
		{
			continue;
		}
		else if (readed < 0)
		{
			_buffer.clear();
			return _buffer; //return if socket broken
		}
	} while (!dataLength.decodeByte(buff[0]));
	readed = 0;
	while(readed < dataLength._val)
	{
		int len = _socket.read(buff, std::min<long>(dataLength._val - readed, 1024)); //in prevent reading more than in packet bytes
		if(len < 0)
		{
			_buffer.clear();
			break;
		}
		_buffer.writeData(buff, len);
		readed += len;
	}
	return _buffer;
}

void BufferedReaderWriter::sendData(const ServiceTypes::Buffer& buff)
{
	MinecraftTypes::VarInt packetSize(buff.size());
	char internalBuffer[MinecraftTypes::VarInt::_maxBytes];
	packetSize.encode(internalBuffer);
	_socket.write(internalBuffer, packetSize._bytes);
	_socket.write(buff.data(), buff.size());
}

const ServiceTypes::Buffer& BufferedReaderWriter::buffer()
{
	return _buffer;
}
