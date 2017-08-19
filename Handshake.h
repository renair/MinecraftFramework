#ifndef _PACKET_HANDSHAKE

#include "Packet.h"

namespace Packets
{
	namespace ClientPackets
	{
		class HandshakePacket : public Packet
		{
		private:
			const static MinecraftTypes::VarInt _ID;
			MinecraftTypes::VarInt _protocolVersion;
			MinecraftTypes::String _serverAddress;
			MinecraftTypes::UShort _serverPort;
			MinecraftTypes::VarInt _nextState;
			Packet* clone();
		public:
			HandshakePacket(long protoVersion, const char* host, MinecraftTypes::UShort port, long nextState);
			HandshakePacket(const HandshakePacket&);
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();
		};
	}
}

#endif // !_PACKET_HANDSHAKE
