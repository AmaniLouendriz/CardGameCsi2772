#include "Player.h"

/// <summary>
/// Constructor that creates a player with the given name in the parameter
/// </summary>
/// <param name="name">name of the player</param>
Player::Player(std::string& name) {
	playerName = name;
	coinsEarned = 0;
	thirdChainRight = false;
	playerHand = new Hand;
}

Chain_Base* Player::constructChain(std::istream& input, std::string& type,const CardFactory* factory) {
	Chain_Base* cb1{};
	if (type == "Red") {
		cb1 = new Chain<Red>(input, factory);
	}
	else if (type == "Blue") {
		cb1 = new Chain<Blue>(input, factory);
	}
	else if (type == "Chili") {
		cb1 = new Chain<Chili>(input, factory);
	}
	else if (type == "Stink") {
		cb1 = new Chain<Stink>(input, factory);
	}
	else if (type == "Green") {
		cb1 = new Chain<Green>(input, factory);
	}
	else if (type == "soy") {
		cb1 = new Chain<soy>(input, factory);
	}
	else if (type == "black") {
		cb1 = new Chain<black>(input, factory);
	}
	else if (type == "garden") {
		cb1 = new Chain<garden>(input, factory);
	}
	return cb1;
}



/// <summary>
/// This constructor reconstructs a player from a given input stream
/// </summary>
/// <param name="input">Input stream from where we will read info</param>
/// <param name="factory">The factory object responsible for creating cards</param>
Player::Player(std::istream& input, const CardFactory* factory) {
	input.seekg(0, std::ios::beg);
	std::getline(input, playerName, '\t');// get the player name

	std::string coins {};
	std::getline(input, coins, ' ');// put the coins in this string var
	coinsEarned = std::stoi(coins);
	
	std::string chainType{};
	Chain_Base* chain{};
	std::string line{};
	
	std::string tmp{};
	std::getline(input, tmp, '\n');// remove any garbage input

	while (std::getline(input, line)) {
		if (!line.empty()) {
			// extracting the chain
			size_t tabPos = line.find('\t'); // Finding the first tab character
			if (tabPos != std::string::npos) {
				chainType = line.substr(0, tabPos);
			}

			std::istringstream lineStream(line);

			chain = constructChain(lineStream, chainType, factory);

			listOfChains.push_back(chain);
		}
	}

	if (listOfChains.size() == 3) {
		thirdChainRight = true;
	}
	else {
		thirdChainRight = false;
	}
	playerHand = new Hand;
}


/// <summary>
/// Method that returns the name of the player
/// </summary>
/// <returns>player name</returns>
std::string Player::getName() {
	return playerName;
}


/// <summary>
/// Method that returns the number of coins presently held by the user
/// </summary>
/// <returns>number of coins</returns>
int Player::getNumCoins() {
	return coinsEarned;
}

/// <summary>
/// Method that adds coinsToAdd to the number of coins currently held by the user 
/// </summary>
/// <param name="coinsToAdd">Value of the coins to add</param>
/// <returns>A reference to the player object which had his coinsEarned attribute modified</returns>
Player& Player::operator+=(int coinsToAdd) {
	coinsEarned = coinsEarned + coinsToAdd;
	return *this;
}


/// <summary>
/// Method that returns the maximum number of chains a player can have
/// </summary>
/// <returns>max number of chains</returns>
int Player::getMaxNumChains() {
	if (thirdChainRight) {
		return 3;
	}

	return 2;
}


/// <summary>
/// Method that returns the number of non-zero chains for a given player
/// </summary>
/// <returns>Number of non-zero chains</returns>
int Player::getNumChains() {
	int count = 0;
	for (Chain_Base* cb : listOfChains) {
		if (cb->getLengthChain() > 0) {
			count++;
		}
	}
	return count;
}


/// <summary>
/// Method that returns the chain at position i, i starts at 1
/// </summary>
/// <param name="i">position of the chain</param>
/// <returns>A reference to the chain at the specified position</returns>
Chain_Base& Player::operator[](int i) const {
	int index = i - 1;
	if (index < 0 || index >= listOfChains.size()) {
		std::cout << "The requested position for operator[] is invalid\n";
		//return;
	}
	return *(listOfChains.at(i));
}


/// <summary>
/// Method that adds an empty third chain to the player for two coins
/// </summary>
void Player::buyThirdChain() {
	try {
		if (coinsEarned < 2) {
			throw "Not Enough Coins when trying to buy third chain";
		}
		coinsEarned -= 2;
		Chain_Base* newChain{};
		listOfChains.push_back(newChain);
		thirdChainRight = true;
	}
	catch (const char* exception) {
		std::cerr << "Error: " << exception << "\n";
	}
}


/// <summary>
/// Method that prints the top card of the players hand if amount is false,
/// and all of the players hand if amount is true to the supplied ostream
/// </summary>
/// <param name="output">Output stream where we would print the object</param>
/// <param name="amount">Variable that determines what to print</param>
void Player::printHand(std::ostream& output, bool amount) {
	if (amount) {
		output << *playerHand;
	}
	else {
		// just print the top card of a players hand
		output << *(playerHand->top());  // in Card.h, the << operator takes a reference
	}
}


