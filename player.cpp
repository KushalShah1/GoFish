//
// Created by kusha on 11/9/2019.
//
#include <cstdlib>

#include "player.h"
Player::Player() {
    myName="Unknown";
}
void Player::addCard(Card c) {
    myHand.push_back(c);
}
void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

Card Player::chooseCardFromHand() const {
    int cardIndex=rand()%myHand.size();
    return myHand.at(cardIndex);
}
bool Player::cardInHand(Card c) const {
    for(Card i:myHand){
        if(i==c){
            return true;
        }
    }
    return false;
}

Card Player::removeCardFromHand(Card c) {
    if(cardInHand(c)){
        for(int i=0; i<myHand.size();i++){
            if(myHand.at(i)==c){
                myHand.erase(myHand.begin()+i);
                return c;
            }
        }
    }
    return c;
}

string Player::showHand() const {
    string hand;
    for(Card c: myHand){
        hand+=c.toString()+"/n";
    }
    return hand;
}

string Player::showBooks() const {
    string hand;
    for(Card c: myBook){
        hand+=c.toString()+"/n";
    }
    return hand;
}

int Player::getHandSize() const {
    return myHand.size();
}
int Player::getBookSize() const {
    return myBook.size();
}