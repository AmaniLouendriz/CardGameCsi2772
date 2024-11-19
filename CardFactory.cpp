#include <iostream>
#include "CardFactory.h"

CardFactory* CardFactory::instance{ nullptr };// init to null
std::vector<Red*> CardFactory::redCards{};
std::vector<Blue*> CardFactory::blueCards{};
std::vector<Chili*> CardFactory::chiliCards{};
std::vector<Stink*> CardFactory::stinkCards{};
std::vector<Green*> CardFactory::greenCards{};
std::vector<soy*> CardFactory::soyCards{};
std::vector<black*> CardFactory::blackCards{};
std::vector<garden*> CardFactory::gardenCards{};

CardFactory::CardFactory() {
	// it would be called exactly once
	//std::cout << "I am the card factory\n";
	// Toutes les cartes doivent etre crees en nombre necessaires pour le jeu

	// Create blue cards
	//for (int i{ 0 }; i < 20; i++) {
	//	Blue item;
	//	blueCards.push_back(item);
	//}

	//// Create chili cards
	//for (int i{ 0 }; i < 18; i++) {
	//	Chili item;
	//	chiliCards.push_back(item);// copy constructor involved ?
	//}

	//// Create Stink Cards
	//for (int i{ 0 }; i < 16; i++) {
	//	Stink item;
	//	stinkCards.push_back(item);
	//}

	//// Create Green  Cards
	//for (int i{ 0 }; i < 14; i++) {
	//	Green item;
	//	greenCards.push_back(item);
	//}

	//// Create soy Cards
	//for (int i{ 0 }; i < 12; i++) {
	//	soy item;
	//	soyCards.push_back(item);
	//}

	//// Create black cards
	//for (int i{ 0 }; i < 10; i++) {
	//	black item;
	//	blackCards.push_back(item);
	//}

	// Create red Cards
	for (int i{ 0 }; i < 8; i++) {
		Red* item = new Red();
		redCards.push_back(item);
	}

	// Create garden cards
	/*for (int i{ 0 }; i < 6; i++) {
		garden item;
		gardenCards.push_back(item);
	}*/
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


// TODO make a destructor for CardFactory so that all cards in all containers would get deleted when the factory is deleted

//void CardFactory::test() const {
//	std::cout << "testing";
//}