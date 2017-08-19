#include "Handshake.h"

using namespace Packets;
using namespace ClientPackets;
using namespace MinecraftTypes;
using namespace ServiceTypes;

const MinecraftTypes::VarInt HandshakePacket::_ID(0x0);

HandshakePacket::HandshakePacket(const HandshakePacket& pack):
	_protocolVersion(pack._protocolVersion._val),
	_serverAddress(pack._serverAddress),
	_serverPort(pack._serverPort),
	_nextState(pack._nextState._val)
{}

HandshakePacket::HandshakePacket(long protoVersion, const char* host, UShort port, long nextState):
	_protocolVersion(protoVersion),
	_serverAddress(host),
	_serverPort(port),
	_nextState(nextState)
{}

Packet* HandshakePacket::clone()
{
	return new HandshakePacket(*this);
}

void HandshakePacket::load(const Buffer& buff)
{
	//TODO throw ServerBoundClass
}

Buffer HandshakePacket::dump()
{
	Buffer buff;
	_ID.write(buff);
	_protocolVersion.write(buff);
	buff.writeData(_serverAddress.cstring(), _serverAddress.bytes());
	buff.writeData(&_serverPort, sizeof(_serverPort));
	_nextState.write(buff);
	return buff;
}

void HandshakePacket::handle(NetworkEngine::BufferedReaderWriter&)
{
	process();
}


long HandshakePacket::getID()
{
	return _ID._val;
}
