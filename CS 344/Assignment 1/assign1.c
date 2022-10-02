#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"

void ParseInputFile(char* filePath) {

}

void OpenFile(char* filePath) {
}

void main(int argv, char* argc) {
   int file_descriptor;
   ssize_t nread, nwritten;
   struct stat, st;
   int fsize;

   if (argv != 2) {
      perror("ERROR: Must give data filepath as an argument!");
      exit(1);
   }

   file_descriptor = open(argc[1], O_RDONLY | O_CREAT, 0060);

   stat(argc[1], &st);
   fsize = st.st_size;

   // If the file failed to open, exit!
   if (file_descriptor == -1) {
      printf("open() failed on \"%s\"\n", filePath);
      perror("in OpenFile()");
      exit(1);
   }

   
   close(file_descriptor);
   return(0); 
}
