#pragma once

#include <queue>
#include <list>
#include <sstream>
#include <cstdlib>
#include "Card.h"
#include "CardFactory.h"

class CardFactory;

class Hand {
private:
    //La main du joueur
    std::queue <Card*, std::list<Card*>> playerHand; 
    //Vide la main du joueur
    void clearHand() {
        while (!playerHand.empty()) {
            delete playerHand.front();// why do we use delete keyword here?
            playerHand.pop();
        }
    }
public:
    //Constructeurs
    Hand() = default;
    Hand(std::istream& input, const CardFactory* cardFact);
    
    Hand& operator+=(Card* card);

    //Met et enleve la carte tout au dessus
    Card* play();

    //Met sans enlever la carte tout au dessus
    Card* top() const;

    //Met et enleve la carte à une position definie
    Card* operator[](int pos);

    //Donne le nombre de cartes en main
    int numCards() const;

    //Affiche toutes les cartes
    friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

    // Enregistre la main dans un fichier
    void saveHand(std::ofstream& filename) const;

    // Destructeur
    ~Hand() {
        clearHand();
    }
};
