#include <iostream>
#include <algorithm>
#include <random>
#include "CardFactory.h"

CardFactory* CardFactory::instance{ nullptr };// init to null
std::vector<Blue*> CardFactory::blueCards{};
std::vector<Chili*> CardFactory::chiliCards{};
std::vector<Stink*> CardFactory::stinkCards{};
std::vector<Green*> CardFactory::greenCards{};
std::vector<soy*> CardFactory::soyCards{};
std::vector<black*> CardFactory::blackCards{};
std::vector<garden*> CardFactory::gardenCards{};
std::vector<Red*> CardFactory::redCards{};


CardFactory::CardFactory() {
	// it would be called exactly once
	std::cout << "I am the card factory constructor\n";
	// Toutes les cartes doivent etre crees en nombre necessaires pour le jeu

	// Create blue cards
	for (int i{ 0 }; i < 20; i++) {
		Blue* item = new Blue();
		blueCards.push_back(item);
	}

	// Create chili cards
	for (int i{ 0 }; i < 18; i++) {
		Chili* item = new Chili();
		chiliCards.push_back(item);// copy constructor involved ?
	}

	// Create Stink Cards
	for (int i{ 0 }; i < 16; i++) {
		Stink* item = new Stink();
		stinkCards.push_back(item);
	}

	// Create Green  Cards
	for (int i{ 0 }; i < 14; i++) {
		Green* item = new Green();
		greenCards.push_back(item);
	}

	// Create soy Cards
	for (int i{ 0 }; i < 12; i++) {
		soy* item = new soy();
		soyCards.push_back(item);
	}

	// Create black cards
	for (int i{ 0 }; i < 10; i++) {
		black* item = new black();
		blackCards.push_back(item);
	}

	// Create garden cards
	for (int i{ 0 }; i < 6; i++) {
		garden* item = new garden();
		gardenCards.push_back(item);
	}

	// Create red Cards
	for (int i{ 0 }; i < 8; i++) {
		Red* item = new Red();
		redCards.push_back(item);
	}
}

CardFactory::~CardFactory() {
	std::cout << "I am the card factory destructor\n";

	for (Card* item : redCards) {
		delete item;
	}

	// UNCOMMENT when ALL CARD CLASSES ARE IMPLEMENTED

	/*for (Card* item : gardenCards) {
		delete item;
	}

	for (Card* item : blackCards) {
		delete item;
	}

	for (Card* item : soyCards) {
		delete item;
	}

	for (Card* item : greenCards) {
		delete item;
	}


	for (Card* item : stinkCards) {
		delete item;
	}


	for (Card* item : chiliCards) {
		delete item;
	}

	for (Card* item : blueCards) {
		delete item;
	}	*/
}

CardFactory* CardFactory::getFactory() {
	if (!instance) {
		instance = new CardFactory();
	}
	return instance;
}

Red* CardFactory::getRed() const {
	Red* item { redCards.back() };
	redCards.pop_back();
	return item;
}

Deck CardFactory::getDeck() const{
	std::cout << "Inside the getDeck\n";
	Deck myDeck;
	auto rng = std::default_random_engine{};
	// UNCOMMENT WHEN THE CLASSES ARE IMPLEMENTED
	/*for (Card* item : blueCards) {
		myDeck.push_back(item);
	}*/

	for (Card* item : redCards) {
		myDeck.push_back(item);
	}

	/*for (Card* item : chiliCards) {
		myDeck.push_back(item);
	}*/

	/*for (Card* item : stinkCards) {
		myDeck.push_back(item);
	}

	for (Card* item : greenCards) {
		myDeck.push_back(item);
	}

	for (Card* item : soyCards) {
		myDeck.push_back(item);
	}

	for (Card* item : blackCards) {
		myDeck.push_back(item);
	}

	for (Card* item : gardenCards) {
		myDeck.push_back(card);
	}*/

	std::shuffle(std::begin(myDeck), std::end(myDeck), rng);
	return myDeck;
}
