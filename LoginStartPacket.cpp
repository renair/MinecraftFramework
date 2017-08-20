#include "LoginStartPacket.h"

using namespace Packets;
using namespace ClientPackets;
using namespace ServiceTypes;
using namespace NetworkEngine;

const MinecraftTypes::VarInt LoginStartPacket::_ID(0x0);

LoginStartPacket::LoginStartPacket(const char* name):
	_name(name)
{}

LoginStartPacket::LoginStartPacket(const LoginStartPacket& pack):
	_name(pack._name)
{}

Packet* LoginStartPacket::clone()
{
	return new LoginStartPacket(*this);
}

void LoginStartPacket::load(const Buffer& buff)
{
	//TODO throw Server bounded method\
	// OR
	//TODO implement loading
}

Buffer LoginStartPacket::dump()
{
	Buffer buff;
	_ID.write(buff);
	buff.writeString(_name);
	return buff;
}

void LoginStartPacket::handle(BufferedReaderWriter& buffIO)
{
	process();
}

long LoginStartPacket::getID()
{
	return _ID._val;
}