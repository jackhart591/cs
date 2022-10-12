#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fcntl.h"
#include "sys/stat.h"

struct movie {
   char* title;
   int year;
   char* langs;
   double rating;
   struct movie* next;
};

void DisplayMenu(struct movie* head);

// Opens the file at the given path. Returns
// a string containing the file's contents.
char* OpenFile(char* filePath) {
   int file_descriptor, fsize;
   ssize_t nread;
   struct stat st;

   file_descriptor = open(filePath, O_RDONLY, 0060);

   stat(filePath, &st);
   fsize = st.st_size; // fsize -> file size

   // If the file failed to open, exit!
   if (file_descriptor == -1) {
      printf("open() failed on \"%s\"\n", filePath);
      perror("in OpenFile()");
      exit(1);
   }

   char* buffer = malloc(fsize + 1);
   nread = read(file_descriptor, buffer, fsize);

   buffer[fsize] = '\0';
   
   close(file_descriptor);
   return buffer;
}

// Creates and returns a movie struct from the given data.
struct movie* createMovie(char* currLine) {
   struct movie* newMovie = malloc(sizeof(struct movie));
   char* savePtr;

   //Title
   char* token = strtok_r(currLine, ",", &savePtr);
   newMovie->title = calloc(strlen(token) + 1, sizeof(char)); // initializes everything to 0s
   strcpy(newMovie->title, token); // Adds a \0 onto the end

   //Year
   token = strtok_r(NULL, ",", &savePtr);
   newMovie->year = atoi(token);

   //Languages
   token = strtok_r(NULL, ",", &savePtr);
   newMovie->langs = calloc(strlen(token) + 1, sizeof(char));
   strcpy(newMovie->langs, token);

   //Rating
   token = strtok_r(NULL, "\n", &savePtr);
   char* eptr = NULL;
   newMovie->rating = strtod(token, &eptr);
   
   return newMovie;
}

// Parses the file line by line into a linked list containing
// movie structs. Returns the head of the linked list. 
struct movie* ParseFile(char* file, char* fileName) {
   char* lineSave;

   struct movie* head = NULL;
   struct movie* current = NULL;
   int i = 0;

   // Gets the header of the CSV file and then the first line
   // of data.
   char* token = strtok_r(file, "\n", &lineSave);
   token = strtok_r(NULL, "\n", &lineSave);
   while (token) {
      struct movie* newMovie = createMovie(token);
      i++;
   
      if (head == NULL) {
         head = newMovie;
         current = head;
      } else {
         current->next = newMovie;
         current = newMovie;
      }
      
      token = strtok_r(NULL, "\n", &lineSave); // Next line
   }

   printf("Processed file %s and parsed data for %d movies\n\n", fileName, i);

   return head;      
}

// Frees every movie in the provided linked list
void freeMovies(struct movie* head) {
   struct movie* current = head;
   struct movie* future = current->next;

   while (current != NULL) {
      future = current->next;
      free(current->title);
      free(current->langs);
      free(current);
      current = future;
   }
}

// Prints the movies released in a given year.
void moviesInYear(struct movie* head) {
   int year;
   struct movie* current = head;
   printf("What year would you like to see movies for?: ");
   scanf("%d", &year);

   int foundOne = 0;
   while (current != NULL) {
      if (current->year == year) {
         printf("%s\n", current->title);
         foundOne = 1;
      }

      current = current->next;
   }

   if (!foundOne) {
      printf("No data was found on movies in this year.\n");
   }

   // Go back to the main menu
   printf("\n");
   DisplayMenu(head);
}

//Prints the highest rated movie in a given year
void ratedInYear(struct movie* head) {
   // A mapping using the year as the key and the rating as the value
   struct movie** rating = calloc(5000, sizeof(struct movie*));
   struct movie* current = head;

   while (current != NULL) {
      if (rating[current->year] == NULL || rating[current->year]->rating < current->rating) {
         rating[current->year] = current;
      }

      current = current->next;
   }

   int i;
   for (i = 0; i < 5000; i++) {
      if (rating[i] != NULL) {
         printf("%d %.1f %s\n", rating[i]->year, rating[i]->rating, rating[i]->title);
      }
   }

   printf("\n");

   free(rating);
   DisplayMenu(head);
}

// Displays all movies of a given language.
void displayByLang(struct movie* head) {
   char* lang = malloc(21 * sizeof(char));
   printf("Enter a language: ");
   scanf("%20s", lang);
   struct movie* current = head;

   int foundOne = 0;
   while (current != NULL) {
      if (strstr(current->langs, lang) != NULL) {
         printf("%d %s\n", current->year, current->title);
         foundOne = 1;
      }

      current = current->next;
   }

   if (!foundOne) {
      printf("There are no movies with this Languague.\n");
   }

   printf("\n");

   free(lang);
   DisplayMenu(head);
}

// Writes out menu
void DisplayMenu(struct movie* head) {
   int selection;
   printf("<1> Show movies released in the specified year\n");
   printf("<2> Show highest rated movie for each year\n");
   printf("<3> Show the title and year of release for all movies in a specified language\n");
   printf("<4> Exit from the program\n");
   scanf("%d", &selection);
   
   switch (selection) {
      case 1:
         moviesInYear(head);
         break;
      case 2:
         ratedInYear(head);
         break;
      case 3:
         displayByLang(head);
         break;
      default:
         printf("Not an option! Try Again!\n");
         DisplayMenu(head);
      case 4:
         return;
   }
}

int main(int argc, char* argv[]) {
   if (argc != 2) {
      perror("ERROR: Must give data filepath as an argument!");
      exit(1);
   }

   char* fContents = OpenFile(argv[1]);
   struct movie* head = ParseFile(fContents, argv[1]);

   DisplayMenu(head);

   free(fContents);
   freeMovies(head);

   return(0); 
}
