#include <iostream>
#include "SpawnPositionPacket.h"
#include "ChangeIndianess.h"

using namespace Packets;
using namespace ServerPackets;
using namespace ServiceTypes;
using namespace NetworkEngine;
using namespace MinecraftTypes;

const MinecraftTypes::VarInt SpawnPositionPacket::_ID(0x05);

SpawnPositionPacket::SpawnPositionPacket() :
	_X(0), _Y(0), _Z(0)
{}

SpawnPositionPacket::SpawnPositionPacket(Int x, Int y, Int z) :
	_X(x), _Y(y), _Z(z)
{}

SpawnPositionPacket::SpawnPositionPacket(const SpawnPositionPacket& pack) :
	_X(pack._X), _Y(pack._Y), _Z(pack._Z)
{/*default copy constructor*/}


SpawnPositionPacket::~SpawnPositionPacket()
{/*default destructor*/}

Packet* SpawnPositionPacket::clone()
{
	return new SpawnPositionPacket(*this);
}

Buffer SpawnPositionPacket::dump()
{
	Buffer b;
	_ID.write(b);
	Int tmp = changeIndianess<Int>(_X); //change to big endian
	b.writeData(&tmp, sizeof(Int));
	tmp = changeIndianess<Int>(_Y); //change to big endian
	b.writeData(&tmp, sizeof(Int));
	tmp = changeIndianess<Int>(_Z); //change to big endian
	b.writeData(&tmp, sizeof(Int));
	return b;
}

void SpawnPositionPacket::load(const Buffer& buff)
{
	Int tmp = 0;
	buff.readData(&tmp, sizeof(tmp));
	_X = changeIndianess<Int>(tmp);
	buff.readData(&tmp, sizeof(tmp));
	_Y = changeIndianess<Int>(tmp);
	buff.readData(&tmp, sizeof(tmp));
	_Z = changeIndianess<Int>(tmp);
}

void SpawnPositionPacket::handle(BufferedReaderWriter& io)
{
	process();
}

long SpawnPositionPacket::getID()
{
	return _ID._val;
}

Int& SpawnPositionPacket::getX()
{
	return _X;
}

Int& SpawnPositionPacket::getY()
{
	return _Y;
}

Int& SpawnPositionPacket::getZ()
{
	return _Z;
}

std::ostream& Packets::ServerPackets::operator<<(std::ostream& os, SpawnPositionPacket& pack)
{
	return os << '(' << pack.getX() << ';' << pack.getY() << ';' << pack.getZ() << ')';
}