#include "TcpClientSocket.h"
#include "Buffer.h"
#include <iostream>
#if defined(__unix__)
#include<cstring>
#endif

using namespace NetworkEngine;

TcpClientSocket::TcpClientSocket():
	_socket(0), _isConnected(false)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!init(MAKEWORD(2, 0))) //version 2
	{
		std::cout << "Error in initialization socket!" << std::endl;
	}
#elif defined(__unix__)
	init(0); // create socket here
#endif
}

TcpClientSocket::TcpClientSocket(const char* host, const char* port):
	_isConnected(false)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!init(MAKEWORD(2, 0))) //version 2
	{
		std::cout << "Error in initialization socket!" << std::endl;
		return;
	}
#elif defined(__unix__)
	init(0); // create socket here
#endif
	connect(host, port);
}

TcpClientSocket::~TcpClientSocket()
{
	freeaddrinfo(_addrinfo);
	close();
}

bool TcpClientSocket::connect(const char* host, const char* port)
{
	ADDRINFO hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(host, port, &hints, &_addrinfo)) //return 0 on success
	{
		std::cout << "Can't found " << host << ':' << port << std::endl;
		return false;
	}
	if(::connect(_socket, _addrinfo->ai_addr, _addrinfo->ai_addrlen)) //return 0 on success
	{
		std::cout << "Can't connect to " << host << ':' << port << std::endl;
		return false;
	}
	_isConnected = true;
	return true;
}

bool TcpClientSocket::init(WORD WSAVersion)
{
#if defined(_WIN32) || defined(_WIN64)
	if (WSAStartup(WSAVersion, &_wsadata)) //return 0 on success
	{
		std::cout << "WSAStartup error!" << std::endl;
		return false;
	}
	if (_wsadata.wVersion != 2 || _wsadata.wHighVersion < 2)
	{
		std::cout << "Not supported WSA version." << std::endl;
		return false;
	}
#endif
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socket == SOCKET_ERROR)
	{
		std::cout << "Can't create socket!" << std::endl;
		return false;
	}
	return true;
}

int TcpClientSocket::read(char* buff, unsigned int len) const
{
	if(!isConnected())
	{
		std::cout << "Socket is not connected. Can not read." << std::endl;
		return -1;
	}
	int bytesRead = recv(_socket, buff, len, 0);
	if(bytesRead < 0)
	{
		std::cout << "Can not read from socket." << std::endl;
		_isConnected = false;
	}
	return bytesRead;
}

int TcpClientSocket::write(const char* buff, unsigned int len) const
{
	if(!isConnected())
	{
		std::cout << "Socket is not connected. Can not write." << std::endl;
		return -1;
	}
	int bytesWritten = send(_socket, buff, len, 0);
	if(bytesWritten < 0)
	{
		std::cout << "Can not write to socket." << std::endl;
		_isConnected = false;
	}
	return bytesWritten;
}

void TcpClientSocket::close() const
{
	if(isConnected())
	{
#if defined(_WIN32) || defined(_WIN64)
		::closesocket(_socket);
#elif defined(__unix__)
		::close(_socket);
#endif
		_isConnected = false;
	}
}

bool TcpClientSocket::isConnected() const
{
	return _isConnected;
}
