#include "PluginMessagePacket.h"
#include "ChangeIndianess.h"

using namespace Packets;
using namespace ClientPackets;
using namespace NetworkEngine;
using namespace ServiceTypes;

const MinecraftTypes::VarInt PluginMessagePacket::_ID(0x17);

PluginMessagePacket::PluginMessagePacket(const char* channel, MinecraftTypes::Short dataLen, const char* data) :
	_channel(channel),
	_dataLength(dataLen)
{
	_data.writeData(data, _dataLength);
}

PluginMessagePacket::PluginMessagePacket(const PluginMessagePacket& pack):
	_channel(pack._channel),
	_dataLength(pack._dataLength),
	_data(pack._data)
{}

PluginMessagePacket::~PluginMessagePacket()
{}

Packet* PluginMessagePacket::clone()
{
	return new PluginMessagePacket(*this);
}

void PluginMessagePacket::load(const Buffer& buff)
{
	_channel = buff.readString();
	//create tmp variable to chnge indianess later
	MinecraftTypes::Short tmp = 0;
	buff.readData(&tmp, sizeof(tmp));
	_dataLength = changeIndianess<MinecraftTypes::Short>(tmp);
	//create tmp buffer to store readed data
	char* tmpBuff = new char[_dataLength];
	buff.readData(tmpBuff, _dataLength);
	_data.writeData(buff.data(), _dataLength);
	delete[] tmpBuff;
}

Buffer PluginMessagePacket::dump()
{
	Buffer b;
	_ID.write(b);
	b.writeString(_channel);
	MinecraftTypes::Short tmp = changeIndianess<MinecraftTypes::Short>(_dataLength);
	b.writeData(&tmp, sizeof(tmp));
	b.writeData(_data.data(), _dataLength);
	return b;
}

void PluginMessagePacket::handle(BufferedReaderWriter&)
{
	process();
}

long PluginMessagePacket::getID()
{
	return _ID._val;
}