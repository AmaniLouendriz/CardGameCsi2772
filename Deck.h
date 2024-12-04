#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Card.h"
#include "CardFactory.h"

class CardFactory;

class Deck : public std::vector<Card*>{
public:
	/// <summary>
	/// Default deck constructor
	/// </summary>
	Deck() {
	}


	/// <summary>
	/// Copy constructor for the deck
	/// </summary>
	/// <param name="d">Deck to copy into the new deck</param>
	Deck(const Deck& d);


	/// <summary>
	/// A constructor with two parameters that is responsible to construct a deck from a given input file, used when reloading the game from a file
	/// </summary>
	/// <param name="input">Input file with all the cards e.g: R B C S g</param>
	/// <param name="factory">Object responsible of creating, deleting and keeping track of cards, according to the factory pattern</param>
	Deck(std::istream& input, const CardFactory* factory);


	/// <summary>
	/// Deck destructor
	/// </summary>
	~Deck();


	/// <summary>
	/// This method deletes the last card on the deck container
	/// </summary>
	/// <returns>Card deleted</returns>
	Card* draw();


	/// <summary>
	/// This method prints all the cards present in the deck on the output stream
	/// </summary>
	/// <param name="output">File or stream on which to print the content of the deck</param>
	/// <param name="deck">The actual deck to print</param>
	/// <returns>The stream where the writing took place</returns>
	friend std::ostream& operator << (std::ostream& output, Deck deck);
};