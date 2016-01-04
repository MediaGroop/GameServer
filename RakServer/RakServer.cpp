// RakServer.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "FileManager.h"
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
#include <stdio.h>  /* defines FILENAME_MAX */

#if defined(_WIN64) || defined(_WIN32)
#include <thread>
#else
#include <pthread.h>
#endif

#define ELPP_THREAD_SAFE
#define ELPP_STACKTRACE_ON_CRASH
#define ELPP_DEBUG_ERRORS
#define ELPP_FORCE_USE_STD_THREAD

#include "easylogging++.h"

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
	char str[FILENAME_MAX];

	getcwd(str, sizeof(str));
	if (!FileManager::DirExists(strcat(str, "//logs//"))){
		mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	std::string log_name = "//logs//";
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
	setupLog();
	LOG(INFO) << "Log is ready!";
	ConfigLoader::init("config.ini");
	LOG(INFO) << "Config is loaded!";
	
	physicsWorker = new PhysicsWorker();
	databaseWorker = new DatabaseWorker();
	syncWorker = new SyncWorker();
	pPooler = new PacketsPooler();
	
	LOG(INFO) << "Setting up a server...";

	//Server init	
	NetworkListener *listen = new NetworkListener();
	listen->add((short)ID_NEW_INCOMING_CONNECTION, handleconn); // Server conenct handler
	listen->add((short)ID_CONNECTION_LOST, handledisconn); // Server disconnect handler
	listen->add((short)VERIFY_ACCOUNT, handleVerify); // Server data verification handler
	listen->add((short)SELECT_CHARACTER, handleCharSelect); // Character choose handler

	mainServer = new Server(listen);
#if defined(_WIN64) && defined(_WIN32)
	mainServer->setThread(new std::thread(mainServer->startMainNetworkThread, mainServer, ConfigLoader::getIntVal("Network-ServerPort"), ConfigLoader::getIntVal("Network-MaxPlayers")));
#else
	pthread_t* trd = new pthread_t();
	server_data data;
	data.instance = mainServer;
	data.max_players = ConfigLoader::getIntVal("Network-MaxPlayers");
	data.port = ConfigLoader::getIntVal("Network-ServerPort");
	pthread_create(trd, NULL, &mainServer->startMainNetworkThread, (void *)&data);
	mainServer->setThread(trd);
#endif
	//Server end
	
	LOG(INFO) << "Setting up a pooler client...";

	//Client init
	NetworkListener* clientListen = new NetworkListener();
	clientListen->add((short)ID_CONNECTION_REQUEST_ACCEPTED, registerServer); // PoolerClientConnectHandler.h
	clientListen->add((short)VERIFY_RESPONSE, verifyResultHandler); // VerifyResponseHandler.h
	clientListen->add((short)ID_CONNECTION_ATTEMPT_FAILED, authConnFail); // ConnToAuthFailHandler.h

	poolerClient = new Client(clientListen);
	LOG(INFO) << "Connecting pooler client...";
	poolerClient->connect(ConfigLoader::getVal("Network-PoolerAddress").c_str(), ConfigLoader::getIntVal("Network-PoolerPort"));
	//Client end
	LOG(INFO) << "Starting workers...";

	physicsWorker->start(ConfigLoader::getVal("PhysicsWorker-Address").c_str(), ConfigLoader::getIntVal("PhysicsWorker-Port"));
	databaseWorker->start(ConfigLoader::getVal("DatabaseWorker-Address").c_str(), ConfigLoader::getIntVal("DatabaseWorker-Port"));
	syncWorker->start(ConfigLoader::getVal("SyncWorker-Address").c_str(), ConfigLoader::getIntVal("SyncWorker-Port"));

	LOG(INFO) << "Game Server instance is ready!";
	//TODO: start command reader loop
	while(true){}

	poolerClient->setRunning(false);
#if defined(_WIN64) || defined(_WIN32)
	poolerClient->getThread()->join();
#endif
	mainServer->setRunning(false);
	
#if defined(_WIN64) || defined(_WIN32)
	mainServer->getThread()->join();
#endif
	//Cleaning 
	//delete pPooler;
	//delete databaseWorker;
	//delete physicsWorker;
	//delete syncWorker;

	return 0;
}
