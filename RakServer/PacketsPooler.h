#pragma once
#include <map>
#include <functional>
#include "FutureHandler.h"

class PacketsPooler
{
private:
	std::map<FutureHandler*, std::function<void(FutureHandler*)>> _handlers;
public:
	std::map<FutureHandler*, std::function<void(FutureHandler*)>>* getHandlers()
	{
		return &_handlers;
	};

	void addFutureHandler(FutureHandler* hndl, std::function<void(FutureHandler*)> f){
		_handlers.insert(std::pair<FutureHandler*, std::function<void(FutureHandler*)>>(hndl, f));
	};

	void invokeFutureHandler(ConnectedClient* c, char packet){
		for (std::map<FutureHandler*, std::function<void(FutureHandler*)>>::iterator ii = this->_handlers.begin(); ii != this->_handlers.end(); ++ii)
		{
			if ((*ii).first->verify(c, packet))
			{
				(*ii).second((*ii).first);
				_handlers.erase((*ii).first);
				break;
			}
		}
	};

	PacketsPooler();
	~PacketsPooler();
};

