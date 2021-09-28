#include<stdio.h>
#include<stdlib.h>

void printwhatipass(int x);

int main(){    
    char* name = "Jackson Hart";    
    printf("My name is %s\n", name);    
    printwhatipass(7);    
    printwhatipass(7*2);    
    printwhatipass(7-2);    
    return 0;
}

void printwhatipass(int x){    
        printf("Passed: %d\n", x);
}