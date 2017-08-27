#include "KeepAlivePacket.h"

using namespace Packets;
using namespace ServerPackets;
using namespace NetworkEngine;
using namespace ServiceTypes;

const long KeepAlivePacket::_ID = 0x00;

KeepAlivePacket::KeepAlivePacket() :
	_keepAliveID(0)
{}

KeepAlivePacket::KeepAlivePacket(const KeepAlivePacket& pack):
	_keepAliveID(pack._keepAliveID)
{}

KeepAlivePacket::KeepAlivePacket(MinecraftTypes::Int id):
	_keepAliveID(id)
{}

Packet* KeepAlivePacket::clone()
{
	return new KeepAlivePacket(*this);
}

void KeepAlivePacket::load(const Buffer& buff)
{
	buff.readData(&_keepAliveID, sizeof(_keepAliveID));
}

Buffer KeepAlivePacket::dump()
{
	Buffer b;
	b.writeData(&_keepAliveID, sizeof(_keepAliveID));
	return b;
}

void KeepAlivePacket::handle(BufferedReaderWriter& io)
{
	process();
	io.sendData(dump());
}

long KeepAlivePacket::getID()
{
	return _ID;
}
