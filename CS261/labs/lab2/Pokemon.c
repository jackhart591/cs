#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct pokemon {
    char* name;
    int dex_num;
};

struct pokemon* create_poke_array(int num_poke);
void init_poke(struct pokemon* poke_array, int index, char* poke_name, int poke_dex_num);
struct pokemon search_dex_num(int poke_dex_num, struct pokemon* poke_array);
struct pokemon search_name(char* poke_name, struct pokemon* poke_array);
void print_poke(struct pokemon poke);
void free_poke_array(struct pokemon* poke_array);

const int ARR_SIZE = 10;

int main() {

    struct pokemon* arr_poke = create_poke_array(ARR_SIZE);

    for (int i = 0; i < ARR_SIZE; i++) {
        init_poke(arr_poke, i, "Char", 2);
    }

    init_poke(arr_poke, 9, "Bulba", 1);

    print_poke(arr_poke[1]);

    print_poke(search_dex_num(1, arr_poke));
    print_poke(search_name("Bulba", arr_poke));

    free_poke_array(arr_poke);

    return 0;
}

struct pokemon* create_poke_array(int num_poke) {
    struct pokemon* arr_poke = malloc(num_poke * sizeof(struct pokemon));

    return arr_poke;
}

void init_poke(struct pokemon* poke_array, int index, char* poke_name, int poke_dex_num) {
    poke_array[index].name = poke_name;
    poke_array[index].dex_num = poke_dex_num;
}

void print_poke(struct pokemon poke) {
    printf("Pokemon name: %s\n", poke.name);
    printf("Pokemon dex number: %d\n", poke.dex_num);
}

struct pokemon search_dex_num(int poke_dex_num, struct pokemon* poke_array) {
    for(int i = 0; i < ARR_SIZE; i++) {
        if(poke_array[i].dex_num == poke_dex_num) {
            return poke_array[i];
        }
    }
}

struct pokemon search_name(char* poke_name, struct pokemon* poke_array) {
    for(int i = 0; i < ARR_SIZE; i++) {
        if(strcmp(poke_array[i].name, poke_name) == 0) {
            return poke_array[i];
        }
    }
}

void free_poke_array(struct pokemon* poke_array) {
    free(poke_array);
}