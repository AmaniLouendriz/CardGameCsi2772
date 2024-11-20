#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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

	static std::default_random_engine rng;
	static std::random_device rd;

	static int redCount;
	static int blueCount;
	static int chiliCount;
	static int stinkCount;
	static int greenCount;
	static int soyCount;
	static int blackCount;
	static int gardenCount;

	int static const RED_COUNT;
	int static const BLUE_COUNT;
	int static const CHILI_COUNT;
	int static const STINK_COUNT;
	int static const GREEN_COUNT;
	int static const SOY_COUNT;
	int static const BLACK_COUNT;
	int static const GARDEN_COUNT;


	CardFactory();// no one can explicitely create this object
public:
	CardFactory(const CardFactory&) = delete;// copy constructor deleted
	CardFactory& operator=(const CardFactory&) = delete;
	~CardFactory();
	Red* getRed() const;
	Blue* getBlue() const;
	Chili* getChili() const;
	Stink* getStink() const;
	Green* getGreen() const;
	soy* getSoy() const;
	black* getBlack() const;
	garden* getGarden() const;
	Deck getDeck() const;
	// should add getters for other colors as well TODO
	static CardFactory* getFactory(); // should verify whether the object is already created, if yes, return a pointer to it. if not, create it using the constructor and return its pointer
};