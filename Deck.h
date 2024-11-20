#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Card.h"
#include "CardFactory.h"

class CardFactory;

class Deck : public std::vector<Card*>{
	// why would it derive from std::vector??
public:
	Deck() {
		std::cout << "default constructor for deck\n";
	}

	Deck(const Deck& d);
	Deck(std::istream& input, const CardFactory* factory);
	~Deck();
	Card* draw();
	friend std::ostream& operator << (std::ostream& output, Deck deck);
};