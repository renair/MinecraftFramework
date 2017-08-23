#include "LoginSuccessPacket.h"

using namespace Packets;
using namespace ServerPackets;
using namespace ServiceTypes;
using namespace NetworkEngine;
using namespace MinecraftTypes;

const long LoginSuccessPacket::_ID = 0x02;


LoginSuccessPacket::LoginSuccessPacket():
	_UUID(""),
	_userName("")
{}

LoginSuccessPacket::LoginSuccessPacket(char* uuid, char* name):
	_UUID(uuid), _userName(name)
{}

LoginSuccessPacket::LoginSuccessPacket(const LoginSuccessPacket& pack):
	_UUID(pack._UUID),
	_userName(pack._userName)
{}

Packet* LoginSuccessPacket::clone()
{
	return new LoginSuccessPacket(*this);
}

void LoginSuccessPacket::load(const Buffer& buff)
{
	_UUID = buff.readString();
	_userName = buff.readString();
}

Buffer LoginSuccessPacket::dump()
{
	Buffer b;
	b.writeString(_UUID);
	b.writeString(_userName);
	return b;
}

void LoginSuccessPacket::handle(BufferedReaderWriter& io)
{
	process();
}

long LoginSuccessPacket::getID()
{
	return _ID;
}