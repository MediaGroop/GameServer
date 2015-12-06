#pragma once
#include "stdafx.h"
#include "VerifyPacket.h"
#include "ServVars.h"

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
	if (cc != nullptr)
	{
		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		RakNet::RakString acc;
		unsigned char hash[20];

		RakNet::StringCompressor::Instance()->DecodeString(&acc, 256, &bsIn);
		
		for (int i = 0; i < 20; ++i)
			bsIn.Read(hash[i]);

		LOG(INFO) << "Verification request for:";
		LOG(INFO) << acc.C_String();

		//Chain client with session hash
		cc->setHash(hash);

		VerifyPacket p(acc, hash);
		p.send(poolerClient->getPeer(), *poolerClient->getServerAddr());

		LOG(INFO) << "Verifying...";
	}
	else
	{
		LOG(INFO) << "No client!"; // must never reach this!
	}
};
