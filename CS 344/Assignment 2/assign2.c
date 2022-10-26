#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "assign1.h"

// Processes the given file, creates a new directory,
// and prints the results out into txt files.
void processFile(char* fileName) {
   char* content = OpenFile(fileName);
   
   if (content == NULL) {
      perror("That wasn't a valid file!\n");
      return;
   }

   struct movie* head = ParseFile(content, fileName);
   int randNum = random() % 100000;
   
   // Parses string so that it is of proper format
   char newFile [1024];
   snprintf(newFile, sizeof(newFile), "./hartjack.movies.%d", randNum);

   mkdir(newFile, 0750);

   printf("Created directory with the name %s\n\n", newFile);
   
   int i;
   for (i = 0; i < 5000; i++) {
      moviesInYear(head, i, newFile);
   }

   // free all the memory
   freeMovies(head);
   free(content);
}

// Gets the largest file's name and processes it.
void largestFile() {
   DIR* dir;
   struct dirent* dp;
   char* fileName;

   // Got this if statement and the while statement from C docs
   if ((dir = opendir(".")) == NULL) {
      perror("Couldn't open .!");
   }

   int largestSize = -1;
   while ((dp = readdir(dir)) != NULL) {
      struct stat st;
      stat(dp->d_name, &st);
   
      if (largestSize <= st.st_size) {
         char prefix [8];
         memcpy(prefix, dp->d_name, 7); // Gets first 6 characters (looking for movies_)
         prefix[7] = '\0';
         const char* postfix = &dp->d_name[strlen(dp->d_name)-4]; // Gets last 4 characters (looking for .csv)
         if (strcmp(prefix, "movies_") == 0 && strcmp(postfix, ".csv") == 0) {
             largestSize = st.st_size;
             fileName = dp->d_name;
         }
      }
   }

   processFile(fileName);
   closedir(dir);
}

// Gets the smallest file's name and processes it.
void smallestFile() {
   DIR* dir;
   struct dirent* dp;
   char* fileName;

   if ((dir = opendir(".")) == NULL) {
      perror("Couldn't open .!");
   }

   int smallestSize = INT_MAX;
   while ((dp = readdir(dir)) != NULL) {
      struct stat st;
      stat(dp->d_name, &st);

      if (smallestSize > st.st_size) {
         char prefix [8];
         memcpy(prefix, dp->d_name, 7); // Gets the first 6 characters (looking for movies_)
         prefix[7] = '\0';
         const char* postfix = &dp->d_name[strlen(dp->d_name)-4]; // Gets the last 4 characters (looking for .csv)
         if (strcmp(prefix, "movies_") == 0 && strcmp(postfix, ".csv") == 0) {
            smallestSize = st.st_size;
            fileName = dp->d_name;
         }
      }
   }

   processFile(fileName);
   closedir(dir);
}

// Asks the user for a file name and attempts to process
// that file.
void namedFile() {
   char fileName [1024];
   printf("What file would you like to process? - ");
   scanf("%s", fileName);

   processFile(fileName);
}

// Displays process file menu.
void displayProcessFile() {

   int answer = -1;

   while (answer <= 0 || answer > 3) {
      printf("\nWhich file would you like to process?\n");
      printf("<1> Pick the largest file\n");
      printf("<2> Pick the smallest file\n");
      printf("<3> Specify the name of the file\n");
      printf("Please enter your selection: ");
      scanf("%d", &answer);

      switch (answer) {
         case 1:
            largestFile();
            break;
         case 2:
            smallestFile();
            break;
         case 3:
            namedFile();
            break;
         default:
            printf("Not a valid selection! Try again!\n");
      }
   }
}

// Displays main menu.
void displayMenu() {
   
   int answer = -1;

   // stuck in menu until user selects 2
   while (1) {
      printf("\n<1> Select file to process\n");
      printf("<2> Exit the program\n");
      printf("Please enter your selection: ");

      scanf("%d", &answer); 

      switch (answer) {
         case 1:
            displayProcessFile();
            break;
         case 2:
            return; // only returns in this case.
         default:
            printf("Not a valid selection! Try again!\n");
      }
   }
}

int main() {
   srandom(time(NULL));
   displayMenu();
   return 0;
}
