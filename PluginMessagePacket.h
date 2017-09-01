#ifndef  _PLUGIN_MESSAGE_PACKET
#define _PLUGIN_MESSAGE_PACKET

#include "Packet.h"

namespace Packets
{
	namespace ClientPackets
	{
		class PluginMessagePacket : public Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;
			MinecraftTypes::String _channel;
			MinecraftTypes::Short _dataLength;
			ServiceTypes::Buffer _data;

			Packet* clone();
		public:
			PluginMessagePacket(const char* channel = "MC|Brand", MinecraftTypes::Short dataLen = 7, const char* data = "vanilla"); //default values
			PluginMessagePacket(const PluginMessagePacket&);
			~PluginMessagePacket();

			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();
		};
	}
}

#endif // ! _PLUGIN_MESSAGE_PACKET
