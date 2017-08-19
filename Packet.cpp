#include "Packet.h"

using namespace Packets;

bool Packet::_isInited = false;
std::unordered_map<long, Packet* const> Packet::_clientPacketsMap;
std::unordered_map<long, Packet* const> Packet::_serverPacketsMap;
std::unordered_map<long, Packet* const>::const_iterator Packet::_citerator;
std::unordered_map<long, Packet* const>::iterator Packet::_iterator;

void Packet::init()
{
	//put here new packets both fore server and client.
	//_clientPacketsMap[0] = new ClientPackets::Handshake();

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