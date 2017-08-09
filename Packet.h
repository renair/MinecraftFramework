#ifndef _PACKETS
#define _PACKETS

#include "Types.h"
#include "BufferedReaderWriter.h"
#include <unordered_map>

namespace Packets
{
	class Packet
	{
	private:
		static std::unordered_map<long, Packet* const> _clientPacketsMap;
		static std::unordered_map<long, Packet* const> _serverPacketsMap;
		static std::unordered_map<long, Packet* const>::const_iterator _citerator;
		static std::unordered_map<long, Packet* const>::iterator _iterator;
		static bool _isInited;
		static void init();
		virtual Packet* clone() = 0;
	public:
		//static void registerServerPacket(long, Packet* const); //TODO
		//static void registerClientPacket(long, Packet* const); //TODO
		static Packet* getServerPacket(long ID);
		static Packet* getClientPacket(long ID);
		virtual void load(const ServiceTypes::Buffer&) = 0;
		virtual ServiceTypes::Buffer dump() = 0;
		virtual void handle(NetworkEngine::BufferedReaderWriter&) = 0;
		virtual long getID() = 0;
	};

	namespace ClientPackets
	{
		class Handshake : public Packet
		{
		public:
			const static MinecraftTypes::VarInt _packetID;
			MinecraftTypes::VarInt _protocolVersion;
			MinecraftTypes::String _serverAddress;
			MinecraftTypes::UShort _serverPort;
			MinecraftTypes::VarInt _nextState;
			//next state constants
			const static MinecraftTypes::VarInt STATUS;
			const static MinecraftTypes::VarInt LOGIN;
		};

		class AuthPacket
		{
		public:
			const static MinecraftTypes::Byte _packetID = 0x00;
			MinecraftTypes::Byte _protocolVersion;
			MinecraftTypes::String _UserName;
			MinecraftTypes::String _AuthToken;
			MinecraftTypes::Short _Unused = 0;
		};

		class LoginSuccess
		{
		public:
			const static MinecraftTypes::Byte _packetID = 0x02;
			MinecraftTypes::String _UUID;
			MinecraftTypes::String Username;
		};

		class ModifyBlock
		{
		public:
			enum ModifyType { Destroy = 0, Build = 1 };
			const static MinecraftTypes::Byte _packetID = 0x05;
			MinecraftTypes::Short _X;
			MinecraftTypes::Short _Y;
			MinecraftTypes::Short _Z;
			MinecraftTypes::Byte _Mode = Build;
			MinecraftTypes::Byte _BlockType;
		};

		class PositionOrientation
		{
		public:
			const static MinecraftTypes::Byte _packetID = 0x08;
			MinecraftTypes::Byte _PlayerID = 255;
			MinecraftTypes::Short _X;
			MinecraftTypes::Short _Y;
			MinecraftTypes::Short _Z;
			MinecraftTypes::Byte _Direction;
			MinecraftTypes::Byte _Angle;
		};
	}

	namespace ServerPackets
	{

	}
}
#endif