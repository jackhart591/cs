#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

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
         largestSize = st.st_size
         fileName = dp->d_name;
      }
   }

   closedir(dir);
}

void smallestFile() {

}

void namedFile() {

}

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

void displayMenu() {
   
   int answer = -1;

   // stuck in menu until user selects 2
   while (1) {
      printf("<1> Select file to process\n");
      printf("<2> Exit the program\n");
      printf("Please enter your selection: ");

      scanf("%d", &answer); 

      switch (answer) {
         case 1:
            displayProcessFile();
            break;
         case 2:
            return;
         default:
            printf("Not a valid selection! Try again!\n");
      }
   }
}

int main() {
   displayMenu();
   return 0;
}
