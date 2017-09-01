#ifndef  _PLAYER_POSITION_PACKET

#include "PlayerPacket.h"

namespace Packets
{
	namespace ClientPackets
	{
		class PlayerPositionPacket : public PlayerPacket
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			Packet* clone();
		protected:
			MinecraftTypes::Double _X;
			MinecraftTypes::Double _FeetY; // _HeadY - 1.65 normally
			MinecraftTypes::Double _HeadY; // absolytely head Y
			MinecraftTypes::Double _Z;
		public:
			PlayerPositionPacket();
			PlayerPositionPacket(MinecraftTypes::Double x, MinecraftTypes::Double y, MinecraftTypes::Double z, MinecraftTypes::Boolean isOnGround = true);
			PlayerPositionPacket(const PlayerPositionPacket&);
			~PlayerPositionPacket();

			virtual void load(const ServiceTypes::Buffer&);
			virtual ServiceTypes::Buffer dump();
			virtual void handle(NetworkEngine::BufferedReaderWriter&);
			virtual long getID();
		};
	}
}

#endif // ! _PLAYER_POSITION_PACKET
