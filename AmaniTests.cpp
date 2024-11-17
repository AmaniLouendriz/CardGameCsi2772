#include <iostream>

#include "Chain.h"
#include "Red.h"


// This file is temporary. Please DO NOT REMOVE

// comment the main if you need to make a new main to test your stuff


int main()
{
    // Testing the Chain class
    Chain<Red> chainRed;
    Card* pointerRed = new Red();
    ((chainRed += pointerRed) += pointerRed)+= pointerRed;
    std::cout << chainRed;
    // Even when the exception is raised, we continue here, which is good 
   delete pointerRed;
}