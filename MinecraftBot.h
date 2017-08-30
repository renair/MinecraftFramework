#ifndef _MINECRAFT_BOT
#define _MINECRAFT_BOT

#include "TcpClientSocket.h"
#include "BufferedReaderWriter.h"
#include "Packet.h"

class MinecraftBot
{
private:
	NetworkEngine::TcpClientSocket _socket;
	NetworkEngine::BufferedReaderWriter _bufferedIO;
	long _protocolVersion;
	MinecraftTypes::String _host;
	MinecraftTypes::UShort _port;
	MinecraftTypes::Position _position;
	bool _isLoggedIn;

	long readPacketID();
	bool handshake();
	void packetProcessing(Packets::Packet*);

	MinecraftBot(const MinecraftBot&) = delete;
	MinecraftBot& operator=(const MinecraftBot&) = delete;
public:
	MinecraftBot(const char* addr, const char* port = "25565", long protocolVersion = 5);
	~MinecraftBot();
	void login(const char*);
	int startHandling();

	//error codes
	static const int PACKET_NOT_FOUND;
	static const int UNEXPECTED_DISCONNECTION;
	static const int UNKNOWN_ERROR;
};


namespace MinecraftBotExceptions
{
	class Exception;
	class NoHostConnection;
}
#endif
