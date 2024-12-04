#pragma once
#include <iostream>
#include <fstream>

class Card {
public:
    //Methode pour obtenir le nombre de pieces par cartes
    virtual int getCardsPerCoin(int coins) const = 0;
    
    //Methode pour obtenir le nom de la carte
    virtual std::string getName() const = 0;
    
    //Methode pour obtenir le premier caractere du nom de  la carte
    virtual void print(std::ostream& out) const = 0;
    
    //Destructeur
    virtual ~Card() = default;
    
    friend std::ostream& operator<<(std::ostream& out, const Card& card) {
        card.print(out);
        return out;
    };

    Card& operator=(const Card&) = delete;

};

//Classe pour la carte Blue
class Blue : public Card {
public:
    Blue() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Blue"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte Chili
class Chili : public Card {
public:
    Chili() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Chili"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte Stink
class Stink : public Card {
public:
    Stink() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Stink"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte Green
class Green : public Card {
public:
    Green() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Green"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte soy
class soy : public Card {
public:
    soy() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "soy"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte black
class black : public Card {
public:
    black() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "black"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte Red
class Red : public Card {
public:
    Red() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Red"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};

//Classe pour la carte garden
class garden : public virtual Card {
public:
    garden() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "garden"; }
    void print(std::ostream& out) const override { out << getName()[0]; }
};


