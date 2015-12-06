#pragma once
class Stateable
{
private:
	char _state;
public:

	void setState(char c){
		_state = c;
	};

	char getState()
	{
		return _state;
	}

	Stateable();

	Stateable(char c) : _state(c) {	};

	virtual ~Stateable();
};

