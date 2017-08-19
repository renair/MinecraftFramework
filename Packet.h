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
		virtual void process();
		virtual long getID() = 0;
	};
}
#endif