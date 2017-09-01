#include "MinecraftBot.h"
#include "PacketsList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace Packets;
using namespace ClientPackets;

MinecraftBot::MinecraftBot(const char* addr, const char* port, long protocolVersion) :
	_socket(addr, port),
	_bufferedIO(_socket),
	_protocolVersion(protocolVersion),
	_host(addr),
	_port(static_cast<short>(std::stoi(port))),
	_isLoggedIn(false)
{
	if(_socket.isConnected())
	{
		cout << "Connection succes" << endl;
	}
}

MinecraftBot::~MinecraftBot()
{
	_socket.close();
}

long MinecraftBot::readPacketID()
{
	MinecraftTypes::VarInt res(0);
	_bufferedIO.buffer().offset() = 0; //to read first bytes
	res.read(_bufferedIO.buffer());
	return res._val;
}

bool MinecraftBot::handshake()
{
	long nextState = 2; // get server status
	// 1 - status
	// 2 - login
	if(_socket.isConnected())
	{
		HandshakePacket handshake(_protocolVersion, _host.cstring(), _port, nextState);
		_bufferedIO.sendData(handshake.dump());
	}
	return _socket.isConnected();
}

void MinecraftBot::login(const char* name)
{
	if(handshake())
	{
		LoginStartPacket pack(name);
		_bufferedIO.sendData(pack.dump());
		if(_socket.isConnected())
		{
			_isLoggedIn = true;
		}
	}
}

int MinecraftBot::startHandling()
{
	unsigned long long i = 0;
	std::ofstream file("packets_log.txt");
	while(_isLoggedIn && _socket.isConnected())
	{
		_bufferedIO.readData();
		long packetID = readPacketID();
		file << "Received packet 0x" << hex << packetID << '\t' << dec << _bufferedIO.buffer().size() << " bytes" <<  std::endl;
		_bufferedIO.buffer().printBytes(file);
		file << std::endl;
		Packets::Packet* packet = Packets::Packet::getServerPacket(packetID);
		
		/*if (++i % 100 == 0)
		{
			ClientPackets::PlayerPositionPacket move(-147.5+0.01*i, 85.0, -132.5 + 0.01*i);
			std::cout << "Move" << std::endl;
			_bufferedIO.sendData(move.dump());
		}*/

		if(packet != NULL)
		{
			packet->load(_bufferedIO.buffer());
			//preprocess packet
			packetProcessing(packet);
			packet->handle(_bufferedIO);
			std::cout << packetID << "\thandled" << std::endl;
			delete packet; // delete if only packet was created
		}
		else
		{
			//std::cout << "\tnot found" << std::endl;
		}
	}
	return 0;
}

void MinecraftBot::packetProcessing(Packets::Packet* pack)
{
	//ClientPackets::PlayerPositionPacket move(_position._coords._x, _position._coords._y, _position._coords._z);
	switch(pack->getID())
	{
	case 0x00: //keep alive packet
		/*_position._coords._x += 1;
		_position._coords._z += 1;
		move.dump().printBytes();
		_bufferedIO.sendData(move.dump());*/
		break;
	case 0x05: // spawn position packet
		ServerPackets::SpawnPositionPacket* spp = static_cast<ServerPackets::SpawnPositionPacket*>(pack);
		_position._coords._x = spp->getX();
		_position._coords._y = spp->getY();
		_position._coords._z = spp->getZ();
		std::cout << "Spawned at: " << *spp << std::endl;
		break;
	}
}
