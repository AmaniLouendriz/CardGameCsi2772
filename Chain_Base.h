#pragma once
#include <iostream>
#include "CardFactory.h"

/// <summary>
/// Interface that all chains derive from
/// </summary>
class Chain_Base {
public:
	virtual int sell() = 0;
	virtual int getLengthChain() = 0;
	virtual void print(std::ostream& output) const = 0;

	virtual const char* getChainType() const = 0;

	virtual Chain_Base& operator+=(Card*) = 0;

	virtual void emptyList() = 0;
	

};