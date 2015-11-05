#pragma once
#include "Server.h"
#include "Client.h"
#include "Worker.h"
#include "World.h"
#include "PacketsPooler.h"

extern Server* mainServer;
extern Client* poolerClient;
extern Worker* physicsWorker;
extern Worker* databaseWorker;
extern Worker* syncWorker;
extern std::map<int, World> worlds;
extern PacketsPooler* pPooler;