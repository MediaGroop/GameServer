#pragma once
#include "stdafx.h"
#include "easylogging++.h"

void onFailConnect(RakNet::Packet* p)
{
	LOG(INFO) << "Database worker is NOT ready!";

};