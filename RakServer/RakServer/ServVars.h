#pragma once
#include "Server.h"
#include "Client.h"
#include "DatabaseWorker.h"

static Server* mainServer;
static Client* poolerClient;
static Worker* physicsWorker;
static DatabaseWorker* databaseWorker;
