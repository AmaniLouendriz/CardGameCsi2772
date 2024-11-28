#include "Deck.h"




class CardFactory;

/// <summary>
/// Copy constructor for the deck
/// </summary>
/// <param name="d">Deck to copy into the new deck</param>
Deck::Deck(const Deck& d) {
	//std::cout << "Deck copy constructor for deck\n";
	for (Card* card : d) {
		push_back(card);
	}
}


/// <summary>
/// A constructor with two parameters that is responsible to construct a deck from a given input file, used when reloading the game from a file
/// </summary>
/// <param name="input">Input file with all the cards e.g: R B C S g</param>
/// <param name="factory">Object responsible of creating, deleting and keeping track of cards, according to the factory pattern</param>
Deck::Deck(std::istream& input, const CardFactory* factory) {
	long size = input.tellg();// assuming the file pointer is at the end of file, using std::ios::ate
	//std::cout << "The size is: " << size << "\n";
	input.seekg(0, std::ios::beg);
	char* tab = new char[size];
	input.read(tab, size);
	int i{ 0 };
	// depending on the card symbol get the right card
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


/// <summary>
/// Deck destructor
/// </summary>
Deck::~Deck() {
	//std::cout << "\ndestructing my deck\n";
}


/// <summary>
/// This method deletes the last card on the deck container
/// </summary>
/// <returns>Card deleted</returns>
Card* Deck::draw() {
	Card* cardUp{ back() };
	pop_back();
	return cardUp;
}


/// <summary>
/// This method prints all the cards present in the deck on the output stream
/// </summary>
/// <param name="output">File or stream on which to print the content of the deck</param>
/// <param name="deck">The actual deck to print</param>
/// <returns>The stream where the writing took place</returns>
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


