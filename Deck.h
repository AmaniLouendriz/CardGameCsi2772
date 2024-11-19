#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
#include "CardFactory.h"

class Deck : public std::vector<Card*>{
	// why would it derive from std::vector??
public:
	Deck();

	Deck(Deck& d);
	~Deck();
	//Deck(std::istream& input, const CardFactory* factory);
	Card* draw();
	friend std::ostream& operator << (std::ostream& output, Deck deck);
};