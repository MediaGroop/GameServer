#include "AuthPoolerPacket.h"
#include "PacketTypes.h"
#include "ConfigLoader.h"
#include "easylogging++.h"

AuthPoolerPacket::AuthPoolerPacket()
{
}


AuthPoolerPacket::~AuthPoolerPacket()
{
}

void AuthPoolerPacket::send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to){
	
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)AUTH_TO_POOLER);

	LOG(INFO) << "Writing pooler key, which is: " + ConfigLoader::getVal("Network-PoolerKey");

	//Retrieving our server info
	RakNet::RakString key(ConfigLoader::getVal("Network-PoolerKey").c_str());
	RakNet::RakString name(ConfigLoader::getVal("Network-ShardName").c_str());
	int id = ConfigLoader::getIntVal("Network-ServerId");
	//**************************

	//Writing info
	bsOut.Write(key);
	bsOut.Write(name);
	bsOut.Write(id);
	bsOut.Write(ConfigLoader::getIntVal("Network-ServerPort"));
	//****************

	by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);
};