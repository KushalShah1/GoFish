#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
void checkAndRemoveBook(Player &currentPlayer,Card &book1, Card &book2, ofstream &testlog );

int main( )
{
    int numCards = 7;

    Player currentPlayer("Joe");//Joe is a player
    Player otherPlayer("Jane");//Jane is the other

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, currentPlayer, numCards);//deals cards
    dealHand(d, otherPlayer, numCards);

    ofstream testlog("testlog.txt",ios::trunc);//file for output
    bool gameOver=false;

    Card book1;
    Card book2;
    Card temp;
    while(!gameOver){//while game isnt over

        checkAndRemoveBook(currentPlayer,book1,book2,testlog);//book at the start of turn

        if(currentPlayer.getHandSize()>0&&d.size()>0) {//if the player has cards and there is cards in deck
            temp = currentPlayer.chooseCardFromHand();
            testlog << currentPlayer.getName() << " asks: Do you have any " << temp.rankString(temp.getRank()) << endl;//asks for a card

            if (otherPlayer.cardInHand(temp)) {
                testlog << otherPlayer.getName() << " says: Yes I have a" << temp.rankString(temp.getRank()) << endl;//if the other has the card
                temp = otherPlayer.removeCardFromHand(temp);
                currentPlayer.addCard(temp);//take the card and add it

                checkAndRemoveBook(currentPlayer,book1,book2,testlog);//book the pair
            } else {
                testlog << otherPlayer.getName() << " says: Go Fish" << endl;//doesnt have the card say go fish
                temp = d.dealCard();
                currentPlayer.addCard(temp);
                testlog << currentPlayer.getName() << " draws a " << temp.toString() << endl;//draws from deck

                checkAndRemoveBook(currentPlayer,book1,book2,testlog);//book it if its a pair
            }
        }
        else if(currentPlayer.getHandSize()>0&&d.size()==0) {//if the people have cards and there is no cards in deck
            temp = currentPlayer.chooseCardFromHand();
            testlog << currentPlayer.getName() << " asks: Do you have any " << temp.rankString(temp.getRank()) << endl;//by logic they must have the a pair

            if (otherPlayer.cardInHand(temp)) {
                testlog << otherPlayer.getName() << " says: Yes I have a" << temp.rankString(temp.getRank()) << endl;
                temp = otherPlayer.removeCardFromHand(temp);
                currentPlayer.addCard(temp);

                checkAndRemoveBook(currentPlayer, book1, book2, testlog);//book it
            }
        }

        else if(d.size()>0){
            temp = d.dealCard();//player had no cards and draws from deck
            currentPlayer.addCard(temp);
            testlog << currentPlayer.getName() << " has no cards and draws a " << temp.toString() << endl;
            checkAndRemoveBook(currentPlayer,book1,book2,testlog);

        }
        else{
            gameOver=true;
        }

        if(currentPlayer.getBookSize()+otherPlayer.getBookSize()==26){//games over when total pairs is 26
            gameOver=true;
        }

        Player toSwap= currentPlayer;
        currentPlayer=otherPlayer;//swap turns
        otherPlayer=toSwap;
        testlog<<endl;

    }

    checkAndRemoveBook(currentPlayer,book1,book2,testlog);//book at the very end, just to get total pair numbers
    checkAndRemoveBook(otherPlayer,book1,book2,testlog);

    testlog << currentPlayer.getName() <<" has : " << currentPlayer.getBookSize() << endl;
    testlog << otherPlayer.getName() <<" has : " << otherPlayer.getBookSize() << endl;

    if(currentPlayer.getBookSize()>otherPlayer.getBookSize()){
        testlog<<currentPlayer.getName()<< " is the winner with "<<currentPlayer.getBookSize()<< " pairs!";//determines winners
    }
    else if(currentPlayer.getBookSize()<otherPlayer.getBookSize()){
        testlog<<otherPlayer.getName()<< " is the winner with "<<otherPlayer.getBookSize()<< " pairs!";
    }
    else{
        testlog<<"Its a tie";
    }
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

void checkAndRemoveBook(Player &currentPlayer,Card &book1, Card &book2, ofstream &testlog ){
    while(currentPlayer.checkHandForBook(book1,book2)){
        currentPlayer.bookCards(book1, book2);
        currentPlayer.removeCardFromHand(book1);
        currentPlayer.removeCardFromHand(book2);
        testlog<<currentPlayer.getName()<<" books the "<<book1.rankString(book1.getRank())<<endl;
    }
}