#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>
#include "Card.h"
#include "CardFactory.h"
#include "Chain_Base.h"



// PLEASE KEEP COMMENTS FOR NOW, ILL REMOVE THEN ONCE ETH IS DONE

/// <summary>
/// The Chain class that keeps a list of all bean cards a player has
/// </summary>
/// <typeparam name="T">T should be one of the derived class that inherits from Card</typeparam>


template <class T> class Chain : public Chain_Base {
	std::vector<Card*> list;  // keeps track of the bean cards       // those two attributes might go to the interface
	char typeCards[10]; // keeps track of the type of cards chain is holding



public:
	// I am adding a default constructor, not so sure about it, might get deleted

	/// <summary>
	/// A default Chain constructor that initialized the "typeCards" instance variable by extracting it from the typeid of the generic parameter T
	/// </summary>
	

	Chain() {
		//std::cout << "In the Chain constructor: ";
		//std::cout << list.size() << "\n";
		std::string s = typeid(T).name();
		//std::cout << "The s is : " << s << "\n";
		int size{ static_cast<int>(s.size()) };
		//std::cout << "the matches are: " << matches[0] << " \n";
		strcpy_s(typeCards, sizeof(typeCards), s.substr(6,size-6).c_str());
		//std::cout << "The type is: " << typeCards << "\n";
	}

	/// <summary>
	/// A constructor that takes input from a file and reconstructs the chain from the file: example of line on the file: Red R R R R
	/// </summary>
	/// <param name="input">The file input stream from where we are reading out chain</param>
	/// <param name="factory">Object that has the responsability to build cards</param>
	
	Chain(std::istream& input, const CardFactory* factory);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="ch">Chain to copy attributes from</param>
	
	Chain(const Chain& ch) {
		// std::cout << "une recopie se fait";

		strcpy_s(typeCards, sizeof(typeCards),ch.typeCards);// copy the type of cards
		for (Card* item : ch.list) {
			list.push_back(item); // fill vector
		}
	}


	~Chain() {
		//delete typeCards;
		//std::cout << "I am the chain destructor\n";
		//delete typeCards;
	}


	/// <summary>
	/// This redefinition of += adds a new card to a chain
	/// </summary>
	/// <param name="Card"> Card to be added to the chain</param>
	/// <returns>Reference to the newly constructed chain</returns>
	Chain<T>& operator+=(Card*);

	/// <summary>
	/// Member function that calculates the amount of money a player would be given if he ever decided to sell his chain in a trade
	/// </summary>
	/// <returns>Amount of money given to the seller after a card trade </returns>
	int sell();

	/// <summary>
	/// Friend fucntion to print a chain on an output stream, e.g: Red R R R 
	/// </summary>
	/// <param name="output">output stream where the printing would be done on</param>
	/// <param name="ch">Chain to print</param>
	/// <returns>a reference to the output stream where the printing took place</returns>
	/// 
	friend std::ostream& operator << (std::ostream& output, Chain<T> ch) {
		// ch is copied by value here, copy constructor used
		// output << "Elements de la liste vector: \n";
		output << ch.typeCards << "\t";// maybe three tabs
		//std::cout << "The size of chain is: " << ch.list.size()<< "\n";

		for (int i{ 0 }; i < ch.list.size(); i++) {
			(*(ch.list.at(i))).print(output);
			output << " ";
			//output << "type of element in vector: " << typeid(*(ch.list.at(i))).name();
		}
		output << "\n";
		return output;
	}


	/// <summary>
	/// Method to get the number of cards in a given chain
	/// </summary>
	/// <returns>Number of cards in a given chain</returns>
	int getLengthChain();

	/// <summary>
	/// TODO
	/// </summary>
	/// <param name="output"></param>
	void print(std::ostream& output) const {
		output << *this;
	}


	const char* getChainType() const {
		return typeCards;
	}
};

template <class T> Chain<T>::Chain(std::istream& input, const CardFactory* factory) {
	std::string typeOfCard{}; // Rethink using string here

	//if (input.is_open()) {
		std::getline(input, typeOfCard, '\t');
		bool ok{ true };
		char card{ 'X' };

		if ((typeOfCard != "Blue") && (typeOfCard != "Chili") && (typeOfCard != "Stink") && (typeOfCard != "Green") && (typeOfCard != "soy")
			&& (typeOfCard != "black") && (typeOfCard != "Red") && (typeOfCard != "garden")) {
			ok = false; // corrupted file
		}

		//std::cout << "generating the chaine:  ";

		// UPDATE THIS TODO, also, if card is a line break, stop parsing

		if (ok) {
			while (input >> card) {
				/*std::cout << card;
				std::cout << " ";*/
				Card* redCard = factory->getRed();
				list.push_back(redCard);
			}
		}
	//}
	//else {
		//std::cout << "ouverture impossible \n";
	//}

}

template <class T> Chain<T>& Chain<T>::operator+=(Card* cardToAdd) {
	//if (this == nullptr) {
	//	// we need to create the chain first
	//	this = new Chain<(typeid(*cardToAdd))>();
	//}// TODO, do not call this method if you know this is gonna be nullptr, delegate this check to another function before doing this
	try {
		if (typeid(*cardToAdd).name() != typeid(T).name()) {
			throw "IllegalType Exception when trying to add a card to a chain";
		}
		list.push_back(cardToAdd);
		return *this;
	}
	catch (const char* exception) {
		std::cout << "trying to add the following card: " << cardToAdd->getName() << " to\n";
		std::cout << *this;
		std::cerr << "Error: " << exception << "\n";
	}
}

template <class T> int Chain<T>::sell(){
	int sizeOfChain { static_cast <int>(list.size()) };

	//std::cout << "\nThe size of chain in the sell method is: " << sizeOfChain;

	// assuming the list is non empty
	int maxCoins{ 4 };
	int requiredCards{}; // cards returned by Card::getCardsPerCoin(int coins)
	int moneyToEarn{}; // amount given to a seller after a trade
	int similarCards{}; // on each iteration, we divide the size of a chain by the number of required cards, the division gives us the parts of cards that have similar numbers, so we count the 
	// money for both parts, and we continue further iterations using the rest of this division (cards that didnt match the amount of required cards we need)
	int restOfCards{};


	while (maxCoins >= 1) {
		requiredCards = (*(list.at(0))).getCardsPerCoin(maxCoins);
		restOfCards = sizeOfChain % requiredCards;
		similarCards = sizeOfChain / requiredCards;
		moneyToEarn += (maxCoins * similarCards);
		sizeOfChain = restOfCards;
		maxCoins--;

		if (sizeOfChain == 0) {
			break;
		}
	}
	return moneyToEarn;
}


/// <summary>
/// Method to get the number of cards in a given chain
/// </summary>
/// <returns>Number of cards in a given chain</returns>
template <class T> int Chain<T>::getLengthChain() {
	return list.size();
}


