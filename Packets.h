#ifndef _PACKETS
#define _PACKETS

#include "Types.h"

namespace ClientPackets
{
	struct AuthPacket
	{
		MinecraftTypes::byte _packetID;
		MinecraftTypes::byte _protocolVersion;
		
	};
}

namespace ServerPackets
{

}

#endif