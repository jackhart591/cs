#include <stdio.h>
#include <stdlib.h>

void print_int(void* x);
void inception(void* a, void (*fp)(void*));
int compare_int(void* a, void* b);

struct Pokemon {
    char* name;
    int dex_num;
};

int main() {
    void* funk; // pointer to function, basically a delegate
    funk = &print_int;
    int x = 10;
    inception(&x, print_int);
    return 0;
}

void print_int(void* x) { 
    int* x_int = (int*)(x); 
    printf("Passed: %d\n", *(int*)x); 
}

void inception(void* a, void (*fp)(void*)) {
    fp(a);
}

void sort_duo(void* a1, void* b1, int (*compare)(void* a, void* b)) {
    if (!compare(a1, b1)) {
        void* temp = a1;
        a1 = b1;
        b1 = temp;
        printf("Swapped!");
    }
}

int compare_int(void* a, void* b) {
    int* a_int = a;
    int* b_int = b;

    if (*a_int > *b_int) {
        return 1;
    } else {
        return 0;
    }
}