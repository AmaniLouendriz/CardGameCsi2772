#include "Main.h"
#include <fstream>
#include <sstream>

using namespace std;

void cleanup(Player* player1, Player* player2, DiscardPile* disPile, TradeArea* tradeArea, Deck* deck, Table* table) {
    delete player1;
    delete player2;
    delete disPile;
    delete tradeArea;
    delete deck;
    delete table;
}

int main() {

    std::string p1_name, p2_name, winner_name;
    const int MAX_NUM_PLAYER = 2;
    Player* p1 = nullptr, * p2 = nullptr;
    DiscardPile* disPile = new DiscardPile;
    CardFactory* cardFact = CardFactory::getFactory();
    Deck* deck = nullptr;
    TradeArea* trAr = new TradeArea;
    Table* tb = nullptr;
    char user_input[2];
    bool savedGame;

    //Demande a l'utilisisateur s'il veut recharger un jeu
    std::cout << "Do you want to reload a game?(y/n)" << std::endl;
    std::cin >> user_input;

    if (user_input[0] == 'y') {
        tb = new Table(*p1, *p2, *disPile, *trAr, *deck, *cardFact);

        // Charge les données sauvegardées
        try {
            tb->reloadDeck();
            deck = tb->getDeck();

            tb->reloadPlayer(1);
            tb->reloadPlayer(2);
            p1 = tb->getPlayer(0);
            p2 = tb->getPlayer(1);

            tb->reloadDiscardPile();
            disPile = tb->getDiscardPile();

            tb->reloadTradeArea();
            trAr = tb->getTradeArea();
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error loading saved game: " << e.what() << std::endl;
            cleanup(p1, p2, disPile, trAr, deck, tb);
            return -1;
        }
    }
    else {
        cout << std::endl;
        cout << "Enter the name of the first player: ";
        cin >> p1_name;
        cout << std::endl;
        cout << "Enter the name of the second player: ";
        cin >> p2_name;
        cout << std::endl;

        p1 = new Player(p1_name);
        p2 = new Player(p2_name);

        tb = new Table(*p1, *p2, *disPile, *trAr, *deck, *cardFact);
        deck = tb->getDeck();

        // Distribution de 5 cartes à chaque joueur
        for (int i = 0; i < MAX_NUM_PLAYER; ++i) {
            for (int j = 0; j < 5; ++j) {
                tb->getPlayer(i)->takeCard(deck->draw());
            }
        }
    }

    //Boucle du jeu
    while (deck->size() > 0) {
        cout << "Remaining cards in deck: " << deck->size() << endl;
        cout << "Do you want to pause and save the game? (y/n)" << endl;
        cin >> user_input;

        if (user_input[0] == 'y') {
            tb->saveTable();
            cout << "Game saved. Exiting." << endl;
            delete p1;
            delete p2;
            delete disPile;
            delete trAr;
            delete tb;
            return 0;
        }

        for (int i = 0; i < MAX_NUM_PLAYER; ++i) {
            Player* current = tb->getPlayer(i);

            // Tour du joueur
            cout << "Player " << current->getName() << "'s turn:" << endl;

            // Le joueur pioche une carte
            current->takeCard(deck->draw());

            // Ajouter des cartes de TradeArea
            if (trAr->numCards() > 0) {
                for (Card* card : trAr->getListOfCards()) {
                    if (current->canChainCard(card)) {
                        current->addToChain(trAr->trade(card->getName()));
                    }
                    else {
                        *disPile += trAr->trade(card->getName());
                    }
                }
            }

            // Le joueur joue une carte
            current->playCard();

            // Gestion des cartes dans TradeArea
            while (disPile->size() > 0 && trAr->legal(disPile->top())) {
                *trAr += disPile->pickUp();
            }

            // Tirage de nouvelles cartes
            for (int j = 0; j < 2; ++j) {
                if (deck->size() > 0) {
                    current->takeCard(deck->draw());
                }
            }

            // Affiche l'état actuel
            cout << *current << endl;
            cout << "Discard Pile: ";
            disPile->print(cout);
            cout << endl;
        }
    }

    // Fin du jeu
    tb->win(winner_name);
    cout << "The winner is: " << winner_name << endl;

    // Nettoyage
    delete p1;
    delete p2;
    delete disPile;
    delete trAr;
    delete tb;

    return 0;
}