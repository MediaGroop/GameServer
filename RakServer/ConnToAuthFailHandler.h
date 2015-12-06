#pragma once
#include "stdafx.h"
#include "easylogging++.h"

void authConnFail(RakNet::Packet* p)
{
	LOG(INFO) << "Authorization server is OFFLINE!";
};