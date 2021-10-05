#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    char* a = "This is a string"; 
    /*doing it this way means that individual letters are read-only
    also usually accompanied with const*/
    char b[] = "This is also a string";

    char* c = malloc(128 * sizeof(char)); // this gets around what was discussed above
    c = strncpy(c, a, 128);

    c[2] = 'u';

    printf("a: %s\n", a);
    printf("b: %s\n", b);

    //a[2] = 'u'; cannot do this, segmentation fault
    b[2] = 'u';

    printf("edited b: %s\n", b);
    printf("c: %s\n", c);

    return 0;
}