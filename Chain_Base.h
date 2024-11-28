#pragma once
#include <iostream>
#include "CardFactory.h"

class Chain_Base {
public:
	//Chain_Base() {}
	//virtual Chain_Base(std::istream& input, const CardFactory* factory);
	virtual int sell() = 0;
	virtual int getLengthChain() = 0;
	virtual void print(std::ostream& output) const = 0;

	virtual const char* getChainType() const = 0;

	virtual Chain_Base& operator+=(Card*) = 0;

};