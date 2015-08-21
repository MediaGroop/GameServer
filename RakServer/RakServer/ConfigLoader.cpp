#include "ConfigLoader.h"
#include "easylogging++.h"

//Creates default configuration file on given location(path is local!)
void ConfigLoader::createDefault(std::string path){
	static char str[64];
	getcwd(str, 64);
	strcat(str, "\\");
	strcat(str, path.c_str());

	FileManager::createFile(str);

	minIni ini(path);

	ini.put("Network", "ServerPort", "67534");
	ini.put("Network", "PoolerPort", "66534");
	ini.put("Network", "PoolerAddress", "127.0.0.1");
	ini.put("Network", "PoolerKey", "topsecret");
	ini.put("Network", "ShardName", "Generic");
	ini.put("Network", "MaxPlayers", "1000");
	ini.put("Network", "ServerId", "1");

	ini.put("Database", "Name", "game");
	ini.put("Database", "Login", "root");
	ini.put("Database", "Password", "root");
	ini.put("Database", "Host", "localhost");
	ini.put("Database", "Port", "3306");
	
	ini.put("PhysicsWorker", "Address", "127.0.0.1");
	ini.put("PhysicsWorker", "Port", "62656");

	ini.put("DatabaseWorker", "Address", "127.0.0.1");
	ini.put("DatabaseWorker", "Port", "62657");

}
//Returns config val (key must be like Section-Variable)
std::string ConfigLoader::getVal(std::string key)
{
	for (map<string, string>::iterator ii = ConfigLoader::getInstance()._vals.begin(); ii != ConfigLoader::getInstance()._vals.end(); ++ii)
	{
		if ((*ii).first == key) {
			return (*ii).second;
		}
	}
	LOG(ERROR) << "There's no value with given name!";
	return "0";
}
//Returns config val, converted to int(Use only when you exactly know var type!)
int ConfigLoader::getIntVal(std::string key)
{
	return atoi((getVal(key)).c_str());
}

//loads config vals from given file(Path is local)
void ConfigLoader::init(std::string path){
	if (FileManager::fileExists(path)){
		minIni ini(path);
		string s, section;
		for (int is = 0; section = ini.getsection(is), section.length() > 0; is++) {
			for (int ik = 0; s = ini.getkey(section, ik), s.length() > 0; ik++) {
				ConfigLoader::getInstance()._vals.insert(pair<string, string>(section + "-" + s, ini.gets(section, s)));
				//LOG(INFO) << section + "-" + s + " " + ini.gets(section, s);
			}
		}
	}
	else
	{
		ConfigLoader::createDefault(path);
		ConfigLoader::init(path);
	}
}