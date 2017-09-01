#ifndef _CLIENT_SETTINGS_PACKET
#define _CLIENT_SETTINGS_PACKET

#include "Packet.h"

namespace Packets
{
	namespace ClientPackets
	{
		class ClientSettingsPacket : public Packet
		{
		private:
			static const MinecraftTypes::VarInt _ID;

			MinecraftTypes::String _locale;
			MinecraftTypes::Byte _viewDistance;
			MinecraftTypes::Byte _chatFlags;
			MinecraftTypes::Boolean _chatColors;
			MinecraftTypes::Byte _difficulty;
			MinecraftTypes::Boolean _showCape;

			Packet* clone();
		public:
			ClientSettingsPacket(const char* locale = "en_GB", MinecraftTypes::Byte viewDistance = 5, MinecraftTypes::Byte chatFlags = CHAT_ENABLED,
				MinecraftTypes::Boolean chatColors = true,	MinecraftTypes::Byte difficulty = DIFF_NORMAl, MinecraftTypes::Boolean showCape = true);
			ClientSettingsPacket(const ClientSettingsPacket&);
			~ClientSettingsPacket();
			//selectors-modifiers
			MinecraftTypes::String& locale();
			MinecraftTypes::Byte& viewDistance();
			MinecraftTypes::Byte& chatFlags();
			MinecraftTypes::Boolean& chatColors();
			MinecraftTypes::Byte& difficulty();
			MinecraftTypes::Boolean& showCape();
			//Packet interface methods
			void load(const ServiceTypes::Buffer&);
			ServiceTypes::Buffer dump();
			void handle(NetworkEngine::BufferedReaderWriter&);
			long getID();

			//chat flags
			static const MinecraftTypes::Byte CHAT_ENABLED;
			static const MinecraftTypes::Byte CHAT_COMMANDS_ONLY;
			static const MinecraftTypes::Byte CHAT_HIDDEN;
			//difficulties
			static const MinecraftTypes::Byte DIFF_PEACEFULL;
			static const MinecraftTypes::Byte DIFF_EASY;
			static const MinecraftTypes::Byte DIFF_NORMAl;
			static const MinecraftTypes::Byte DIFF_HARD;
		};
	}
}

#endif // ! _CLIENT_SETTINGS_PACKET

