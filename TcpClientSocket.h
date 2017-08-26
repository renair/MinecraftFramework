#ifndef _TCP_SOCKET
#define _TCP_SOCKET

#if defined(_WIN32) || defined(_WIN64)

//Windows compilation
#pragma comment(lib, "ws2_32.lib")
#include<WinSock2.h>
#include <WS2tcpip.h>

#elif defined(__unix__)

//unix compilation
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h> //for close(_socket)
#define SOCKET int //like in windows
#define WORD short //like in windows
#define ADDRINFO addrinfo
#define SOCKET_ERROR -1

#endif

namespace NetworkEngine
{
	class TcpClientSocket
	{
	private:
		mutable bool _isConnected;
		SOCKET _socket;
		struct addrinfo* _addrinfo;
#if defined(_WIN32) || defined(_WIN64)
		WSADATA _wsadata;
#endif
		TcpClientSocket(const TcpClientSocket&); //close copy constructor
		TcpClientSocket& operator=(const TcpClientSocket&); //close operator=
		bool init(WORD WSAVersion);
	public:
		TcpClientSocket();
		TcpClientSocket(const char* host, const char* port);
		~TcpClientSocket();
		bool connect(const char* host, const char* port);
		unsigned int read(char* buff, unsigned int len) const;
		unsigned int write(const char* buff, unsigned int len) const;
		void close() const;
		bool isConnected() const;
	};
}
#endif
