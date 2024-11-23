#include "TradeArea.h"

// HOW TO DIFFER BETWEEN A DECK AND A TRADE AREA WHEN WE PRINT THEM

TradeArea::TradeArea(std::istream& input, const CardFactory* factory) {
	long sizeFile = input.tellg() ;// get the size of the input
	input.seekg(0, std::ios::beg);// place the pointer at the beg of the file
	char* tab = new char[sizeFile];// tab should be of length sizeFile
	input.read(tab, sizeFile);// read from input and transfer to tab
	int i{ 0 };
	while (i < sizeFile) {
		if (tab[i] != ' ') {
			if (tab[i] == 'R') {
				//std::cout << tab[i];
				container.push_back(factory->getRed());
			}
			else if (tab[i] == 'B') {
				container.push_back(factory->getBlue());
			}
			else if (tab[i] == 'C') {
				container.push_back(factory->getChili());
			}
			else if (tab[i] == 'S') {
				container.push_back(factory->getStink());
			}
			else if (tab[i] == 'G') {
				container.push_back(factory->getGreen());
			}
			else if (tab[i] == 's') {
				container.push_back(factory->getSoy());
			}
			else if (tab[i] == 'b') {
				container.push_back(factory->getBlack());
			}
			else if (tab[i] == 'g') {
				container.push_back(factory->getGarden());
			}
		}
		i++;
	}
	delete[] tab;
}


/// <summary>
/// This method adds a card to the trade area, but it doesn't verify if it's legal to do so
/// </summary>
/// <param name="cardToAdd">The card that should be added to the trade area</param>
/// <returns>A reference to the tradearea newly updated</returns>
TradeArea& TradeArea::operator+=(Card* const cardToAdd) {
	container.push_back(cardToAdd);
	return *this;
}


/// <summary>
/// This method checks if a card can be legally added to the trade area; i.e: a card of the same bean is 
/// already present in the trade area
/// </summary>
/// <param name="cardToAdd">The card that the player wants to add</param>
/// <returns>True if legal, false if not</returns>
bool TradeArea::legal(const Card* const cardToAdd) {
	std::string nameToAdd{ cardToAdd->getName() };
	std::list<Card*>::const_iterator it{ container.cbegin() };
	bool res{ false };// this boolean variable tracks down whether a card of the same bean is already present in the container or not
	while (it != container.cend()) {
		std::cout << "The card is: " << (**it).getName() << "\n";
		if ((**it).getName() == nameToAdd) {
			res = true;
			break;
		}
		it++;
	}
	return res;
}


/// <summary>
/// This method removes a card with the type cardType from the trade area
/// </summary>
/// <param name="cardType">Type of card to be deleted</param>
/// <returns>A pointer to the newly deleted card</returns>
Card* TradeArea::trade(const std::string cardType) {
	std::list<Card*>::const_iterator it{ container.cbegin() };
	Card* cardErased{};
	while (it != container.cend()) {
		if ((**it).getName() == cardType) {
			cardErased = (*it);
			container.erase(it);
			break;
		}
	}
	return cardErased;
}


/// <summary>
/// This method computes the total number of cards currently in the trade area
/// </summary>
/// <returns>The number of cards in the trade area</returns>
int TradeArea::numCards() {
	return container.size();
}


/// <summary>
/// This method prints the content of the trade area on an output file or stream e.g: R g s
/// </summary>
/// <param name="output">The file or the stream where elements are going to be printed</param>
/// <param name="trade">The tradeArea object to print</param>
/// <returns>A reference to the file or the stream that we used to write on</returns>
std::ostream& operator << (std::ostream& output, TradeArea trade) {
	int i = 1;
	for (Card* card : trade.container) {
		card->print(output);
		output << " ";
		i++;
		if (i == 20) {
			output << "\n"; // print at max 20 columns?
			i = 1;
		}
	}
	output << "\n";
	return output;
}



