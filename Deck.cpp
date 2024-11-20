#include "Deck.h"




//Deck::Deck(std::istream& input, const CardFactory* factory) {
//	std::cout << "constructeur avec deux args";
//}

class CardFactory;

Deck::Deck(const Deck& d) {
	std::cout << "Deck copy constructor for deck\n";
	for (Card* card : d) {
		push_back(card);
	}
}

Deck::Deck(std::istream& input, const CardFactory* factory) {
	long size = input.tellg();
	//std::cout << "The size is: " << size << "\n";
	input.seekg(0, std::ios::beg);
	char* tab = new char[size];
	input.read(tab, size);
	int i{ 0 };
	while (i < size) {
		if (tab[i] != ' ') {
			//std::cout << tab[i];
			if (tab[i] == 'R') {
				//std::cout << tab[i];
				push_back(factory->getRed());
			}
			else if (tab[i] == 'B') {
				push_back(factory->getBlue());
			}
			else if (tab[i] == 'C') {
				push_back(factory->getChili());
			}
			else if (tab[i] == 'S') {
				push_back(factory->getStink());
			}
			else if (tab[i] == 'G') {
				push_back(factory->getGreen());
			}
			else if (tab[i] == 's') {
				push_back(factory->getSoy());
			}
			else if (tab[i] == 'b') {
				push_back(factory->getBlack());
			}
			else if (tab[i] == 'g') {
				push_back(factory->getGarden());
			}
		}
		i++;
	}

	delete[] tab;
}

Deck::~Deck() {
	std::cout << "\ndestructing my deck\n";
}

Card* Deck::draw() {
	Card* cardUp{ back() };
	pop_back();
	return cardUp;
}

std::ostream& operator << (std::ostream& output, Deck deck) {
	//output << "Cards present in the deck: \n";
	int i{ 0 };
	//std::cout << "deck size: " << deck.size() << "\n";
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


