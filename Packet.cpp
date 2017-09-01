#include "Packet.h"
#include "PacketsList.h"

using namespace Packets;

bool Packet::_isInited = false;
std::unordered_map<long, Packet*> Packet::_clientPacketsMap;
std::unordered_map<long, Packet*> Packet::_serverPacketsMap;
std::unordered_map<long, Packet*>::const_iterator Packet::_citerator;
std::unordered_map<long, Packet*>::iterator Packet::_iterator;

void Packet::init()
{
	//put here new packets both fore server and client.
	//server packets
	_serverPacketsMap[0x02] = new ServerPackets::LoginSuccessPacket();
	_serverPacketsMap[0x00] = new ServerPackets::KeepAlivePacket();
	_serverPacketsMap[0x05] = new ServerPackets::SpawnPositionPacket();
	//client packets
	_clientPacketsMap[0x03] = new ClientPackets::PlayerPacket();
	_clientPacketsMap[0x04] = new ClientPackets::PlayerPositionPacket();
	_clientPacketsMap[0x15] = new ClientPackets::ClientSettingsPacket();
	_clientPacketsMap[0x17] = new ClientPackets::PluginMessagePacket();
	_isInited = true;
}

Packet* Packet::getServerPacket(long packetID)
{
	if(!_isInited)
	{
		init();
	}
	_citerator = _serverPacketsMap.find(packetID);
	return _citerator == _serverPacketsMap.end() ? NULL : _citerator->second->clone();
}

Packet* Packet::getClientPacket(long packetID)
{
	if(!_isInited)
	{
		init();
	}
	_citerator = _clientPacketsMap.find(packetID);
	return _citerator == _clientPacketsMap.end() ? NULL : _citerator->second->clone();
}

void Packet::process()
{
	// overwrite this method to add your own code in handle()
}