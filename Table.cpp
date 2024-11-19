#include "Table.h"
#include <fstream>
#include <stdexcept>
#include <iostream>


//Retourne true si un joueur a gagne en donnant le nom par reference
bool Table::win(std::string& pName) {
    if (deck->size() > 0) {
        return false;
    }
    if (p1->getNumCoins() > p2->getNumCoins()) {
        pName = p1->getName();
    }
    else if (p1->getNumCoins() < p2->getNumCoins()) {
        pName = p2->getName();
    }
    else { //  equality
       pName = "Equality";
    }
    return true;
}

//Affiche la main du joueur courrant
void Table::printHand(bool showAll) {
    Player* current = (currentPlayer == 0) ? p1 : p2;
    current->printHand(std::cout, showAll);
}

//Joueur par l'ID
Player* Table::getPlayer(int id) {
    currentPlayer = id;
    if (id == 0) return p1;
    else return p2;
}

//Enregistre l'etat de la table 
void Table::saveTable() {
    std::ofstream deckFile("Saved-Deck.txt", std::ios::trunc);
    if (!deckFile) throw std::runtime_error("Could not open Saved-Deck.txt");
    deck->saveDeck(deckFile);
    deckFile.close();

    std::ofstream dpFile("Saved-DiscardPile.txt", std::ios::trunc);
    if (!dpFile) throw std::runtime_error("Could not open Saved-DiscardPile.txt");
    disPile->save(dpFile);
    dpFile.close();

    std::ofstream taFile("Saved-TradeArea.txt", std::ios::trunc);
    if (!taFile) throw std::runtime_error("Could not open Saved-TradeArea.txt");
    tradeAr->saveTradeArea(taFile);
    taFile.close();

    p1->savePlayer(1);
    p2->savePlayer(2);
}

//Recharge le deck du jeu
void Table::reloadDeck() {
    std::ifstream deckFile("Saved-Deck.txt");
    if (!deckFile.is_open()) {
        throw std::runtime_error("Saved-Deck.txt not found");
    }
    *deck = Deck(deckFile, *cardFact);
}

//Recharge discardPile
void Table::reloadDiscardPile() {
    std::ifstream dpFile("Saved-DiscardPile.txt");
    if (!dpFile.is_open()) {
        throw std::runtime_error("Saved-DiscardPile.txt not found");
    }
    *disPile = DiscardPile(dpFile, cardFact);
}

//Recharge TradeArea
void Table::reloadTradeArea() {
    std::ifstream trArFile("Saved-TradeArea.txt");
    if (!trArFile.is_open()) {
        throw std::runtime_error("Saved-TradeArea.txt not found");
    }
    *tradeAr = TradeArea(trArFile, cardFact);
}


//Afficher les informations de la table
std::ostream& operator<<(std::ostream& output, const Table& tb) {
    output << "Player 1:\n" << tb.p1 << "\n";
    output << "Player 2:\n" << tb.p2 << "\n";
    output << "Discard Pile (Top): " << tb.disPile << "\n";
    output << "Trade Area: " << tb.tradeAr << "\n";
    output << "_______________________\n";
    return output;
}