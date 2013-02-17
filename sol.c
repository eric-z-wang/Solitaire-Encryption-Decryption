#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "card.h"
#include "reading.h"


#define MAX_LEN 80 /*Maximum length of message*/ 


/*Given the head of a circular linked list of cards, 
  generate the next keystream value
  and store it in the memory pointed to by bit.
*/

Card *nextRound (Card *deck, int *bit) {
  /*Using the head, does one round of solitaire encryption.*/
  
  Card *head = deck;
  head = swapAfter(head, 27);
  head = swapAfter(head, 28);
  head = swapAfter(head, 28);
  if (cardPos(head, 28) > cardPos(head, 27)){
    head = tripleCut(head, 27, 28);
  }
  else{
    head = tripleCut(head, 28, 27);
  }
  if (cardVal(head, 28) == 28){
    head = insertBottom(head, 27);
  }
  else{
    head = insertBottom(head, cardVal(head, 28));
  }
  if (cardVal(head, 1) == 28){
    if ((cardVal(head, 28) == 28) || (cardVal(head, 28) == 27)){
      return nextRound(head, bit);
    }
    else{
      *bit = cardVal(head, cardVal(head, 1));
      return head;
    }
  }
  else{
    if ((cardVal(head, cardVal(head, 1) + 1) == 28) || (cardVal(head, cardVal(head, 1) + 1) == 27)){
      return nextRound(head, bit);
    }
    else{
      *bit = (cardVal(head, cardVal(head, 1) + 1));
      return head;
    }
  }
}


/*Given a deck filename, a message filename, and a mode
  ('e' or 'd'), encrypt or decrypt the messages using the deck.
  Output the processed messages on standard output, one per line.
*/

void process (char *deckfname, char *msgfname, char mode) {
    int i;
    int j;
    int k;
    int counter;
    char str[MAX_LEN];
    int *bit = malloc(sizeof(int));
    int *bitArray = malloc(sizeof(int)*MAX_LEN);
    int *resultArray = malloc(sizeof(int)*MAX_LEN);
    int *list = malloc(sizeof(int)*MAX_LEN);
    
    
    Card *deck = readDeck(deckfname);
    FILE *fp = fopen(msgfname, "r");
  
    while (!feof(fp)){
      readLine(fp, str, MAX_LEN);
      for (i=0; i < strlen(str); i++){
	int num = str[i] - 64;
	list[i] = num;
      }
      for (j=0; j < i; j++){
	deck = nextRound(deck, bit);
	bitArray[j] = *bit;
      }
      if (mode == 'e'){
	for (k=0; k < j; k++){
	  int sub = list[k] + bitArray[k];
	  if (sub <= 26){
	    resultArray[k] = sub;
	  }
	  else{
	    resultArray[k] = sub % 26;
	  }
	}
      }
      else if (mode == 'd'){
	for (k=0; k < j; k++){
	  if (bitArray[k] >= list[k]){
	    int sub = (list[k] + 26) - bitArray[k];
	    resultArray[k] = sub;
	  }
	  else{
	    int sub = list[k] - bitArray[k];
	    resultArray[k] = sub;
	  }
	}
      }
      for(counter = 0; counter < k; counter++){
	char converted = resultArray[counter] + 64;
	printf("%c", converted);
      }
      printf("\n");
    }
    fclose(fp);		//closes and frees memory.
    free(bitArray);
    free(resultArray);
    free(list);
    free(bit);
    deallocateCards(deck);
}

int main(int argc, char *argv[]) {
   int opt;
   char *deckfname[PATH_MAX] = {0}, *msgfname[PATH_MAX] = {0};
   FILE *fp;
   char mode = 'z'; /*Invalid mode*/
	if (argc == 1){ 	//check if commands are given by checking if argc is 1.
   		perror("No commands were entered.\n");
   		exit(1);
   }

   /*Obtain and validate commandline args*/
   while ((opt = getopt (argc, argv, "d:m:ED")) != -1){		//Looping over all the commands
   		switch (opt){										//and their options.
   			case 'd':
   				if ((fp = fopen(optarg, "r")) == NULL){
   					perror("Deck file does not exist.\n"); 	//If deck file does not exit, exit.
   					exit(1);
   				}
   				else{
   					deckfname[0] = optarg;
   					break;
   					}
   			case 'm':
   				if ((fp = fopen(optarg, "r")) == NULL){		//If message file does not exit, exit.
   					perror("Message file does not exist.\n");
   					exit(1);
   				}
   				else{
   					msgfname[0] = optarg;
   					break;
   				}
   			case 'E':
   				mode = 'e';
   				break;
   			case 'D':
   				mode = 'd';
   				break;
   			case '?':
   				perror("Please enter valid commands.\n");
   				exit(1);
   			default:
   				exit(1);
   		}
   }

   process (deckfname[0], msgfname[0], mode); //Calls process with valid parameters.
   fclose(fp);
   return 0;
  
 }