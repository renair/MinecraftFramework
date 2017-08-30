#ifndef _SPAWN_POSITION_PACKET
#define _SPAWN_PROTECTION_PACKET

#include <iostream>
#include "Packet.h"

namespace Packets
{
	namespace ServerPackets
	{
		class SpawnPositionPacket : public Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			MinecraftTypes::Int _X;
			MinecraftTypes::Int _Y;
			MinecraftTypes::Int _Z;

			Packet* clone();
		public:
			SpawnPositionPacket();
			SpawnPositionPacket(MinecraftTypes::Int x, MinecraftTypes::Int y, MinecraftTypes::Int z);
			SpawnPositionPacket(const SpawnPositionPacket&);
			~SpawnPositionPacket();
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();

			MinecraftTypes::Int& getX();
			MinecraftTypes::Int& getY();
			MinecraftTypes::Int& getZ();
		};

		std::ostream& operator<<(std::ostream&, SpawnPositionPacket&);
	}
}


#endif
