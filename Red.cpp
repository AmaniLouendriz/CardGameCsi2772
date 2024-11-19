#include "Red.h"
#include "Card.h"

// THIS IS JUST TEMPORARY, I USED IT TO TEST MY CODE
// YOU CAN UPDATE IT WITH YOUR CURRENT CHANGES

Red::Red() : Card() {
	//std::cout << "I am the constructor of Red \n";
}

int Red::getCardsPerCoin(int coins) {
	if (coins == 4) {
		return 5;
	}
	else if (coins == 3) {
		return 4;
	}
	else if (coins == 2) {
		return 3;
	} 
	else if (coins == 1) {
		return 2;
	}
	return 0;
}

