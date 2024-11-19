#include "Card.h"
#include <iostream>
#include <stdexcept>
using namespace std;

//Retourne le nombre de points par carte Blue 
int Blue::getCardsPerCoin(int coins) const {
    switch (coins){
    case 1: 
        return 4;
    case 2: 
        return 6;
    case 3: 
        return 8;
    case 4:
        return 10;
    default:
        throw std::invalid_argument("Invalid coin value for Blue card");
    }
}


//Retourne le nombre de points par carte Chili
int Chili::getCardsPerCoin(int coins) const {
    switch (coins){
    case 1:
        return 3;
    case 2:
        return 6;
    case 3:
        return 8;
    case 4:
        return 9;
    default:
        throw std::invalid_argument("Invalid coin value for Chili card");
    }
}


//Retourne le nombre de points par carte Stink
int Stink::getCardsPerCoin(int coins) const {
    switch (coins){
    case 1:
        return 3;
    case 2:
        return 5;
    case 3:
        return 7;
    case 4:
        return 8;
    default:
        throw std::invalid_argument("Invalid coin value for Stink card");
    }
}


//Retourne le nombre de points par carte Green
int Green::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1:
        return 3;
    case 2:
        return 5;
    case 3:
        return 6;
    case 4:
        return 7;
    default:
        throw std::invalid_argument("Invalid coin value for Green card");
    }
}


//Retourne le nombre de points par carte soy
int soy::getCardsPerCoin(int coins)  const {
    switch (coins) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 6;
    case 4:
        return 7;
    default:
        throw std::invalid_argument("Invalid coin value for soy card");
    }
}


//Retourne le nombre de points par carte black
int black::getCardsPerCoin(int coins) const { 
    switch (coins) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 5;
    case 4:
        return 6;
    default:
        throw std::invalid_argument("Invalid coin value for black card");
    }
}


//Retourne le nombre de points par carte Red
int Red::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    default:
        throw std::invalid_argument("Invalid coin value for Red card");
    }
}


//Retourne le nombre de points par carte garden
int garden::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1:
        return 0;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 0;
    default:
        throw std::invalid_argument("Invalid coin value for garden card");
    }
}