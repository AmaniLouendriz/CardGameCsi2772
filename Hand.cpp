#include "Hand.h"

Hand::Hand(std::istream& input, const CardFactory* cardFact) {
    std::string line;
    try {
        while (std::getline(input, line)) {
            Card* card = nullptr;

            //Associe la carte a la chaine 
            if (line == "B") card = new Blue;
            else if (line == "C") card = new Chili;
            else if (line == "S") card = new Stink;
            else if (line == "G") card = new Green;
            else if (line == "s") card = new soy;
            else if (line == "b") card = new black;
            else if (line == "R") card = new Red;
            else if (line == "g") card = new garden;
            else throw std::invalid_argument("Unknown card type: " + line);

            if (card) {
                playerHand.push(card);
            }
        }
    }
    catch (const std::exception& e) {
        //enleve les cartes ajoutees en cas d'erreur
        while (!playerHand.empty()) {
            delete playerHand.front();
            playerHand.pop();
        }
        //L'exception est rappelee
        throw;
    }

}


Card* Hand::play() {
    if (playerHand.empty()) throw std::out_of_range("Hand is empty");
    Card* card = playerHand.front();
    playerHand.pop(); //Enleve la premiere carte
    return card;
}

//Remet la premiere carte
Card* Hand::top() const {
    if (playerHand.empty()) throw std::out_of_range("Hand is empty");
    return playerHand.front();
}

//Remet et enleve une carte a une position donnee
Card* Hand::operator[](int pos) {
    if (pos < 0 || pos >= playerHand.size()) throw std::out_of_range("Index out of range");

    std::queue<Card*, std::list<Card*>> temp;
    Card* card = nullptr;

    for (int i = 0; i < playerHand.size(); ++i) {
        Card* current = playerHand.front();
        playerHand.pop();

        if (i == pos) {
            card = current;
        }
        else {
            temp.push(current);
        }
    }

    playerHand = temp;
    return card;
}

//Retourne le opmbre de cartes
int Hand::numCards() const {
    return playerHand.size();
}

//Affiche toutes les cartes
std::ostream& operator<<(std::ostream& os, const Hand& hand) {
    std::queue<Card*, std::list<Card*>> temp = hand.playerHand;

    while (!temp.empty()) {
        temp.front()->print(os);
        os << " ";
        temp.pop();
    }

    return os;
}


//Met la main dans un fichier
void Hand::saveHand(std::ofstream& filename) const {

    std::queue<Card*, std::list<Card*>> temp = playerHand;

    while (!temp.empty()) {
        temp.front()->print(filename);
        filename << std::endl;
        temp.pop();
    }
    std::cout << "Hand saved." << std::endl;
}

Hand& Hand::operator+=(Card* card) {
    playerHand.push(card);
    return *this;
}