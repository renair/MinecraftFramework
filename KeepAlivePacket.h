#ifndef _KEEP_ALIVE_PACKET

#include "Packet.h"

namespace Packets
{
	namespace ServerPackets
	{
		class KeepAlivePacket : public Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			MinecraftTypes::Int _keepAliveID;
			Packet* clone();
		public:
			KeepAlivePacket();
			KeepAlivePacket(const KeepAlivePacket&);
			KeepAlivePacket(MinecraftTypes::Int id);
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();
		};
	}
}


#endif // !_KEEP_ALIVE_PACKET
