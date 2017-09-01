#include "ClientSettingsPacket.h"

using namespace Packets;
using namespace ClientPackets;
using namespace NetworkEngine;
using namespace ServiceTypes;

const MinecraftTypes::VarInt ClientSettingsPacket::_ID(0x15);

//chat flags
const MinecraftTypes::Byte ClientSettingsPacket::CHAT_ENABLED = 0;
const MinecraftTypes::Byte ClientSettingsPacket::CHAT_COMMANDS_ONLY = 1;
const MinecraftTypes::Byte ClientSettingsPacket::CHAT_HIDDEN = 2;
//difficulties
const MinecraftTypes::Byte ClientSettingsPacket::DIFF_PEACEFULL = 0;
const MinecraftTypes::Byte ClientSettingsPacket::DIFF_EASY = 1;
const MinecraftTypes::Byte ClientSettingsPacket::DIFF_NORMAl = 2;
const MinecraftTypes::Byte ClientSettingsPacket::DIFF_HARD = 3;

ClientSettingsPacket::ClientSettingsPacket(const char* locale, MinecraftTypes::Byte viewDistance, MinecraftTypes::Byte chatFlags,
	MinecraftTypes::Boolean chatColors, MinecraftTypes::Byte difficulty, MinecraftTypes::Boolean showCape) :
	_locale(locale),
	_viewDistance(viewDistance),
	_chatFlags(chatFlags),
	_chatColors(chatColors),
	_difficulty(difficulty),
	_showCape(showCape)
{}

ClientSettingsPacket::ClientSettingsPacket(const ClientSettingsPacket& pack):
	_locale(pack._locale),
	_viewDistance(pack._viewDistance),
	_chatFlags(pack._chatFlags),
	_chatColors(pack._chatColors),
	_difficulty(pack._difficulty),
	_showCape(pack._showCape)
{}

ClientSettingsPacket::~ClientSettingsPacket()
{}

//selectors-modifiers
MinecraftTypes::String& ClientSettingsPacket::locale()
{
	return _locale;
}

MinecraftTypes::Byte& ClientSettingsPacket::viewDistance()
{
	return _viewDistance;
}

MinecraftTypes::Byte& ClientSettingsPacket::chatFlags()
{
	return _chatFlags;
}

MinecraftTypes::Boolean& ClientSettingsPacket::chatColors()
{
	return _chatColors;
}

MinecraftTypes::Byte& ClientSettingsPacket::difficulty()
{
	return _difficulty;
}

MinecraftTypes::Boolean& ClientSettingsPacket::showCape()
{
	return _showCape;
}

//Packet interface methods
Packet* ClientSettingsPacket::clone()
{
	return new ClientSettingsPacket(*this);
}

void ClientSettingsPacket::load(const Buffer& buff)
{
	_locale = buff.readString();
	buff.readData(&_viewDistance, sizeof(_viewDistance));
	buff.readData(&_chatFlags, sizeof(_chatFlags));
	buff.readData(&_chatColors, sizeof(_chatColors));
	buff.readData(&_difficulty, sizeof(_difficulty));
	buff.readData(&_showCape, sizeof(_showCape));
}

Buffer ClientSettingsPacket::dump()
{
	Buffer b;
	_ID.write(b);
	b.writeString(_locale);
	b.writeData(&_viewDistance, sizeof(_viewDistance));
	b.writeData(&_chatFlags, sizeof(_chatFlags));
	b.writeData(&_chatColors, sizeof(_chatColors));
	b.writeData(&_difficulty, sizeof(_difficulty));
	b.writeData(&_showCape, sizeof(_showCape));
	return b;
}

void ClientSettingsPacket::handle(NetworkEngine::BufferedReaderWriter&)
{
	process();
}

long ClientSettingsPacket::getID()
{
	return _ID._val;
}