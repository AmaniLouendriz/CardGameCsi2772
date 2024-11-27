#include "Main.h"


//void cleanup(Player* player1, Player* player2, DiscardPile* disPile, TradeArea* tradeArea, Deck* deck, Table* table) {
//    delete player1;
//    delete player2;
//    delete disPile;
//    delete tradeArea;
//    delete deck;
//    delete table;
//}

int main() {

    std::string p1_name{};// player 1
    std::string p2_name{};//player 2
    std::string winner_name{};

    const int MAX_NUM_PLAYER = 2;
    Player* p1 = nullptr;
    Player* p2 = nullptr;

    DiscardPile* disPile = new DiscardPile;

    CardFactory* cardFact = CardFactory::getFactory();
    Deck deck{};
    TradeArea* trAr = new TradeArea;
    Table* tb = nullptr;
    char user_input[2];
    bool savedGame{};

    //Demande a l'utilisateur s'il veut recharger un jeu
    std::cout << "Do you want to reload a game?(y/n)" << std::endl;
    std::cin >> user_input;

    if (user_input[0] == 'y') {
        // Case where the user wants to reload game from file
        
    //    tb = new Table(*p1, *p2, *disPile, *trAr, *deck, *cardFact);

    //    // Charge les données sauvegardées
    //    try {
    //        tb->reloadDeck();
    //        deck = tb->getDeck();

    //        tb->reloadPlayer(1);
    //        tb->reloadPlayer(2);
    //        p1 = tb->getPlayer(0);
    //        p2 = tb->getPlayer(1);

    //        tb->reloadDiscardPile();
    //        disPile = tb->getDiscardPile();

    //        tb->reloadTradeArea();
    //        trAr = tb->getTradeArea();
    //    }
    //    catch (const std::runtime_error& e) {
    //        std::cerr << "Error loading saved game: " << e.what() << std::endl;
    //        cleanup(p1, p2, disPile, trAr, deck, tb);
    //        return -1;
    //    }
    }
    else {
        // we assume that names do not contain white space chars

        std::cout << std::endl;
        std::cout << "Enter the name of the first player: ";
        std::cin >> p1_name;
        //std::cout << "The name of the first player is: " << p1_name;// DEBUGGING, TO BE REMOVED
          
        std::cout << std::endl;
        std::cout << "Enter the name of the second player: ";
        std::cin >> p2_name;
        std::cout << std::endl;

        p1 = new Player(p1_name);
        p2 = new Player(p2_name);

        deck = cardFact->getDeck();
        tb = new Table(*p1, *p2, *disPile, *trAr, deck, *cardFact);// Why sending as references, why not as pointers?
        Card* cc{};
        Player* pp{};
        // Distribution de 5 cartes à chaque joueur
        std::cout << "Before giving the cards to the players, the deck is: \n";
        std::cout << deck;
        for (int i = 0; i < MAX_NUM_PLAYER; ++i) {
            // get the player first
            pp = tb->getPlayer(i);
            for (int j = 0; j < 5; ++j) {
                // Draw the card from the deck
                cc = deck.draw();// not sure whether the draw should be the first or the last element of the deck, right now Im doing the last
                // add this card to the players hand
                (pp->getHand()) += cc;
            }
        }

        // DEBUGGING, PLS LEAVE THE FOLLOWING LINES FOR NOW COMMENTED

       /* std::cout << "after giving to each player their hands: \n";
        std::cout << *p1;
        std::cout << std::endl;
        std::cout << *p2;
        std::cout << "The hand of the first player is: \n";
        std::cout << p1->getHand();
        std::cout << std::endl;
        std::cout << "The hand of the second player is: \n";
        std::cout << p2->getHand();
        std::cout << std::endl;*/
    }

    //Boucle du jeu
    while (deck.size() > 0) {
        std::cout << "Remaining cards in deck: " << deck.size() << std::endl;
        std::cout << "Do you want to pause and save the game? (y/n)" << std::endl;
        std::cin >> user_input;

        if (user_input[0] == 'y') {
            // in case the player wants to pause and save
            
            //tb->saveTable();
            //cout << "Game saved. Exiting." << endl;
            //delete p1;
            //delete p2;
            //delete disPile;
            //delete trAr;
            //delete tb;
            return 0;
        }

        for (int i = 0; i < MAX_NUM_PLAYER; ++i) {
            Player* current = tb->getPlayer(i);

            // Tour du joueur
            std::cout << "Player " << current->getName() << "'s turn:" << std::endl;

            // display the table first







    //        // Le joueur pioche une carte
    //        current->takeCard(deck->draw());

    //        // Ajouter des cartes de TradeArea
    //        if (trAr->numCards() > 0) {
    //            for (Card* card : trAr->getListOfCards()) {
    //                if (current->canChainCard(card)) {
    //                    current->addToChain(trAr->trade(card->getName()));
    //                }
    //                else {
    //                    *disPile += trAr->trade(card->getName());
    //                }
    //            }
    //        }

    //        // Le joueur joue une carte
    //        current->playCard();

    //        // Gestion des cartes dans TradeArea
    //        while (disPile->size() > 0 && trAr->legal(disPile->top())) {
    //            *trAr += disPile->pickUp();
    //        }

    //        // Tirage de nouvelles cartes
    //        for (int j = 0; j < 2; ++j) {
    //            if (deck->size() > 0) {
    //                current->takeCard(deck->draw());
    //            }
    //        }

    //        // Affiche l'état actuel
    //        cout << *current << endl;
    //        cout << "Discard Pile: ";
    //        disPile->print(cout);
    //        cout << endl;
        }
    }

    //// Fin du jeu
    //tb->win(winner_name);
    //cout << "The winner is: " << winner_name << endl;

    //// Nettoyage
    //delete p1;
    //delete p2;
    //delete disPile;
    //delete trAr;
    //delete tb;

    //return 0;
}