#pragma once
#include "Stateable.h"

class StateProcessor
{
public:
	StateProcessor();
	
	virtual ~StateProcessor();

	//processing stateable's object, if it's in exact state, else left it. 
	virtual bool process(Stateable* s){ return true; };
};

