#include <iostream>
#include <fstream>

#include "Chain.h"
#include "Red.h"


// This file is temporary. Please DO NOT REMOVE

// comment the main if you need to make a new main to test your stuff


int main()
{
    // Testing the Chain class
    Chain<Red> chainRed;
    Card* RedCardPtr = new Red();  // its the cardFactory who should construct this! It shouldnt be allowed here. private constructors? 
    ((chainRed += RedCardPtr) += RedCardPtr)+= RedCardPtr;
    chainRed += RedCardPtr;
    ((chainRed += RedCardPtr) += RedCardPtr) += RedCardPtr;
    std::cout << chainRed;
    // Even when the exception is raised, we continue here, which is good 
    int money{ chainRed.sell() };
    std::cout << "\nIf I ever sell this chain, I would get: " << money << "\n";
    //// reading from a file then constructing the chain

    std::ifstream file("ChainRed.txt", std::ios::in | std::ios::binary );

    const CardFactory* factory{ CardFactory::getFactory() };

    Chain<Red> chainRedFile(file, factory);
    std::cout << "after using the file constructor: \n";
    std::cout << chainRedFile;


    delete factory;
    delete RedCardPtr;
}