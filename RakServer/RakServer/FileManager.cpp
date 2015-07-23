#include "FileManager.h"
#include "easylogging++.h"
#include "stdafx.h"
#include <io.h>
#include <string>

using namespace std;

bool FileManager::fileExists(std::string path)
{
	return access(path.c_str(), 0) != -1;
}

bool FileManager::DirExists(const char * fname){
	if (fname == NULL || _tcslen(fname) == 0)
	{
		return false;
	}
	DWORD dwAttrs = ::GetFileAttributes(fname);
	if (dwAttrs == DWORD(-1))
	{
		DWORD dLastError = GetLastError();
		if (ERROR_TOO_MANY_NAMES == dLastError
			|| ERROR_SHARING_VIOLATION == dLastError
			|| ERROR_TOO_MANY_SESS == dLastError
			|| ERROR_SHARING_BUFFER_EXCEEDED == dLastError)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
void FileManager::createFile(std::string fname)
{
	ofstream ofs(fname);
	ofs.close();
}