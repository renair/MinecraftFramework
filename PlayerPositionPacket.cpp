#include "PlayerPositionPacket.h"
#include "ChangeIndianess.h"

using namespace Packets;
using namespace ClientPackets;
using namespace ServiceTypes;
using namespace NetworkEngine;

const MinecraftTypes::VarInt PlayerPositionPacket::_ID(0x04);

PlayerPositionPacket::PlayerPositionPacket() :
	PlayerPacket(true), _X(0), _FeetY(0), _HeadY(1.60), _Z(0)
{}

PlayerPositionPacket::PlayerPositionPacket(MinecraftTypes::Double x, MinecraftTypes::Double y, MinecraftTypes::Double z, MinecraftTypes::Boolean isOnGround):
	PlayerPacket(isOnGround), _X(x), _FeetY(y),_HeadY(_FeetY + 1.60), _Z(z)
{}

PlayerPositionPacket::PlayerPositionPacket(const PlayerPositionPacket& p):
	PlayerPacket(p), _X(p._X), _FeetY(p._FeetY),_HeadY(p._HeadY)
{}

PlayerPositionPacket::~PlayerPositionPacket()
{}

Packet* PlayerPositionPacket::clone()
{
	return new PlayerPositionPacket(*this);
}

void PlayerPositionPacket::load(const ServiceTypes::Buffer& b)
{
	MinecraftTypes::Double tmp = 0;
	//read coords
	b.readData(&tmp, sizeof(tmp));
	_X = changeIndianess<MinecraftTypes::Double>(tmp);
	b.readData(&tmp, sizeof(tmp));
	_FeetY = changeIndianess<MinecraftTypes::Double>(tmp);
	b.readData(&tmp, sizeof(tmp));
	_HeadY = changeIndianess<MinecraftTypes::Double>(tmp);
	b.readData(&tmp, sizeof(tmp));
	_Z = changeIndianess<MinecraftTypes::Double>(tmp);
	//read isOnGround
	b.readData(&_isOnEarth, sizeof(_isOnEarth));
}

Buffer PlayerPositionPacket::dump()
{
	Buffer b;
	_ID.write(b);
	//write coords
	MinecraftTypes::Double tmp = changeIndianess<MinecraftTypes::Double>(_X);
	b.writeData(&tmp, sizeof(tmp));
	tmp = changeIndianess<MinecraftTypes::Double>(_FeetY);
	b.writeData(&tmp, sizeof(tmp));
	tmp = changeIndianess<MinecraftTypes::Double>(_HeadY);
	b.writeData(&tmp, sizeof(tmp));
	tmp = changeIndianess<MinecraftTypes::Double>(_Z);
	b.writeData(&tmp, sizeof(tmp));
	//writeing isOnEarth
	b.writeData(&_isOnEarth, sizeof(_isOnEarth));

	return b;
}

void PlayerPositionPacket::handle(NetworkEngine::BufferedReaderWriter&)
{
	process();
}

long PlayerPositionPacket::getID()
{
	return _ID._val;
}