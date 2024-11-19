#pragma once
#include <iostream>
#include "Card.h"

// THIS IS JUST TEMPORARY, I USED IT TO TEST MY CODE
// YOU CAN UPDATE IT WITH YOUR CURRENT CHANGES

class Red : public Card {
public:
	Red();

	void print(std::ostream& out) {
		out << 'R';
	}

	int getCardsPerCoin(int coins);
};