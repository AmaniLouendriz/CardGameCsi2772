#pragma once
#include <iostream>
#include <list>
#include "Card.h"
#include "CardFactory.h"

class TradeArea {
	std::list<Card*> container;

public:
	TradeArea() {};


	/// <summary>
	/// The copy constructor
	/// </summary>
	/// <param name="tA">The object to be copied onto the newly constructed object</param>
	TradeArea(const TradeArea& tA) {
		//std::cout << "The copy constructor is called";
		for (Card* item : tA.container) {
			container.push_back(item);
		}
	}

	/// <summary>
	/// This constructor reconstructs a trade area from a given file
	/// </summary>
	/// <param name="input">Input file or stream </param>
	/// <param name="factory">The object that is responsible of generating cards</param>
	TradeArea(std::istream& input, const CardFactory* factory);


	/// <summary>
	/// This method adds a card to the trade area, but it doesn't verify if it's legal to do so
	/// </summary>
	/// <param name="cardToAdd">The card that should be added to the trade area</param>
	/// <returns>A reference to the tradearea newly updated</returns>
	TradeArea& operator+=(Card* const cardToAdd);


	/// <summary>
	/// This method checks if a card can be legally added to the trade area; i.e: a card of the same bean is 
	/// already present in the trade area
	/// </summary>
	/// <param name="cardToAdd">The card that the player wants to add</param>
	/// <returns>True if legal, false if not</returns>
	bool legal(const Card* const cardToAdd);


	/// <summary>
	/// This method removes a card with the type cardType from the trade area
	/// </summary>
	/// <param name="cardType">Type of card to be deleted</param>
	/// <returns>A pointer to the newly deleted card</returns>
	Card* trade(std::string cardType);


	/// <summary>
	/// This method computes the total number of cards currently in the trade area
	/// </summary>
	/// <returns>The number of cards in the trade area</returns>
	int numCards();


	/// <summary>
	/// This method prints the content of the trade area on an output file or stream e.g: R g s
	/// </summary>
	/// <param name="output">The file or the stream where elements are going to be printed</param>
	/// <param name="trade">The tradeArea object to print</param>
	/// <returns>A reference to the file or the stream that we used to write on</returns>
	friend std::ostream& operator << (std::ostream& output, TradeArea trade);

	/// <summary>
	/// Getter of all cards present in the trade area
	/// </summary>
	/// <returns>A list of cards</returns>
	std::list<Card*> getListOfCards();

	/// <summary>
	/// Gets from a trade area a pointer to a card, which code equals c
	/// </summary>
	/// <param name="c">Card symbol</param>
	/// <returns>Pointer to the card</returns>
	Card* getCard(char c);
};