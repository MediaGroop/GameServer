#pragma once
#include "Stateable.h"
class Signal;

class Avatar :
	public Stateable
{
public:
	Avatar();
	virtual ~Avatar();
	virtual void signal(Signal* s){};
};

