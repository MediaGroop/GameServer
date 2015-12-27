#pragma once
#include "Stateable.h"

class Avatar :
	public Stateable
{
public:
	Avatar();
	virtual ~Avatar();
	virtual void signal(Signal* s){};
};

