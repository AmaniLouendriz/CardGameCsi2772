#pragma once
#include "DiscardPile.h"
#include "CardFactory.h"
#include "Card.h"



DiscardPile::DiscardPile(std::istream& input, const CardFactory* cardFact) {
    std::string line;
    while (std::getline(input, line)) {
        Card* card = nullptr;

        if (line == "B") card = cardFact->getBlue();
        else if (line == "C") card = cardFact->getChili();
        else if (line == "S") card = cardFact->getStink();
        else if (line == "G") card = cardFact->getGreen();
        else if (line == "s") card = cardFact->getSoy();
        else if (line == "b") card = cardFact->getBlack();
        else if (line == "R") card = cardFact->getRed();
        else if (line == "g") card = cardFact->getGarden();
        else throw std::invalid_argument("Unknown card type: " + line);

        if (card) cards.push_back(card);
    }
}

DiscardPile& DiscardPile::operator+=(Card* c) {
    cards.push_back(c);
    return *this;
}

// Avec ce code, nous renvoyons la carte tout au dessus
Card* DiscardPile::pickUp() {
    if (cards.empty()) throw std::out_of_range("DiscardPile is empty");
    Card* card = cards.back();
    cards.pop_back();
    return card;
}
// Nous renvoyons la carte tout au dessus sans l'enlever
Card* DiscardPile::top() const {
    if (cards.empty()) throw std::out_of_range("DiscardPile is empty");
    return cards.back();
}
// Nous affichons les cartes 
void DiscardPile::print(std::ostream& os) const {
    for (const auto& card : cards) {
        os << card->getName()[0] << " ";
    }
}
// Si l'insertion est nulle
std::ostream& operator<<(std::ostream& os, const DiscardPile& disPile) {
    if (!disPile.cards.empty()) {
        disPile.cards.back()->print(os);
    }
    else {
        os << "-------";
    }
    return os;
}

void DiscardPile::save(std::ostream& out) const {
    for (const auto& card : cards) { 
        out << *card << std::endl; 
    }
}

