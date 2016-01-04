#pragma once
#include "stdafx.h"

enum PWorkerPackets{
	CREATE_WORLD_P = ID_USER_PACKET_ENUM + 1,
	UPDATE_ENTITY_P = CREATE_WORLD_P + 1,
	ADD_ENTITY_P = UPDATE_ENTITY_P + 1,
	REMOVE_ENTITY_P = ADD_ENTITY_P + 1
};