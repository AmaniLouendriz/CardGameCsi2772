// UNCOMMENT ONCE THIS FUNCTIONALITY HAS BEEN IMPLEMENTED

//#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
//#include "TradeArea.h"
#include  "CardFactory.h"
#include <stdexcept>

class Table {
    //Player* p1;
    //Player* p2;
    int currentPlayer; // id of the current player
    DiscardPile* disPile;
    //TradeArea* tradeAr;
    Deck* deck;
    CardFactory* cardFact;

public:
    //On construit une nouvelle table
    /*Table(Player& player1, Player& player2, DiscardPile& discardPile, TradeArea& tradeArea, Deck& deck, CardFactory& cardFactory)
        :p1(&player1), p2(&player2), disPile(&discardPile), tradeAr(&tradeArea), deck(&deck), cardFact(&cardFactory), currentPlayer(0){}*/
    
    //Destructeur
    ~Table() = default;

    bool win(std::string&);
    void printHand(bool);
    friend std::ostream& operator<<(std::ostream&, const Table&);
    void saveTable();
    void reloadDeck();
    void reloadDiscardPile();
    void reloadTradeArea();
    //Player* getPlayer(int);
};