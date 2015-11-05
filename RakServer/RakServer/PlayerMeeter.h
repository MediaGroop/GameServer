#pragma once
#include "StateProcessor.h"
#include "ConnectedClient.h"

class PlayerMeeter: public StateProcessor
{
public:
	static PlayerMeeter& getInstance()
	{
		static PlayerMeeter    instance; 
		return instance;
	}

	virtual bool process(Stateable* s) override;
	bool process(ConnectedClient* c);

private:
	PlayerMeeter();
	~PlayerMeeter();
	PlayerMeeter(PlayerMeeter const&);
	void operator=(PlayerMeeter const&);
	PlayerMeeter(PlayerMeeter const&) = delete;
	void operator=(PlayerMeeter const&) = delete;
};

