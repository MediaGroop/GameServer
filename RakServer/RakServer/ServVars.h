#pragma once
#include "Server.h"
#include "Client.h"
#include "Worker.h"
#include "World.h"

extern Server* mainServer;
extern Client* poolerClient;
extern Worker* physicsWorker;
extern Worker* databaseWorker;
extern std::map<int, World> worlds;