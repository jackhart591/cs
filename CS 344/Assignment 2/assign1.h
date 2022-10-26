#ifndef ASSIGN1_INCLUDED
#define ASSIGN1_INCLUDED

struct movie {
   char* title;
   int year;
   char* langs;
   double rating;
   struct movie* next;
};

char* OpenFile(char*);
struct movie* ParseFile(char*, char*);

#endif
