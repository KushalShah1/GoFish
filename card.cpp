//
// Created by jayan on 11/9/2019.
//

#include "card.h"
#include <cstring>
#include <cstdio>
#include <sstream>


//constructor??
Card::Card() {
    myRank=1;
    mySuit=Suit (0);
}
//ace of spades
Card::Card(int myRank, Suit s){
    this->myRank = myRank;
    mySuit = s;
};

string Card::toString() const{
    return this->rankString(myRank)+this->suitString(mySuit);
}

bool Card::sameSuitAs(const Card& c) const {
    return (mySuit == c.mySuit);
}

//return rank
int Card::getRank() const {
    return myRank;
}

string Card::suitString(Card::Suit s) const {
    if (s == Suit(0)){
        string suit = "s";
        return suit;
    }
    else if (s == Suit(1)){
        string suit = "h";
        return suit;
    }
    else if (s == Suit(2)){
        string suit = "d";
        return suit;
    }
    else if (s == Suit(3)){
        string suit = "c";
        return suit;
    }
    else{
        string suit = "error";
        return suit;
    }
}

string Card::rankString(int r) const{
    stringstream s;
    if (2 <= r && r<= 10){
        s<<r;
        string rank;
        rank=s.str();
        return rank;
    }
    else if(r==1){
        string rank = "A";
        return rank;
    }
    else if(r==11){
        string rank = "J";
        return rank;
    }
    else if(r==12){
        string rank = "Q";
        return rank;
    }
    else if(r==13){
        string rank = "K";
        return rank;
    }
    else{
        return "error";
    }
}

bool  Card::operator==(const Card &rhs) const {
    return (myRank == rhs.myRank);
}

bool Card::operator != (const Card& rhs) const{
    return (myRank != rhs.myRank);
}