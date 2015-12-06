// RakServer.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "easylogging++.h"
#include "FileManager.h"
#include <thread>
#include "NetworkListener.h"
#include "AuthPoolerPacket.h"
#include "ConfigLoader.h"
#include "Server.h"
#include "Client.h"
#include "PacketTypes.h"
#include "PhysicsWorker.h"
#include "DatabaseWorker.h"
#include "SyncWorker.h"
#include "CharacterSelectHandler.h"

#define ELPP_STL_LOGGING
#define ELPP_PERFORMANCE_MICROSECONDS
#define ELPP_LOG_STD_ARRAY
#define ELPP_LOG_UNORDERED_MAP
#define ELPP_UNORDERED_SET
#define ELPP_THREAD_SAFE
#define ELPP_EXPERIMENTAL_ASYNC 

//Handlers
//Server
#include "ServerConnectHandler.h"
#include "GameServerDisconnectHandler.h"
#include "VerificationHandler.h"

//Client
#include "PoolerClientConnectHandler.h"
#include "VerifyResponseHandler.h"
#include "ConnToAuthFailHandler.h"

INITIALIZE_EASYLOGGINGPP

//Extern vars
Server* mainServer;
Client* poolerClient;
Worker* physicsWorker;
Worker* databaseWorker;
Worker* syncWorker;
std::map<int, World> worlds;
PacketsPooler* pPooler;

//Configuring easyLogging
void setupLog(){
	time_t t;
	t = time(0);
	char str[64];

	getcwd(str, 64);
	if (!FileManager::DirExists(strcat(str, "\\logs\\"))){
		mkdir(str);
	}

	std::string log_name = "logs\\";
	log_name.append(asctime(localtime(&t)));
	log_name[log_name.length() - 1] = ' ';
	log_name.append(".txt");

	for (int i = 0; i < log_name.length(); ++i)
	{
		if (log_name[i] == ':' || log_name[i] == ' ' || log_name[i] == '\r')
		{
			log_name[i] = '_';
		}
	}

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, log_name);
}


//Entry point
//Configure log
//Read config file
int main(int argc, const char** argv)
{
	Entity::registerClasses();
	char str[1];
	setupLog();

	ConfigLoader::init("config.ini");

	physicsWorker = new PhysicsWorker(new RakNet::RPC4());
	databaseWorker = new DatabaseWorker(new RakNet::RPC4());
	syncWorker = new SyncWorker(new RakNet::RPC4());
	pPooler = new PacketsPooler();

	//Server init	
	NetworkListener *listen = new NetworkListener();
	listen->add((short)ID_NEW_INCOMING_CONNECTION, handleconn); // Server conenct handler
	listen->add((short)ID_CONNECTION_LOST, handledisconn); // Server disconnect handler
	listen->add((short)VERIFY_ACCOUNT, handleVerify); // Server data verification handler
	listen->add((short)SELECT_CHARACTER, handleCharSelect); // Character choose handler

	mainServer = new Server(listen);

	mainServer->setThread(new std::thread(mainServer->startMainNetworkThread, mainServer, ConfigLoader::getIntVal("Network-ServerPort"), ConfigLoader::getIntVal("Network-MaxPlayers")));
	//Server end

	//Client init
	NetworkListener* clientListen = new NetworkListener();
	clientListen->add((short)ID_CONNECTION_REQUEST_ACCEPTED, registerServer); // PoolerClientConnectHandler.h
	clientListen->add((short)VERIFY_RESPONSE, verifyResultHandler); // VerifyResponseHandler.h
	clientListen->add((short)ID_CONNECTION_ATTEMPT_FAILED, authConnFail); // ConnToAuthFailHandler.h

	poolerClient = new Client(clientListen);
	poolerClient->connect(ConfigLoader::getVal("Network-PoolerAddress"), ConfigLoader::getIntVal("Network-PoolerPort"));
	//Client end

	physicsWorker->start(ConfigLoader::getVal("PhysicsWorker-Address"), ConfigLoader::getIntVal("PhysicsWorker-Port"));
	databaseWorker->start(ConfigLoader::getVal("DatabaseWorker-Address"), ConfigLoader::getIntVal("DatabaseWorker-Port"));
	syncWorker->start(ConfigLoader::getVal("SyncWorker-Address"), ConfigLoader::getIntVal("SyncWorker-Port"));

	//TODO: start command reader loop
	cin >> str;//Just for blocking

	poolerClient->setRunning(false);
	poolerClient->getThread()->join();

	mainServer->setRunning(false);
	mainServer->getThread()->join();

	//Cleaning 
	//delete pPooler;
	//delete databaseWorker;
	//delete physicsWorker;
	//delete syncWorker;

	return 0;
}

