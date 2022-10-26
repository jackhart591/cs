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
      return NULL;
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

   newMovie->next = NULL;
   
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

   printf("Processed file %s and parsed data for %d movies\n", fileName, i);

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
void moviesInYear(struct movie* head, int year, char* path) {
   struct movie* current = head;
   int fd = -1;

   int foundOne = 0;
   while (current != NULL) {
      if (current->year == year) {
         char fileName [1034];
         char newline = '\n';
         snprintf(fileName, sizeof(fileName), "%s/%d.txt", path, year);
         if (foundOne == 0) {
            fd = open(fileName, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);  
            write(fd, current->title, strlen(current->title));
            write(fd, &newline, 1);
         } else {
            write(fd, current->title, strlen(current->title));
            write(fd, &newline, 1);
         }
         foundOne = 1;
      }

      current = current->next;
   }

   if (fd != -1) {
      close(fd);
   }
}
