#pragma once
#include <iostream>
#include <vector>
#include "Chain.h"
#include "Hand.h"
#include "Utils.h"

class Player {
	std::string playerName;// TODO: not sure whether this should be a reference or no
	int coinsEarned;
	bool thirdChainRight;
	std::vector<Chain_Base*> listOfChains;
	Hand* playerHand;
	Chain_Base* constructChain(std::istream& input,std::string& type, const CardFactory* factory);
public:
	/// <summary>
	/// Constructor that creates a player with the given name in the parameter
	/// </summary>
	/// <param name="name">name of the player</param>
	Player(std::string& name);


	/// <summary>
	/// This constructor reconstructs a player from a given input stream
	/// </summary>
	/// <param name="input">Input stream from where we will read info</param>
	/// <param name="factory">The factory object responsible for creating cards</param>
	Player(std::istream& input, const CardFactory* factory);


	/// <summary>
	/// Method that returns the name of the player
	/// </summary>
	/// <returns>player name</returns>
	std::string getName();

	/// <summary>
	/// Method that returns the number of coins presently held by the user
	/// </summary>
	/// <returns>number of coins</returns>
	int getNumCoins();


	/// <summary>
	/// Method that adds coinsToAdd to the number of coins currently held by the user 
	/// </summary>
	/// <param name="coinsToAdd">Value of the coins to add</param>
	/// <returns>A reference to the player object which had his coinsEarned attribute modified</returns>
	Player& operator+=(int coinsToAdd);

	/// <summary>
	/// Method that returns the maximum number of chains a player can have
	/// </summary>
	/// <returns>max number of chains</returns>
	int getMaxNumChains();

	/// <summary>
	/// Method that returns the number of non-zero chains for a given player
	/// </summary>
	/// <returns>Number of non-zero chains</returns>
	int getNumChains();


	/// <summary>
	/// Method that returns the chain at position i, i starts at 1
	/// </summary>
	/// <param name="i">position of the chain</param>
	/// <returns>A reference to the chain at the specified position</returns>
	Chain_Base& operator[](int i) const;// the prof is saying it should return a reference to Chain& instead, not sure how that would be done

	/// <summary>
	/// Method that adds an empty third chain to the player for two coins
	/// </summary>
	void buyThirdChain();


	/// <summary>
	/// Method that prints the top card of the players hand if amount is false,
	/// and all of the players hand if amount is true to the supplied ostream
	/// </summary>
	/// <param name="output">Output stream where we would print the object</param>
	/// <param name="amount">Variable that determines what to print</param>
	void printHand(std::ostream& output, bool amount);


	/// <summary>
	/// Method that prints a player object on the output stream, e.g:
	/// Dave    3 coins 
	/// Red     R R R R
    /// Blue    B
	/// </summary>
	/// <param name="output">Output stream where the printing would take place</param>
	/// <param name="player">Player object to print with all its attributes</param>
	/// <returns>a reference to the output stream where the printing took place</returns>
	friend std::ostream& operator << (std::ostream& output, Player& player);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="card"></param>
	/// <returns></returns>
	Hand& addCardToHand(Card* card);


	Hand& getHand() {
		// HAND SHOULD BE PRIVATE, JUST FOR DEBUGGING PURPOSES
		return *playerHand;
	}


	int addCardToChain(char symbol);



	void playCard();




};

