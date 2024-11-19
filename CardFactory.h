#pragma once
#include <iostream>
#include <vector>
#include "Red.h"
#include "Blue.h"
#include "Chili.h"
#include "Stink.h"
#include "Green.h"
#include "soy.h"
#include "black.h"
#include "garden.h"
#include "Card.h"
#include "Deck.h"

class Deck;

class CardFactory {
	static CardFactory* instance;
	static std::vector<Red*> redCards; 
	static std::vector<Blue*> blueCards;
	static std::vector<Chili*> chiliCards;
	static std::vector<Stink*> stinkCards;
	static std::vector<Green*> greenCards;
	static std::vector<soy*> soyCards;
	static std::vector<black*> blackCards;
	static std::vector<garden*> gardenCards;

	CardFactory();// no one can explicitely create this object
public:
	CardFactory(const CardFactory&) = delete;// copy constructor deleted
	CardFactory& operator=(const CardFactory&) = delete;
	~CardFactory();
	Red* getRed() const;
	Deck getDeck() const;
	// should add getters for other colors as well TODO
	static CardFactory* getFactory(); // should verify whether the object is already created, if yes, return a pointer to it. if not, create it using the constructor and return its pointer
};