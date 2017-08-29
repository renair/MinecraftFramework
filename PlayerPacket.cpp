#include "PlayerPacket.h"

using namespace Packets;
using namespace ClientPackets;
using namespace ServiceTypes;
using namespace MinecraftTypes;
using namespace NetworkEngine;

const MinecraftTypes::VarInt PlayerPacket::_ID(0x03);

PlayerPacket::PlayerPacket(bool isOnEarth):
	_isOnEarth(isOnEarth)
{}

PlayerPacket::PlayerPacket(const PlayerPacket& copy):
	_isOnEarth(copy._isOnEarth)
{}

PlayerPacket::~PlayerPacket()
{}

Packet* PlayerPacket::clone()
{
	return new PlayerPacket(*this);
}

void PlayerPacket::load(const Buffer& buff)
{
	//TODO read ID and compare
	buff.readData(&_isOnEarth, sizeof(_isOnEarth));
}


Buffer PlayerPacket::dump()
{
	Buffer b;
	_ID.write(b);
	b.writeData(&_isOnEarth, sizeof(_isOnEarth));
	return b;
}

void PlayerPacket::handle(BufferedReaderWriter& io)
{
	process();
	//nothing to handle in client packets
}

long PlayerPacket::getID()
{
	return _ID._val;
}