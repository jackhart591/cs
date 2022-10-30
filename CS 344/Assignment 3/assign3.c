#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

#define MAX_COMMAND_CHAR 2048
#define MAX_ARGS 512

struct Command {
   char* command;
   char* args[MAX_ARGS];
   char* inputFile;
   char* outputFile;
   int background;
};

DIR* currentDirectory;

struct Command* waitForInput() {
   printf(": ");
   fflush(stdout);
   struct Command* newCommand = malloc(sizeof(struct Command));
   char* commandText = calloc(MAX_COMMAND_CHAR, sizeof(char));

   scanf("%2048s", commandText);
   newCommand->command = malloc(MAX_COMMAND_CHAR * sizeof(char));
   
   // Sets command variable
   strcpy(newCommand->command, commandText);

   newCommand->inputFile = malloc(MAX_COMMAND_CHAR * sizeof(char));
   newCommand->outputFile = malloc(MAX_COMMAND_CHAR * sizeof(char));

   int i;
   int nextInput = 1;
   int nextOutput = 1;
   for (i = 0; i < MAX_ARGS + 4; i++) {
      char newLine;
      newLine = getchar();

      if (newLine == '\n') {
         break;
      }

      scanf("%2048s", commandText);
      if (nextInput == 0) {
         strcpy(newCommand->inputFile, commandText);
         nextInput = 1;
      } else if (nextOutput == 0) {
         strcpy(newCommand->outputFile, commandText);
         nextOutput = 1;
      } else if (strcmp(commandText, "<") == 0) {
         nextInput = 0;
      } else if (strcmp(commandText, ">") == 0) {
         nextOutput = 0;
      } else {
          newCommand->args[i] = malloc(MAX_COMMAND_CHAR * sizeof(char));
          strcpy(newCommand->args[i], commandText);
      }

   }

   return newCommand;
}

void changeDirectory(struct Command* command) {
   if (command->args[0] != NULL) {
      if (chdir(command->args[0]) != 0) {
         perror("Couldn't find this directory!");
      }
   } else {
      if (chdir(getenv("HOME")) != 0) {
         perror("Couldn't find this directory!");
      }
   }
}

void statusCommand(struct Command* command) {

}

void exitShell() {

}

void execCommand(struct Command* command) {

}

int main() {

   while (1) {
       struct Command* command = waitForInput();
       printf("Command: %s, Args: %s\n", command->command, command->args[0]);

       if (strcmp(command->command, "cd") == 0) {
          changeDirectory(command);
       } else if (strcmp(command->command, "status") == 0) {
          statusCommand(command);
       } else if (strcmp(command->command, "exit") == 0) {
          exitShell();
       } else {
          execCommand(command);
       }
   }

   return 0;
}
