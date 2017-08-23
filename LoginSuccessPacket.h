#ifndef _LOGIN_SUCCESS_PACKET
#define _LOGIN_SUCCESS_PACKET

#include "Packet.h"

namespace Packets
{
	namespace ServerPackets
	{
		class LoginSuccessPacket : public Packet
		{
		private:
			static const long _ID;
			MinecraftTypes::String _UUID;
			MinecraftTypes::String _userName;
		public:
			LoginSuccessPacket();
			LoginSuccessPacket(char* uuid, char* name);
			LoginSuccessPacket(const LoginSuccessPacket&);
			Packet* clone();
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();
		};
	}
}


#endif