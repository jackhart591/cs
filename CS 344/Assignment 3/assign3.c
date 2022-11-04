#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_COMMAND_CHAR 2048
#define MAX_ARGS 514
#define MAX_PROCESS 10000

struct Command {
   char* command;
   char* args[MAX_ARGS];
   int inputFile;
   int outputFile;
   int background;
};

pid_t* fgPids;
pid_t* bgPids;

void HandleSigInt(int signo) {
   int i;
   for (i = 0; i < MAX_PROCESS; i++) {
      if (fgPids[i] != 0) {
         kill(fgPids[i], SIGINT);
         char* message = "Terminated by signal 2\n";
         write(STDOUT_FILENO, message, 24);
      }
   }
   
   free(fgPids);
   fgPids = calloc(MAX_PROCESS, sizeof(pid_t));
}

struct Command* waitForInput() {
   printf(": ");
   fflush(stdout);
   struct Command* newCommand = malloc(sizeof(struct Command));
   char* commandText = calloc(MAX_COMMAND_CHAR, sizeof(char));

   scanf("%2048s", commandText);
   newCommand->command = malloc(MAX_COMMAND_CHAR * sizeof(char));
   
   // Sets command variable
   strcpy(newCommand->command, commandText);

   newCommand->args[0] = malloc(MAX_COMMAND_CHAR * sizeof(char));
   strcpy(newCommand->args[0], commandText);

   newCommand->inputFile = 0;
   newCommand->outputFile = 0;
   int i;
   int nextInput = 1;
   int nextOutput = 1;
   int checkFinal = 1;
   for (i = 1; i < MAX_ARGS + 4; i++) {
      char newLine;
      newLine = getchar();

      if (newLine == '\n') {
         if (checkFinal == 0) newCommand->background = 0;
         else newCommand->background = 1;

         break;
      }

      scanf("%2048s", commandText);
      if (nextInput == 0) {
         newCommand->inputFile = open(commandText, O_WRONLY | O_CREAT | O_TRUNC, 0640);

         if (newCommand->inputFile == -1) {
            perror("There was problem in opening the input file!");
            exit(1);
         }

         nextInput = 1;
         checkFinal = 1;
      } else if (nextOutput == 0) {
         newCommand->outputFile = open(commandText, O_WRONLY | O_CREAT | O_TRUNC, 0640);

         if (newCommand->outputFile == -1) {
            perror("There was a problem in opening the output file!");
            exit(1);
         }

         nextOutput = 1;
         checkFinal = 1;
      } else if (strcmp(commandText, "<") == 0) {
         nextInput = 0;
         checkFinal = 1;
      } else if (strcmp(commandText, ">") == 0) {
         nextOutput = 0;
         checkFinal = 1;
      } else if (strcmp(commandText, "&") == 0) {
         checkFinal = 0;
      } else {
          newCommand->args[i] = malloc(MAX_COMMAND_CHAR * sizeof(char));
          strcpy(newCommand->args[i], commandText);
          checkFinal = 1;
      }
   }

   newCommand->args[i] = NULL;
   free(commandText);

   return newCommand;
}

void changeDirectory(struct Command* command) {
   if (command->args[1] != NULL) {
      if (chdir(command->args[1]) != 0) {
         perror("Couldn't find this directory!");
         fflush(stdout);
      }
   } else {
      if (chdir(getenv("HOME")) != 0) {
         perror("Couldn't find this directory!");
         fflush(stdout);
      }
   }
}

void statusCommand(struct Command* command) {

}

void exitShell() {
   kill(0, SIGTERM);
   exit(0);
}

void openFgProcess(struct Command* command, pid_t childId) {
   int i;
   for (i = 0; i < MAX_PROCESS; i++) {
      if (fgPids[i] == 0) {
         fgPids[i] = childId;
         execvp(command->command, command->args);
         perror("That was not a recognized command!\n");
         fflush(stdout);
         exit(1);
      }
   } 
}

void openBgProcess(struct Command* command, pid_t childId) {
   int i, ifd, ofd;

   if (command->inputFile == 0) {
      ifd = open("/dev/null", O_WRONLY);
   } else {
      ifd = command->inputFile;
   }

   if (command->outputFile == 0) {
      ofd = open("/dev/null", O_WRONLY);
   } else {
      ofd = command->outputFile;
   }

   for (i = 0; i < MAX_PROCESS; i++) {
      printf("bgPid: %d", bgPids[i]);
      fflush(stdout);
      if (bgPids[i] == 0) {
         bgPids[i] = childId;

         printf("Output: %d", command->outputFile);
         fflush(stdout);
         int result = dup2(ifd, 0);
         if (result == -1) {
            perror("Error with dup2");
         }
         
         result = dup2(ofd, 1);
         if (result == -1) {
            perror("Error with dup2");
         }

         execvp(command->command, command->args);
         perror("That was not a recognized command!\n");
         fflush(stdout);
         exit(1);
      }
   }
}

void execCommand(struct Command* command) {
   pid_t spawnpid = fork();
   pid_t childpid;
   int childStatus;

   switch(spawnpid) {
      case -1:
         perror("fork() failed!\n");
         fflush(stdout);
         exit(1);
         break;
      case 0:
         if (command->background == 1) openFgProcess(command, childpid);
         else openBgProcess(command, childpid);

         break;
      default:
         if (command->background == 1) childpid = wait(&childStatus); 
      
         printf("Child %d exited with a status of %d!\n", childpid, childStatus);
         break;
   }

   int i;
   for (i = 0; i < MAX_PROCESS; i++) {
      if (bgPids[i] != 0) {
         waitpid(bgPids[i], &childStatus, WNOHANG);
         if (childStatus != 0) bgPids[i] = 0;
      }
   }
}

void freeCommand(struct Command* command) {
   free(command->command);

   int i;
   for (i = 0; i < MAX_ARGS; i++) {
      if (command->args[i] != NULL) {
         free(command->args[i]);
      }
   }

   if (command->inputFile != 0) {
      close(command->inputFile);
   }

   if (command->outputFile != 0) {
      close(command->outputFile);
   }

   free(command);
}

int main() {

   fgPids = calloc(MAX_PROCESS, sizeof(pid_t));
   bgPids = calloc(MAX_PROCESS, sizeof(pid_t));

   signal(SIGINT, HandleSigInt); // Update this, signal is deprecated!

   while (1) {
       struct Command* command = waitForInput();
       printf("Command: %s, Args: %s\n", command->command, command->args[0]);

       if (strcmp(command->command, "cd") == 0) {
          changeDirectory(command);
       } else if (strcmp(command->command, "status") == 0) {
          statusCommand(command);
       } else if (strcmp(command->command, "exit") == 0) {
          freeCommand(command);
          free(fgPids);
          free(bgPids);
          exitShell();
       } else {
          execCommand(command);
       }

       freeCommand(command);
   }

   return 0;
}
