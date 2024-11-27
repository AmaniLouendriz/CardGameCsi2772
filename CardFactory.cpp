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


std::random_device CardFactory::rd{};
std::default_random_engine CardFactory::rng{rd()};
int CardFactory::redCount   { 8 };
int CardFactory::blueCount  { 20 };
int CardFactory::chiliCount { 18 };
int CardFactory::stinkCount { 16 };
int CardFactory::greenCount { 14 };
int CardFactory::soyCount   { 12 };
int CardFactory::blackCount { 10 };
int CardFactory::gardenCount { 6 };
int const CardFactory::RED_COUNT {8};
int const CardFactory::BLUE_COUNT {20};
int const CardFactory::CHILI_COUNT {18};
int const CardFactory::STINK_COUNT {16};
int const CardFactory::GREEN_COUNT{ 14 };
int const CardFactory::SOY_COUNT {12};
int const CardFactory::BLACK_COUNT {10};
int const CardFactory::GARDEN_COUNT {6};


CardFactory::CardFactory() {
	// it would be called exactly once
	// std::cout << "I am the card factory constructor\n";
	// All cards should be created in the necessary count for the game

	// Create blue cards
	for (int i{ 0 }; i < BLUE_COUNT; i++) {
		Blue* item = new Blue();
		blueCards.push_back(item);
	}

	// Create chili cards
	for (int i{ 0 }; i < CHILI_COUNT; i++) {
		Chili* item = new Chili();
		chiliCards.push_back(item);// copy constructor involved ?
	}

	// Create Stink Cards
	for (int i{ 0 }; i < STINK_COUNT; i++) {
		Stink* item = new Stink();
		stinkCards.push_back(item);
	}

	// Create Green  Cards
	for (int i{ 0 }; i < GREEN_COUNT; i++) {
		Green* item = new Green();
		greenCards.push_back(item);
	}

	// Create soy Cards
	for (int i{ 0 }; i < SOY_COUNT; i++) {
		soy* item = new soy();
		soyCards.push_back(item);
	}

	// Create black cards
	for (int i{ 0 }; i < BLACK_COUNT; i++) {
		black* item = new black();
		blackCards.push_back(item);
	}

	// Create garden cards
	for (int i{ 0 }; i < GARDEN_COUNT; i++) {
		garden* item = new garden();
		gardenCards.push_back(item);
	}

	// Create red Cards
	for (int i{ 0 }; i < RED_COUNT; i++) {
		Red* item = new Red();
		redCards.push_back(item);
	}
}

CardFactory::~CardFactory() {
	//std::cout << "I am the card factory destructor\n";

	for (Card* item : redCards) {
		delete item;
	}

	for (Card* item : gardenCards) {
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
	}
}

CardFactory* CardFactory::getFactory() {
	if (!instance) {
		instance = new CardFactory();
	}
	return instance;
}

Red* CardFactory::getRed() const {
	Red* item { redCards.at(redCount-1)};
	redCount--;
	if (redCount == 0) {
		redCount = RED_COUNT;
	}
	return item;
}

Blue* CardFactory::getBlue() const {
	Blue* item{ blueCards.at(blueCount - 1) };
	blueCount--;
	if (blueCount == 0) {
		blueCount = BLUE_COUNT;
	}
	return item;
}

Chili* CardFactory::getChili() const {
	Chili* item{ chiliCards.at(chiliCount - 1) };
	chiliCount--;
	if (chiliCount == 0) {
		chiliCount = CHILI_COUNT;
	}
	return item;
}

Stink* CardFactory::getStink() const {
	Stink* item{ stinkCards.at(stinkCount - 1) };
	stinkCount--;
	if (stinkCount == 0) {
		stinkCount = STINK_COUNT;
	}
	return item;
}

Green* CardFactory::getGreen() const {
	Green* item{ greenCards.at(greenCount - 1) };
	greenCount--;
	if (greenCount == 0) {
		greenCount = GREEN_COUNT;
	}
	return item;
}

soy* CardFactory::getSoy() const {
	soy* item{ soyCards.at(soyCount - 1) };
	soyCount--;
	if (soyCount == 0) {
		soyCount = SOY_COUNT;
	}
	return item;
}

black* CardFactory::getBlack() const {
	black* item{ blackCards.at(blackCount - 1) };
	blackCount--;
	if (blackCount == 0) {
		blackCount = BLACK_COUNT;
	}
	return item;
}

garden* CardFactory::getGarden() const {
	garden* item{ gardenCards.at(gardenCount - 1) };
	gardenCount--;
	if (gardenCount == 0) {
		gardenCount = GARDEN_COUNT;
	}
	return item;
}

Deck CardFactory::getDeck() const{
	//std::cout << "Inside the getDeck\n";
	Deck myDeck;

	for (Card* item : blueCards) {
		myDeck.push_back(item);
	}

	for (Card* item : redCards) {
		myDeck.push_back(item);
	}

	for (Card* item : chiliCards) {
		myDeck.push_back(item);
	}

	for (Card* item : stinkCards) {
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
		myDeck.push_back(item);
	}

	std::shuffle(std::begin(myDeck), std::end(myDeck), rng);
	return myDeck;
}
