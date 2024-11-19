#pragma once
#include "iostream"


// THIS IS JUST TEMPORARY, I USED IT TO TEST MY CODE
// YOU CAN UPDATE IT WITH YOUR CURRENT CHANGES

class Card {
public:
	Card() {
		//std::cout << "I am the Card constructor\n";
	}

	virtual int getCardsPerCoin(int coins) = 0;

	virtual void print(std::ostream& out) = 0;

};
