#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);

int main( )
{
    int numCards = 7;

    Player p1("Joe");
    Player p2("Jane");

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);

    cout << p1.getName() <<" has : " << p1.showHand() << endl;
    cout << p2.getName() <<" has : " << p2.showHand() << endl;

    ofstream testlog("testlog.txt");
    bool gameOver=false;

    Player currentPlayer=p1;
    Player otherPlayer=p2;
    while(!gameOver){


        Card book1;
        Card book2;
        while(currentPlayer.checkHandForBook(book1,book2)){
            currentPlayer.bookCards(book1, book2);
            currentPlayer.removeCardFromHand(book1);
            currentPlayer.removeCardFromHand(book2);

            testlog<<currentPlayer.getName()<<" books the "<<book1.rankString(book1.getRank())<<endl;
        }



        Card temp;
        if(currentPlayer.getHandSize()>0&&d.size()>0) {
            temp = currentPlayer.chooseCardFromHand();
            testlog << currentPlayer.getName() << " asks do you have any " << temp.rankString(temp.getRank()) << endl;

            if (otherPlayer.cardInHand(temp)) {
                testlog << otherPlayer.getName() << " says: Yes I have a" << temp.rankString(temp.getRank()) << endl;
                temp = otherPlayer.removeCardFromHand(temp);
                currentPlayer.addCard(temp);

                Card remove1 = currentPlayer.removeCardFromHand(temp);
                Card remove2 = currentPlayer.removeCardFromHand(temp);

                currentPlayer.bookCards(remove1, remove2);
                testlog << currentPlayer.getName() << " books the " << remove1.rankString(remove1.getRank()) << endl;
            } else {
                testlog << otherPlayer.getName() << " says Go Fish" << endl;
                temp = d.dealCard();
                currentPlayer.addCard(temp);
                testlog << currentPlayer.getName() << " draws a " << temp.toString() << endl;


                if(currentPlayer.checkHandForBook(book1,book2)) {
                    currentPlayer.bookCards(book1, book2);
                    currentPlayer.removeCardFromHand(book1);
                    currentPlayer.removeCardFromHand(book2);
                    testlog << currentPlayer.getName() << " books the " << book1.rankString(book1.getRank()) << endl;
                }
            }
        }
        else if(d.size()>0){
            temp = d.dealCard();
            currentPlayer.addCard(temp);
            testlog << currentPlayer.getName() << " has no cards and draws a " << temp.toString() << endl;
        }
        else{
            while(otherPlayer.checkHandForBook(book1,book2)){
                otherPlayer.bookCards(book1, book2);
                otherPlayer.removeCardFromHand(book1);
                otherPlayer.removeCardFromHand(book2);

                testlog<<otherPlayer.getName()<<" books the "<<book1.rankString(book1.getRank())<<endl;
            }
            gameOver=true;
        }

        testlog<<endl;

        if(currentPlayer.getBookSize()+otherPlayer.getBookSize()==26){
            gameOver=true;
        }


        Player toswap= currentPlayer;
        currentPlayer=otherPlayer;
        otherPlayer=toswap;
    }


    testlog << currentPlayer.getName() <<" has : " << currentPlayer.getBookSize() << endl;
    testlog << otherPlayer.getName() <<" has : " << otherPlayer.getBookSize() << endl;

    if(currentPlayer.getBookSize()>otherPlayer.getBookSize()){
        testlog<<currentPlayer.getName()<< " is the winner with "<<currentPlayer.getBookSize()<< " pairs!";
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
