#pragma once
#include "stdafx.h"
#include "Packet.h"

class AuthPoolerPacket :
	public Packet
{
public:
	AuthPoolerPacket();
	~AuthPoolerPacket();
    virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};

