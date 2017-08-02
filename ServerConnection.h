#ifndef _SERVER_CONNECTION
#define _SERVER_CONNECTION

#include<string>

class ServerConnection
{
private:
public:
	ServerConnection(std::string, int port);
	~ServerConnection();
	bool login(std::string name);
};

#endif