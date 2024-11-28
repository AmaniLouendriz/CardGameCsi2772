#include "Main.h"


//void cleanup(Player* player1, Player* player2, DiscardPile* disPile, TradeArea* tradeArea, Deck* deck, Table* table) {
//    delete player1;
//    delete player2;
//    delete disPile;
//    delete tradeArea;
//    delete deck;
//    delete table;
//}

/// <summary>
/// Checks whether the card symbol is legal
/// </summary>
/// <param name="card"></param>
/// <returns></returns>

bool static isSymbolLegal(char card) {
    if (card == 'R' || card == 'B' || card == 'C' || card == 'S' || card == 'G' || card == 's' || card == 'b' || card == 'g') {
        return true;
    }
    return false;
}

std::string static mapToName(char type) {
    if (type == 'B') {
        return "Blue";
    }
    else if (type == 'C') {
        return "Chili";
    }
    else if (type == 'S') {
        return "Stink";
    }
    else if (type == 'G') {
        return "Green";
    }
    else if (type == 's') {
        return "soy";
    }
    else if (type == 'b') {
        return "black";
    }
    else if (type == 'R') {
        return "Red";
    }
    else if (type == 'g') {
        return "garden";
    }
    return "";
}

bool static wantsToChainCards() {
    std::cout << "Do you want to add cards from the trade area to your chains?(y/n)  ";
    char answer[2]{};
    std::cin >> answer;
    char card{};

    if (answer[0] == 'y') {
        bool valid{ false };
        while (!valid) {
            std::cout << "Please input the symbol of the card you would like to add to your chains: ";
            std::cin >> card;
            if (!isSymbolLegal(card)) {
                std::cout << "The card symbol you gave is invalid\n";
            }
            else {
                valid = true;
            }
        }
    }
    return card;
}

bool static askForRepetition() {
    std::cout << "Would you like to play another topmost card from hand?:(y/n)   ";
    char answer[2]{};
    std::cin >> answer;
    if (answer[0] == 'y') {
        return true;
    }
    return false;
}

bool static askShowHandDiscardCard() {
    std::cout << "Would you like to show your hand and discard an arbitrary card into the discard pile?:(y/n)   ";
    char answer[2]{};
    std::cin >> answer;
    if (answer[0] == 'y') {
        return true;
    }
    return false;
}



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
                pp->addCardToHand(cc);
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
    Card* cardDrawn{};

    std::cout << "Cards have been given to the two players: \n";

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
            std::cout << *tb << std::endl;
            //Le joueur pioche une carte
            std::cout << "You drew a card from the deck\n";
            cardDrawn = deck.draw();
            current->addCardToHand(cardDrawn);
            std::cout << "The card has been added to your hand\n";
            std::cout << "Your hand is: REMOVE THE HAND GETTER AFTERWARD in the player, Im just using it for debugging\n";// TODO
            std::cout << current->getHand();

            // Ajouter des cartes de TradeArea
            std::cout << "The size of the trade area is: " << trAr->numCards() << "\n";
            if (trAr->numCards() > 0) {
                char card = wantsToChainCards();
                while (card != '\0') {
                    // meaning the player wants to add a card from the trade area to his chains
                    int index{ current->addCardToChain(card) };
                    if (index == -1) {
                        std::cout << "Sorry, you can't get that card from the trade area because you either have no chain with that card type or you have reached your maximum number of chains\n";
                    }
                    else {
                        Card* gottenCard{ trAr->trade(mapToName(card)) };
                        (current->operator[](i + 1)) += gottenCard;// the card is drawn from the trade area and added to the players cards
                    }
                    card = wantsToChainCards();
                }
                // if the player doesn't want the cards, they should be discarded  (in the discard pile)
                for (Card* card : trAr->getListOfCards()) {
                    *disPile += trAr->trade(card->getName());
                }

                // this was replaced by the above
                //for (Card* card : trAr->getListOfCards()) {
                    //if (current->canChainCard(card)) {
                        //current->addToChain(trAr->trade(card->getName()));
                    //}
                    //else {
                        //*disPile += trAr->trade(card->getName());
                    //}
                //}
                // this was replaced by the above
                std::cout << "The player now has the following:FOR DEBUGGING ONLY\n";
                std::cout << *current << std::endl;
                std::cout << "The trading area is now: FOR DEBUGGING ONLY\n";
                std::cout << *trAr << std::endl;
            }

            // Le joueur joue une carte
            //std::cout << "until now is it good?\n";TODO
            std::cout << "You play the first top card from your hand\n";
            current->playCard();
            std::cout << "You have now: \n" << *current << std::endl;
            if (askForRepetition()) {
               current->playCard();// if the player wants, we would play a card again
            }

            // ask player whether he wants to show his hand
            if (askShowHandDiscardCard()) {
                std::cout << "Your hand is: \n";
                std::cout << current->getHand();
                std::cout << std::endl;
                bool valid{ false };
                while (!valid) {
                    char cc{}; std::cout << "which arbitrary card would you like to discard?(enter just the symbol;e.g: R):  "; std::cin >> cc;
                    int index{ current->getHand().doesCardExist(cc) };
                    if (index != -1) {
                        Card* cardDiscarded { current->getHand()[index] };// remove the card at index
                        (*disPile) += cardDiscarded;
                        valid = true;
                    }
                    else {
                        std::cout << "this card doesn't exist on your hand\n";
                    }
                }
            }



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
    delete tb; // the table destructor would delete all of the below
   /* delete p2;
    delete p1;
    delete trAr;
    delete disPile;*/

    return 0;
}