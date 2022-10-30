#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct movie {
    int stuff;
};

struct movie* processFile(char* filePath) {
    FILE* movieFile = fopen(filePath, "r");

    char* currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char* token;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info.csv\n");
        return 1;
    }

    struct movie* movieList = processFile(argv[1]);

    return 0;
}