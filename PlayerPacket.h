#ifndef _PALYER_PACKET
#include "Packet.h"


namespace Packets
{
	namespace ClientPackets
	{
		class PlayerPacket : Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			
			virtual Packet* clone();
		protected:
			MinecraftTypes::Boolean _isOnEarth;
		public:
			PlayerPacket(bool isOnEarth = true);
			PlayerPacket::PlayerPacket(const PlayerPacket& copy);
			~PlayerPacket();
			virtual void load(const ServiceTypes::Buffer&);
			virtual ServiceTypes::Buffer dump();
			virtual void handle(NetworkEngine::BufferedReaderWriter&);
			virtual long getID();
		};
	}
}

#endif // !_PALYER_PACKET

