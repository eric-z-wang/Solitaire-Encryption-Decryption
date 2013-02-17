#ifndef CARD_H
#define CARD_H

struct card {
  int val; /*Value of card*/
  struct card *next; /*Next card in circular list*/
};
typedef struct card Card;

/*Given the head of a circular linked list of cards,
  print each card's value.
*/

void printCardInfo (Card *cardlist);


/*Create a new circular linked list of cards
  with one card of value val.
*/

Card *newCard (int val);


/*Given the head of a circular linked list of cards,
  and the value of a new card, add the new card to the end of cardlist.
*/
  
Card *addTailCard (Card *cardlist, int val);


/*Given the head of a circular linked list of cards,
  and the value of an existing card, swap that card with the next card in cardlist.
*/

Card *swapAfter (Card *cardlist, int val);


/*Given the head of a circular linked list of cards,
  and the value of an existing card, return the position of that card.
*/

int cardPos (Card *cardlist, int val);


/*Given the head of a circular linked list of cards
  and the values of the top and bottom jokers, perform a triple cut.
*/

Card *tripleCut (Card *cardlist, int top, int bot);

/*Given the head of a circular linked list of cards,
  and a position, return the value of the card at that position.
*/

int cardVal (Card *cardlist, int pos);


/*Given the head of a circular linked list of cards,
  insert num top cards above the bottom-most card.
*/

Card *insertBottom (Card *cardlist, int num);


/*Free all memory for all cards in the circular linked list of cards.
*/

void deallocateCards (Card *cardlist);

#endif