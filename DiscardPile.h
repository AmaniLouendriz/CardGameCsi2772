#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Card.h"




class CardFactory;

class DiscardPile {
private :
    std::vector<Card*> cards;
public:
   //Constructeurs
    DiscardPile() = default;
    
    DiscardPile(std::istream& input, const CardFactory* cardFact);
    
    //Ajoute la carte au dessus
    DiscardPile& operator+=(Card* c);
    
    //Enleve et met la carte au dessus
    Card* pickUp();

    Card* top() const;

    //Affiche les cartes
    void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const DiscardPile& disPile);
    
    //Destructeur
    ~DiscardPile() = default;

    void save(std::ostream& out) const;
    //Retourne le nombre de cartes
    size_t size() const {
        return cards.size();
    }


};
