#ifndef _TCP_SOCKET
#define _TCP_SOCKET

#pragma comment(lib, "ws2_32.lib")
#include<WinSock2.h>

namespace NetworkEngine
{
	class TcpClientSocket
	{
	private:
		mutable bool _isConnected;
		SOCKET _socket;
		struct addrinfo* _addrinfo;
		WSADATA _wsadata;

		TcpClientSocket(const TcpClientSocket&); //close copy constructor
		TcpClientSocket& operator=(const TcpClientSocket&); //close operator=
		bool init(WORD WSAVersion);
	public:
		TcpClientSocket();
		TcpClientSocket(const char* host, const char* port);
		~TcpClientSocket();
		bool connect(const char* host, const char* port);
		unsigned int read(char* buff, unsigned int len) const;
		unsigned int write(char* buff, unsigned int len) const;
		void close() const;
		bool isConnected() const;
	};
}
#endif