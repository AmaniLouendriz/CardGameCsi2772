#include "Player.h"

/// <summary>
/// Constructor that creates a player with the given name in the parameter
/// </summary>
/// <param name="name">name of the player</param>
Player::Player(std::string& name) {
	playerName = name;
	coinsEarned = 0;
	thirdChainRight = false;
	playerHand = new Hand; // UNSAFE with nullptr, hopefully, this is better
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
	//SOME STUFF SHOULD CHANGE HERE BECAUSE NOW, the space between a players name and coins is just 1 tab

	input.seekg(0, std::ios::ate);// go to the end of the file
	long sizeFile = input.tellg();// get the file size
	input.seekg(0, std::ios::beg);
	std::getline(input, playerName, '\t');// get the player name
	int offSet_name_tab = playerName.size() + 1;// adding 1 to the offset because when we print a player, we add 1 tab before we print the number of coins.

	input.seekg(offSet_name_tab, std::ios::beg);// moove the cursor by the offset
	std::string coins {};
	std::getline(input, coins, ' ');// put the coins in this string var
	coinsEarned = std::stoi(coins);
	int offSet_name_tab_ToEnd = offSet_name_tab + coins.size() + 1 + 6;// this offset takes into account the whole first line from the player name to the line break, we add 1 to count for the space between "number" and "coins", we add 6 because "coins" takes 5 chars and there is a line break at the end
	// from now on, it is not guaranteed that the chains would be present, TODO: check before parsing
	int parsed = offSet_name_tab_ToEnd;
	std::string chainType{};
	Chain_Base* chain{};
	std::string line{};
	while (parsed < sizeFile) {
		input.seekg(parsed, std::ios::beg);
		std::getline(input, chainType, '\t');
		chain = constructChain(input, chainType, factory);
		listOfChains.push_back(chain);
		// as for now, first chain was constructed
		std::getline(input, line, '\n');// to get the offset by which to move the cursor
		parsed = parsed + line.size() + 1;// 1 is add to count for the line break
	}

	if (listOfChains.size() == 3) {
		thirdChainRight = true;
	}
	// how do I initialize the player hand


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


Hand& Player::getHand() {
	return *playerHand;
}




