#include "TcpClientSocket.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace NetworkEngine;

TcpClientSocket::TcpClientSocket():
	_socket(0), _isConnected(false)
{
	if(!init(MAKEWORD(2, 0))) //version 2
	{
		std::cout << "Error in initialization socket!" << std::endl;
	}
}

TcpClientSocket::TcpClientSocket(const char* host, const char* port)
{
	if(!init(MAKEWORD(2, 0))) //version 2
	{
		std::cout << "Error in initialization socket!" << std::endl;
		return;
	}
	if(!connect(host, port))
	{
		std::cout << "Can't connect to the " << host << ':' << port << std::endl;
	}
}

TcpClientSocket::~TcpClientSocket()
{
	freeaddrinfo(_addrinfo);
}

bool TcpClientSocket::connect(const char* host, const char* port)
{
	ADDRINFO hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (int a = getaddrinfo(host, port, &hints, &_addrinfo)) //return 0 on success
	{
		std::cout << "Can't found " << host << ':' << port << std::endl;
		return false;
	}
	if(::connect(_socket, _addrinfo->ai_addr, _addrinfo->ai_addrlen)) //return 0 on success
	{
		std::cout << "Can't connect to host." << std::endl;
		return false;
	}
	_isConnected = true;
	return true;
}

bool TcpClientSocket::init(WORD WSAVersion)
{
	//TODO throw error CantStartWSA
	if (WSAStartup(WSAVersion, &_wsadata)) //return 0 on success
	{
		std::cout << "WSAStartup error!" << std::endl;
		return false;
	}
	//TODO throw error "NoSupportableVersion"
	if (_wsadata.wVersion != 2 || _wsadata.wHighVersion < 2)
	{
		std::cout << "Not supported version." << std::endl;
		return false;
	}
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socket == SOCKET_ERROR)
	{
		std::cout << "Can't create socket!" << std::endl;
		return false;
	}
	return true;
}

unsigned int TcpClientSocket::read(char* buff, unsigned int len) const
{
	int bytesReaded = recv(_socket, buff, len, 0);
	return bytesReaded > 0 ? bytesReaded : 0;
}

unsigned int TcpClientSocket::write(char* buff, unsigned int len) const
{
	int bytesWrited = send(_socket, buff, len, 0);
	return bytesWrited > 0 ? bytesWrited: 0;
}

bool TcpClientSocket::isConnected()
{
	return _isConnected;
}
