#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reading.h"


/*Read all cards from deck filename and return them as a circular linked list.
*/

Card *readDeck (char *filename) {
  FILE *fp;
  int c;
  fp = fopen(filename, "r");
  fscanf (fp, "%d", &c);	//Get the integers one by one from filestream
  Card *head = newCard(c);
  fscanf (fp, "%d", &c);
  while (!feof(fp)){
    head = addTailCard(head, c);
    fscanf (fp, "%d", &c);
  }
  fclose(fp);
  return head;
}
/*Read and store a line from message fp into str.
  Store at most n characters. Discard non-letters and convert
  letters to uppercase. str should always be a valid string.
*/

int readLine(FILE *fp, char str[], int n) {
  if (!feof(fp)){
    char c;
    int i = 0;
    while (((c = fgetc(fp)) != EOF) && c != '\n' && i < n){
      if (isalpha(c)){
		str[i] = (int)toupper(c);
		i++;
      }
    }
    str[i++] = '\0'; //str is a character array, we need a null character at the end.
    return i - 1;
  }
  else{
    str[0] = '\0';
    return 0;
  }
}