#include "Table.h"


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
//
////Affiche la main du joueur courrant
//void Table::printHand(bool showAll) {
//    Player* current = (currentPlayer == 0) ? p1 : p2;
//    current->printHand(std::cout, showAll);
//}

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
    deckFile << *deck;
    // Saving deck
    
    deckFile.close();

    std::ofstream dpFile("Saved-DiscardPile.txt", std::ios::trunc);
    if (!dpFile) throw std::runtime_error("Could not open Saved-DiscardPile.txt");
    // Saving discard pile
    disPile->save(dpFile);
    dpFile.close();

    std::ofstream taFile("Saved-TradeArea.txt", std::ios::trunc);
    if (!taFile) throw std::runtime_error("Could not open Saved-TradeArea.txt");
    // Saving trade area
    taFile << *tradeAr;
    taFile.close();
    std::ofstream playerFile1("Saved-Player1.txt", std::ios::trunc);
    if (!playerFile1) throw std::runtime_error("Could not open Saved-Player1.txt");
    // saving players
    //1
    playerFile1 << *p1;
    playerFile1.close();
    //2
    std::ofstream playerFile2("Saved-Player2.txt", std::ios::trunc);
    if (!playerFile2) throw std::runtime_error("Could not open Saved-Player2.txt");
    playerFile2 << *p2;
    playerFile2.close();

    // saving hands
    //1
    std::ofstream playerFileHand1("Saved-PlayerH1.txt", std::ios::trunc);
    if (!playerFileHand1) throw std::runtime_error("Could not open Saved-PlayerH1");
    p1->getHand().saveHand(playerFileHand1);
    playerFileHand1.close();
    // saving hands
    // 2
    std::ofstream playerFileHand2("Saved-PlayerH2.txt", std::ios::trunc);
    if (!playerFileHand2) throw std::runtime_error("Could not open Saved-PlayerH2");
    p2->getHand().saveHand(playerFileHand2);
    playerFileHand2.close();
}

//Recharge le deck du jeu
void Table::reloadDeck() {
    std::ifstream deckFile("Saved-Deck.txt", std::ios::in | std::ios::binary | std::ios::ate);
    if (!deckFile.is_open()) {
        throw std::runtime_error("Saved-Deck.txt not found");
    }
    *deck = Deck(deckFile, cardFact);
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
    std::ifstream trArFile("Saved-TradeArea.txt", std::ios::in | std::ios::binary | std::ios::ate);
    if (!trArFile.is_open()) {
        throw std::runtime_error("Saved-TradeArea.txt not found");
    }
    *tradeAr = TradeArea(trArFile, cardFact);
}


//Afficher les informations de la table
std::ostream& operator<<(std::ostream& output, const Table& tb) {
    // just show the current player
    // discard pile and trade area do not print for some reason
    if (tb.currentPlayer == 0) {
        output << "Player 1:\n" << *(tb.p1) << "\n";
    }
    else {
        output << "Player 2:\n" << *(tb.p2) << "\n";
    }
    output << "Deck: \n";
    output << *(tb.deck) << "\n";
    output << "Discard Pile (Top): " << *(tb.disPile) << "\n";
    output << "Trade Area: " << *(tb.tradeAr) << "\n";
    output << "_______________________\n";
    return output;
}

Deck Table::getDeck() {
    return *deck;
}


void Table::reloadPlayer(int i) {
    if (i == 1) {
        std::ifstream playerFile1("Saved-Player1.txt", std::ios::in | std::ios::binary | std::ios::ate);
        if (!playerFile1.is_open()) {
            throw std::runtime_error("Saved-Player1.txt not found");
        }
        p1 = new Player(playerFile1, cardFact);

        std::ifstream playerFileH1("Saved-PlayerH1.txt");
        if (!playerFileH1.is_open()) {
            throw std::runtime_error("Saved-PlayerH1.txt not found");
        }
        Hand* hand1 = new Hand(playerFileH1, cardFact);
        p1->setHand(hand1);        
    }
    else {
        std::ifstream playerFile2("Saved-Player2.txt", std::ios::in | std::ios::binary | std::ios::ate);
        if (!playerFile2.is_open()) {
            throw std::runtime_error("Saved-Player2.txt not found");
        }
        p2 = new Player(playerFile2, cardFact);

        std::ifstream playerFileH2("Saved-PlayerH2.txt");
        if (!playerFileH2.is_open()) {
            throw std::runtime_error("Saved-PlayerH2.txt not found");
        }
        Hand* hand2 = new Hand(playerFileH2, cardFact);
        p2->setHand(hand2);
    }   
}

DiscardPile* Table::getDiscardPile() {
    return disPile;
}

TradeArea* Table::getTradeArea() {
    return tradeAr;
}