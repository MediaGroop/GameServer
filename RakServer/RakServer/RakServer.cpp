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
//Handlers
//Server
//Pooler client

#define ELPP_STL_LOGGING
#define ELPP_PERFORMANCE_MICROSECONDS
#define ELPP_LOG_STD_ARRAY
#define ELPP_LOG_UNORDERED_MAP
#define ELPP_UNORDERED_SET
#define ELPP_THREAD_SAFE

//Handlers
//Server
#include "ServerConnectHandler.h"
//Client
#include "PoolerClientConnectHandler.h"

INITIALIZE_EASYLOGGINGPP

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
	char str[1];
	setupLog();
	
	ConfigLoader::init("config.ini");
	
	//Server init
	NetworkListener listen;
	listen.add((short)ID_NEW_INCOMING_CONNECTION, handleconn); // Server conenct handler
	Server srv(&listen);
	
	mainServer = &srv;
	std::thread trd(mainServer->startMainNetworkThread, mainServer, ConfigLoader::getIntVal("Network-ServerPort"), ConfigLoader::getIntVal("Network-MaxPlayers"));
	mainServer->networkTrd = &trd;
	//Server end

	//Client init
	NetworkListener clientListen;
	clientListen.add((short)ID_CONNECTION_REQUEST_ACCEPTED, registerServer); // PoolerClientConnectHandler.h

	Client clnt(&clientListen);

	poolerClient = &clnt;
	poolerClient->connect(ConfigLoader::getVal("Network-PoolerAddress"), ConfigLoader::getIntVal("Network-PoolerPort"));
	//Client end

	//TODO: start command reader loop
	cin >> str;//Just for blocking

	poolerClient->running = false;
	poolerClient->networkTrd->join();

	mainServer->networkRunning = false;
	mainServer->networkTrd->join();

	return 0;
}

