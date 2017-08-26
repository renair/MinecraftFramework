#ifndef _MINECRAFT_BOT
#define _MINECRAFT_BOT

#include "TcpClientSocket.h"
#include "BufferedReaderWriter.h"

class MinecraftBot
{
private:
	NetworkEngine::TcpClientSocket _socket;
	NetworkEngine::BufferedReaderWriter _bufferedIO;

	long readPacketID();
	void handshake();
	void login();

	MinecraftBot(const MinecraftBot&);
	MinecraftBot& operator=(const MinecraftBot&);
public:
	MinecraftBot(const char* addr, const char* port);
	~MinecraftBot();
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
