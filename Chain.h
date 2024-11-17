#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>
#include <regex> // need to extract the type of an object from typeid
#include "Card.h"


// PLEASE KEEP COMMENTS FOR NOW, ILL REMOVE THEN ONCE ETH IS DONE

/// <summary>
/// The Chain class that keeps a list of all bean cards a player has
/// </summary>
/// <typeparam name="T">T should be one of the derived class that inherits from Card</typeparam>


template <class T> class Chain {
	std::vector<Card*> list;  // keeps track of the bean cards
	char typeCards[10]; // keeps track of the type of cards chain is holding

public:
	// I am adding a default constructor, not so sure about it, might get deleted

	/// <summary>
	/// A default Chain constructor that initialized the "typeCards" instance variable by extracting it from the typeid of the generic parameter T
	/// </summary>
	

	Chain() {
		//std::cout << "In the Chain constructor: ";
		//std::cout << list.size() << "\n";
		std::regex pattern("[^class(\s)+]+"); // extract the type of a card class using regex
		std::smatch matches;
		std::string s = typeid(T).name();
	    if (std::regex_search(s, matches, pattern)) {
			//std::cout << "the matches are: " << matches[0] << " \n";
			strcpy_s(typeCards,sizeof(typeCards), matches[0].str().c_str());
		}
		//std::cout << "The type is: " << typeCards << "\n";
	}

	//Chain(std::istream&, const CardFactory*);   this gives a problem for some reason, to investigate

	/// <summary>
	/// This redefinition of += adds a new card to a chain
	/// </summary>
	/// <param name="Card"> Card to be added to the chain</param>
	/// <returns>Reference to the newly constructed chain</returns>
	Chain<T>& operator+=(Card*);

	/// <summary>
	/// TODO
	/// </summary>
	/// <returns></returns>
	int sell();

	/// <summary>
	/// Friend fucntion to print a chain on an output stream, e.g: Red R R R 
	/// </summary>
	/// <param name="output">output stream where the printing would be done on</param>
	/// <param name="ch">Chain to print</param>
	/// <returns>a reference to the output stream where the reference took place</returns>
	/// 
	friend std::ostream& operator << (std::ostream& output, Chain<T> ch) {
		output << "Elements de la liste vector: \n";
		output << ch.typeCards << "\t";

		for (int i{ 0 }; i < ch.list.size(); i++) {
			(*(ch.list.at(i))).print(output);
			output << " ";
			//output << "type of element in vector: " << typeid(*(ch.list.at(i))).name();
		}
		return output;
	}
};

template <class T> Chain<T>& Chain<T>::operator+=(Card* cardToAdd) {
		try {
			if (typeid(*cardToAdd).name() != typeid(T).name()) {
				throw "IllegalType Exception when trying to add a card to a chain";
			}
			list.push_back(cardToAdd);
			return *this;
		}
		catch (const char* exception) {
			std::cerr << "Error: " << exception << "\n";
		}
}

template <class T> int Chain<T>::sell(){
	return 1;
}


