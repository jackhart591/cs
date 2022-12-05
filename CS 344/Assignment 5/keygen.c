#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
   srand(time(NULL));
   if (argc != 2) {
      perror("Incorrect amount of arguments!\n");
      return 1;
   }

   int length;
   length = atoi(argv[1]); // Get the second arg as integer

   int i;
   for (i = 0; i < length; i++) {
      int randChar = rand() % 27;
      char newChar;

      if (randChar == 26) {
         newChar = ' ';
      } else {

         newChar = randChar + 'A';
      }

      printf("%c", newChar);
   }

   printf("\n");
}
