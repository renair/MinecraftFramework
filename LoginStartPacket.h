#ifndef _LOGIN_START_PACKET

#include "Packet.h"

namespace Packets
{
	namespace ClientPackets
	{
		class LoginStartPacket : public Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			MinecraftTypes::String _name;
		public:
			LoginStartPacket(const char* name);
			LoginStartPacket(const LoginStartPacket&);
			Packet* clone();
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();
		};
	}
}

#endif