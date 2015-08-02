#pragma once
#include "stdafx.h"
#include "ServVars.h"
#include "VerifyPacket.h"

//
// Verification map:
//    
//    Client => Game Server(Pooler client)
//       /\                      ||
//       ||                      \/                                          
//       ||                 Pooler server ==> [check] ==> Pooler Server===\
//		 ||														   		 ||
//		 ||																 \/
//		 \====================================================Game Server(Pooler client)
void handleVerify(RakNet::Packet *packet){
	ConnectedClient* cc = mainServer->getClient(packet->guid);
	if (cc != nullptr){
		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		RakNet::RakString acc, hash;
		unsigned char data[20];

		RakNet::StringCompressor::Instance()->DecodeString(&acc, 256, &bsIn);
		bsIn.Read(data);
		hash = RakNet::RakString(reinterpret_cast<char*>(data));
		
		LOG(INFO) << "Verification request for:";
		LOG(INFO) << acc.C_String();
		
		//Chain client with session hash
		cc->hash = hash;

		VerifyPacket p(acc, hash);
		p.send(poolerClient->peer, poolerClient->serverAddress);

		LOG(INFO) << "Verifying...";
	}
};
