#pragma once
#include "stdafx.h"
#include "easylogging++.h"

void onFailPhyConnect(RakNet::Packet* p)
{
	LOG(INFO) << "Physics worker is NOT ready!";

};