/// <summary>
/// Method that prints a player object on the output stream, e.g:
/// Dave    3 coins 
/// Red     R R R R
/// Blue    B
/// </summary>
/// <param name="output">Output stream where the printing would take place</param>
/// <param name="player">Player object to print with all its attributes</param>
/// <returns>a reference to the output stream where the printing took place</returns>
std::ostream& operator << (std::ostream& output, Player& player) {
	output << player.playerName;
	output << "\t";
	output << player.coinsEarned << " " << "coins\n";
	for (Chain_Base* cb : player.listOfChains) {
		cb->print(output);
	}
	return output;
}


Hand& Player::addCardToHand(Card* card) {
	*(playerHand) += card;
	return *playerHand;
}


void Player::playCard() {
	Card* cardFirst{ playerHand->top() };// get the player's card, without removing it for now
	//std::cout << "the cardFirst is: " << *cardFirst << "\n";
	//std::cout << "the list of chains size is: " << listOfChains.size();
	int res{ addCardToChain(cardFirst) };

	if (res == -1) {
		std::cout << "The card wasn't added to your chains\n";
	}
	else {
		playerHand->play();
	}
}


int Player::addCardToChain(Card* cardFirst) {
	// check first if the list of chains is empty
	if (listOfChains.size() == 0) {
		Chain_Base* ch { utils::constructChain(cardFirst->getName()[0]) };// constructing a new chain of the same type as card
		listOfChains.push_back(ch);
		*listOfChains.at(0) += cardFirst;
		std::cout << "card: " << cardFirst->getName()[0] << "  has been added to one of the your chains\n";
		return 1;
	}

	for (Chain_Base* ch : listOfChains) { // see if the player can add this card to an existing chain or if he has space to make a new chain for that card
		if (ch != nullptr) {
			if (ch->getChainType() == cardFirst->getName()) {
				// card first can be added here
				(*ch) += cardFirst; // card has been added to this chain
				std::cout << "card: " << cardFirst->getName()[0] << "  has been added to one of your existing chains\n";
				return 1;
			}
		}
		else {
			// this only fires if the player bought the right to have a third chain
			Chain_Base* cb = utils::constructChain(cardFirst->getName()[0]);
			*ch = *cb;// new chain with the card type made
			(*ch) += cardFirst;// new card added
			std::cout << "You already bought a right to have a third chain. A new chain is created, and card: " << cardFirst->getName()[0] << " has been added to it\n";
			return 1;
		}
	}

	// If we are here, one possibility is that the player doesnt yet have a chain of that type yet, check for it
	if (listOfChains.size() < getMaxNumChains()) {
		Chain_Base* ch { utils::constructChain(cardFirst->getName()[0]) };// constructing a new chain of the same type as card
		listOfChains.push_back(ch);
		*listOfChains.at(listOfChains.size() - 1) += cardFirst;
		std::cout << "card: " << cardFirst->getName()[0] << "  has been added to one of the your chains\n";
		return 1;
	}

	// if we are here, meaning the player needs to sell a chain he has, but before, check if he can buy the right to have a third one

	if (getNumCoins() >= 2 && !thirdChainRight) {
		std::cout << "You have reached your maximum number of chains but you can buy the right for a third one for 2 coins. Do you wish to proceed?(y/n):  ";
		char answer[2]{};
		std::cin >> answer;
		if (answer[0] == 'y') {
			buyThirdChain();
			listOfChains.at(getNumChains() - 1) = utils::constructChain(cardFirst->getName()[0]);
			listOfChains.at(getNumChains() - 1)->operator+=(cardFirst);
			std::cout << " A new third chain was added\n";
			//int index = getNumChains() - 1;
			return 1;
		}
	}

	// if we are here, one possibility could be that the player reached the number of chains he can have and he doesnt have enough money to buy a third one
	// then he should sell

	std::cout << "You have reached your maximum amount of chains, and you dont have enough coins or you dont want to to purchase the right for a third one, so you will have to sell one of your chains\n";

	int max{ 0 };// we will use this to sell the chain with maximum coins
	char type{};
	int index{ -1 }; // index of the chain to sell
	
	for (int i{ 0 }; i < getNumChains();i++) {
		int amount = listOfChains.at(i)->sell();
		if (amount > max) {
			max = amount;
			index = i;
		}
	}
	

	// what happens to a chain we sell? do we add it to the trade area or sth? TODO
	if (index != -1) {
		std::cout << "By selling your chain at position: " << (index + 1) << ", You would get " << max << " coins extra.\n";
		*this += max;
		type = (*cardFirst).getName()[0];
		listOfChains.at(index)->emptyList();// empty the old chain we sold

		listOfChains.at(index) = utils::constructChain(type);// override the existing chain

		listOfChains.at(index)->operator+=(cardFirst);
		std::cout << "The corresponding chain has been sold and a new chain was constructed instead\n";
		return 1;
	}
	else {
		// none of the chains have a maximum profit for the user, select the first one
		std::cout << "You have to sell your first chain because all your chains did not reach the minimum number of cards to get profit back \n";


		//listOfChains.at(0)->print(std::cout);// old chain that should be overwritten

		listOfChains.at(0)->emptyList();// empty the old chain

		listOfChains.at(0) = (utils::constructChain(cardFirst->getName()[0]));// substitite the old chain with the new one

		listOfChains.at(0)->operator+=(cardFirst);// add the card

		//std::cout << "after the thing\n";
		//listOfChains.at(0)->print(std::cout);
		return 1;
	}
	return -1;
}








