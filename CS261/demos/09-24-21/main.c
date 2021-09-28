#include <stdio.h> // have to include .h on packages in C
#include <stdlib.h>

struct Pokeman {
    char* name;
    int dexNum;
}; // only data members

void printwhatipass(int x);

int main () {

    int a = 5;
    char* b = "Benny";
    float pi = 3.14;

    printf("Hello World!\n");
    printf("Int a = %d\n", a);
    printf("String b = %s\n", b);
    printf("Float pi = %4.3f\n", pi);
    printf("Char b[2] = %c\n", b[2]);

    printf("1: %d\t 2: %s\t 3: %f\n", a, b, pi);

    printwhatipass(20);

    //if, else if, else, for, while, and do while all work the same still

    struct Pokeman pika = {.name = "Sparky", .dexNum = 25};

    pika.name = "Bolt";

    printf("Pokemon's name: %s\n", pika.name);

    int t = 20;
    int* t_ptr = &t;

    printf("Pointer: %p\n", t_ptr);
    printf("Actual Value: %d\n", *t_ptr);

    void* v_ptr = t_ptr; // generic pointer that will take in any type

    printf("Void Pointer: %p", *(int*)(v_ptr)); // cast to int pointer and then dereference

    v_ptr = &pika;

    printf("%s\n", ((struct Pokeman*) v_ptr)->name);

    struct Pokeman* bulba = malloc(10 * sizeof(struct Pokeman)); // dynamically allocated (always contiguous)
    bulba[0].name = "Flower";

    free(bulba); // works for everything

    //pflukeh@oregonstate.edu

    return 0;
}

void printwhatipass(int x) {
    printf("%d was passed\n", x);
}

// compile with gcc --std=c99 -g <file> or gcc --std=c99 -g -o <file> <name of exe>
// valgrind still works