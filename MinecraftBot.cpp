#include "MinecraftBot.h"
#include "Packet.h"
#include <iostream>

MinecraftBot::MinecraftBot(char* addr, char* port):
	_socket(addr, port), _bufferedIO(_socket)
{
	if(_socket.isConnected())
	{
		std::cout << "Connection succes" << std::endl;
	}
	else
	{
		std::cout << "Can't connect to host " << addr << ':' << port << std::endl;
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
	//TODO implement mathod
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
		long packetID = readPacketID();
		std::cout << "Received packet #" << packetID;
		Packets::Packet* packet = Packets::Packet::getServerPacket(packetID);
		packet->handle(_bufferedIO);
		std::cout << "\thandled" << std::endl;
		delete packet;
	}
}