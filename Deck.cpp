#include "Deck.h"



Deck::Deck() {
	std::cout << "default constructor for deck\n";
}
//Deck::Deck(std::istream& input, const CardFactory* factory) {
//	std::cout << "constructeur avec deux args";
//}

Deck::Deck(Deck& d) {
	std::cout << "Deck copy constructor for deck\n";
	for (Card* card : d) {
		push_back(card);
	}
}

Deck::~Deck() {
	std::cout << "destructing my deck\n";
}

Card* Deck::draw() {
	Card* cardUp{ back() };
	pop_back();
	return cardUp;
}

std::ostream& operator << (std::ostream& output, Deck deck) {
	output << "Cards present in the deck: \n";
	int i{ 0 };
	std::cout << "deck size: " << deck.size() << "\n";
	for (Card* item : deck) {
		item->print(output);
		output << " ";
		i++;
		if (i == 20) {
			output << "\n"; // print a table with 20 columns
			i = 0;
		}
	}
	output << "\n";
	return output;
}