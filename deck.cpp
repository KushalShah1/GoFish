//
// Created by kusha on 11/6/2019.
//

#include <ctime>
#include <cstdlib>
#include "deck.h"
//Makes a pristine deck of cards
Deck::Deck() {
    myIndex=0;
    srand(time(0));
    for(int i=0;i<4;i++){
        for(int j=1;j<14;j++){
            myCards[myIndex]=Card(j, (Card::Suit)(i));
            myIndex++;
        }
    }
    myIndex=0;
}
//shuffles the deck of cards so its random
void Deck::shuffle() {
    int rand1;
    int rand2;
    Card temp;
    for(int i=0;i<100;i++){
        rand1=rand()%52;
        rand2=rand()%52;//random indexes

        temp=myCards[rand1];        //swaps cards
        myCards[rand1]=myCards[rand2];
        myCards[rand2]=temp;
    }
}
//deals a card from the top of the deck
Card Deck::dealCard() {
    myIndex++;
    return myCards[myIndex-1];//returns the next card
}
//returns the amount of cards left
int Deck::size() const {
    return 52-myIndex;//52 cards in a deck
}