#include <stdio.h>
#include <stdlib.h>
#include "card.h"


/*Given the head of a circular linked list of cards,
  print each card's value on the same line separated by spaces.
  After printing the card values,  advance to the next line.
*/

void printCardInfo (Card *cardlist) {
  if (!cardlist)
    return;
  Card *head = cardlist;
  do {
    printf ("%d ", cardlist->val);
    cardlist = cardlist->next;
  } while (cardlist != head);
  printf ("\n");
}


/*Create a new circular linked list of cards
  with one card of value val.
  Since the list is circular,  the next pointer refers back to the val card.
*/

Card *newCard (int val) {
  struct card *node;
  node = malloc (sizeof(struct card));
  node->val = val;
  node->next = node;
  return node;
}


/*Given the head of a circular linked list of cards,
  and the value of a new card, add the new card to the list of cards.
*/

Card *addTailCard (Card *cardlist, int val) {
  Card *head = cardlist;
  while (cardlist->next != head){
     cardlist = cardlist->next;
  }
  cardlist->next = newCard(val);
  cardlist->next->next = head;
  return head;
}


/*Given the head of a circular linked list of cards,
  and the value of a card, return the card prior to that card.
  That is, the next pointer of the returned card is card with value val.
  If val is not found, return NULL.
*/

Card *findCard (Card *cardlist, int val) {
  Card *head = cardlist;
  while (cardlist->next->val != val){
    if (cardlist->next == head){
      return NULL;
    }
    cardlist = cardlist->next;
  } 
  return cardlist;
}


/*Given the head of a circular linked list of cards,
  and the value of an existing card, swap that card with the next card in cardlist.
  Return the (possibly different) head of the list of cards.
*/

Card *swapAfter (Card *cardlist, int val) {
  Card *head = cardlist;
  Card *targetcard = findCard(cardlist, val)->next;
  if (targetcard->next == head){
     head = targetcard;
  }
  else if (head->val == val){
    head = head->next;
  }
  while (cardlist->next != targetcard){
    cardlist = cardlist->next;
  }
  Card *aftertarget = targetcard->next;
  targetcard->next = targetcard->next->next;
  aftertarget->next = targetcard;
  cardlist->next = aftertarget;
  return head;
}


/*Given the head of a circular linked list of cards,
  and the value of an existing card, return the position of that card.
  The top card has position 1.
*/

int cardPos (Card *cardlist, int val) {
	int index = 1;
	while (cardlist->val != val){
		cardlist = cardlist->next;
		index ++;
	}
  return index;
}


/*Given the head of a circular linked list of cards
  and the values of the top and bottom jokers, perform a triple cut.
*/

Card *tripleCut (Card *cardlist, int top, int bot) {
  Card *head;
  if ((cardPos(cardlist, top) == 1) && (cardPos(cardlist, bot) == 28)) {
    return cardlist;
  }
  else if (cardPos(cardlist, top) == 1){
    head = findCard(cardlist, bot)->next->next;
    return head;
  }
  else if (cardPos(cardlist, bot) == 28){
    head = findCard(cardlist, top)->next;
    return head;
  }
  else{
    Card *top_joker = findCard(cardlist, top);
    Card *bot_joker = findCard(cardlist, bot);
    Card *head = cardlist;
    while (cardlist->next != head){
      cardlist = cardlist->next;
    }
    Card *bot_card = cardlist;
    Card *new_head = bot_joker->next->next;
    bot_joker->next->next = head;
    bot_card->next = top_joker->next;
    head = new_head;
    top_joker->next = head;
    return head;
  }
}


/*Given the head of a circular linked list of cards,
  and a position, return the value of the card at that position.
  The top card is at position 1.
*/

int cardVal(Card *cardlist, int pos) {
	int index = 1;
	while (index != pos){
		cardlist = cardlist->next;
		index++;
	}
  return cardlist->val;
}


/*Given the head of a circular linked list of cards,
insert num top cards above the bottom-most card.
*/

Card *insertBottom (Card *cardlist, int num) {
  if (num >= 27){
    return cardlist;
  }
  int index = 1;
  Card *head = cardlist;
  while (cardlist->next->next != head){
    cardlist = cardlist->next;
  }
  Card *before_bot_card = cardlist;
  Card *bot_card = before_bot_card->next;
  cardlist = head;
  while (index < num){
    index ++;
    cardlist = cardlist->next;
  }
  Card *new_head = cardlist->next;
  before_bot_card->next = head;
  cardlist->next = bot_card;
  bot_card->next = new_head;
  head = new_head;
  return head;
}

/*Free all memory for all cards in the circular linked list of cards.
*/

void deallocateCards (Card *cardlist) {
  Card *head = cardlist;
  cardlist = cardlist->next;
  while (cardlist != head){
    Card *buffer = cardlist;
    cardlist = cardlist->next;
    free ( buffer );
  }
  free ( head );
  return;
}