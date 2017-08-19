#include "MinecraftBot.h"
#include "Packet.h"
#include "PacketsList.h"
#include <iostream>

using namespace std;

MinecraftBot::MinecraftBot(char* addr, char* port):
	_socket(addr, port), _bufferedIO(_socket)
{
	if(_socket.isConnected())
	{
		cout << "Connection succes" << endl;
	}
	else
	{
		cout << "Can't connect to host " << addr << ':' << port << endl;
		//throw MinecraftBotExceptions::NoHostConnection;
	}
}

MinecraftBot::~MinecraftBot()
{
	_socket.close();
}

long MinecraftBot::readPacketID()
{
	MinecraftTypes::VarInt res(0);
	res.decode(_bufferedIO.buffer().data());
	return res._val;
}

void MinecraftBot::handshake()
{
	//TODO implement method
	long protoVer = 5;
	char* host = "platinium.ddns.net";
	MinecraftTypes::UShort port = 25565; //default port
	long nextState = 1; // get server status
	// 1 - status
	// 2 - login
	Packets::ClientPackets::HandshakePacket handshake(protoVer, host, port, nextState);
}

void MinecraftBot::login()
{
	handshake();
	//TODO implement method
}

int MinecraftBot::startHandling()
{
	login();
	while(true)
	{
		_bufferedIO.readData();
		long packetID = readPacketID();
		std::cout << "Received packet #" << packetID;
		Packets::Packet* packet = Packets::Packet::getServerPacket(packetID);
		packet->handle(_bufferedIO);
		std::cout << "\thandled" << std::endl;
		delete packet;
	}
}