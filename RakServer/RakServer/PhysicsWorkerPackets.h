#pragma once
#include "stdafx.h"

enum PWorkerPackets{
	CREATE_WORLD = ID_USER_PACKET_ENUM + 1,
	UPDATE_ENTITY = CREATE_WORLD + 1,
	ADD_ENTITY = UPDATE_ENTITY + 1,
	REMOVE_ENTITY = ADD_ENTITY + 1
};