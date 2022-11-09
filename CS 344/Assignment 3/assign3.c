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
   int numArgs;
   int inputFile;
   int outputFile;
   int background;
};

pid_t* fgPids;
pid_t* bgPids;

void HandleSigIntParent(int signo) {
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

void HandleSigStpParent(int signo) {
   
}

void HandleSigIntChild(int signo) {

}

void HandleSigStpChild(int signo) {

}

void IgnoreSignal(int signo) {}

struct Command* waitForInput() {
   printf(": ");
   fflush(stdout);
   char* buffer = calloc(MAX_COMMAND_CHAR, sizeof(char));
   char* bufferptr = buffer;
   int offset = 0;
   struct Command* newCommand = malloc(sizeof(struct Command));
   char* commandText = calloc(MAX_COMMAND_CHAR, sizeof(char));


   if (fgets(buffer, MAX_COMMAND_CHAR, stdin) == NULL) {
      perror("Error in fgets");
      exit(1);
   }

   if (sscanf(buffer, "%2048s%n", commandText, &offset) < 1) {
      free(newCommand);
      free(commandText);
      return NULL;
   }

   bufferptr += offset;

   newCommand->command = malloc(MAX_COMMAND_CHAR * sizeof(char));
   newCommand->numArgs = 0;

   if (strstr(commandText, "$$") != NULL) {
      char pid[25];
      snprintf(pid, sizeof(pid), "%d", getpid());
      char* newString = malloc(MAX_COMMAND_CHAR);

      int i;
      int j = 0;
      int k = 0;
      for (i = 0; i < MAX_COMMAND_CHAR; i++) {
         if (commandText[i] == '$' && commandText[i+1] == '$') {
            strncpy(newString + k, commandText + j, i-j);
            k += (i-j);
            printf("%s\n", newString);
            newString[k] = '\0';
            strcat(newString, pid);
            k += strlen(pid);
            printf("%s\n", newString);
            i++;
            j = i+1;
         }

      }

      strcat(newString, commandText + j);
      strcpy(commandText, newString);
      free(newString);
   }
   
   // Sets command variable
   strcpy(newCommand->command, commandText);

   newCommand->args[0] = malloc(MAX_COMMAND_CHAR * sizeof(char));
   strcpy(newCommand->args[0], commandText);
   newCommand->numArgs++;

   newCommand->inputFile = 0;
   newCommand->outputFile = 0;
   int i;
   int nextInput = 1;
   int nextOutput = 1;
   int checkFinal = 1;
   for (i = 1; i < MAX_ARGS + 4; i++) {
   
      if (sscanf(bufferptr, "%2048s%n", commandText, &offset) != 1) {
         if (checkFinal == 0) newCommand->background = 0;
         else newCommand->background = 1;

         break;
      } else {
         if (checkFinal == 0) {
            newCommand->args[i] = malloc(MAX_COMMAND_CHAR * sizeof(char));
            newCommand->args[i] = "&";
            i++;
            checkFinal = 1;
         }
      }

      bufferptr += offset;
      
      if (nextInput == 0) {
         newCommand->inputFile = open(commandText, O_WRONLY | O_CREAT | O_TRUNC, 0640);

         if (newCommand->inputFile == -1) {
            perror("There was problem in opening the input file!");
            exit(1);
         }

         nextInput = 1;
      } else if (nextOutput == 0) {
         newCommand->outputFile = open(commandText, O_WRONLY | O_CREAT | O_TRUNC, 0640);

         if (newCommand->outputFile == -1) {
            perror("There was a problem in opening the output file!");
            exit(1);
         }

         nextOutput = 1;
      } else if (strcmp(commandText, "<") == 0) {
         nextInput = 0;
      } else if (strcmp(commandText, ">") == 0) {
         nextOutput = 0;
      } else if (strcmp(commandText, "&") == 0) {
         checkFinal = 0;
      } else {
         newCommand->args[i] = malloc(MAX_COMMAND_CHAR * sizeof(char));
         strcpy(newCommand->args[i], commandText);
         newCommand->numArgs++;
      }
   }

   newCommand->args[i] = NULL;

   free(commandText);
   free(buffer);

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

   struct sigaction SIGINT_act = {0};

   SIGINT_act.sa_handler = HandleSigIntChild;
   sigfillset(&SIGINT_act.sa_mask);
   SIGINT_act.sa_flags = 0;
   sigaction(SIGINT, &SIGINT_act, NULL);

   struct sigaction SIGSTP_act = {0};

   SIGSTP_act.sa_handler = HandleSigStpChild;
   sigfillset(&SIGSTP_act.sa_mask);
   SIGSTP_act.sa_flags = 0;
   //sigaction(SIGSTP, &SIGSTP_act, NULL);

   for (i = 0; i < MAX_PROCESS; i++) {
      if (fgPids[i] == 0) {
         fgPids[i] = childId;

         if (command->inputFile != 0) {
            int result = dup2(command->inputFile, 0);
            if (result == -1) {
               perror("Error with dup2");
               fflush(stdout);
            }
         }


         if (command->outputFile != 0) {
            int result = dup2(command->outputFile, 1);
            if (result == -1) {
               perror("Error with dup2");
               fflush(stdout);
            }
         }

         execvp(command->command, command->args);
         perror("That was not a recognized command!\n");
         fflush(stdout);
         exit(1);
      }
   } 
}

void openBgProcess(struct Command* command, pid_t childId) {
   int i, ifd, ofd;

   struct sigaction SIGINT_act = {0};

   SIGINT_act.sa_handler = HandleSigIntChild;
   sigfillset(&SIGINT_act.sa_mask);
   SIGINT_act.sa_flags = 0;
   sigaction(SIGINT, &SIGINT_act, NULL);

   struct sigaction SIGSTP_act = {0};

   SIGSTP_act.sa_handler = HandleSigStpChild;
   sigfillset(&SIGSTP_act.sa_mask);
   SIGSTP_act.sa_flags = 0;
   //sigaction(SIGSTP, &SIGSTP_act, NULL);

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

         int result = dup2(ifd, 0);
         if (result == -1) {
            perror("Error with dup2");
            fflush(stdout);
         }
         
         result = dup2(ofd, 1);
         if (result == -1) {
            perror("Error with dup2");
            fflush(stdout);
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
      
         //printf("Child %d exited with a status of %d!\n", childpid, childStatus);
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
   for (i = 0; i < command->numArgs; i++) {
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

   struct sigaction SIGINT_act = {0};

   SIGINT_act.sa_handler = HandleSigIntParent;
   sigfillset(&SIGINT_act.sa_mask);
   SIGINT_act.sa_flags = SA_RESTART;
   sigaction(SIGINT, &SIGINT_act, NULL);

   struct sigaction SIGSTP_act = {0};

   SIGSTP_act.sa_handler = HandleSigStpParent;
   sigfillset(&SIGSTP_act.sa_mask);
   SIGSTP_act.sa_flags = SA_RESTART;
   //sigaction(SIGSTP, &SIGSTP_act, NULL);

   while (1) {
       struct Command* command = waitForInput();
       if (command == NULL) { continue; }
       //printf("Command: %s, Args: %s\n", command->command, command->args[1]);

        if (strcmp(command->command, "cd") == 0) {
          changeDirectory(command);
        } else if (strcmp(command->command, "status") == 0) {
          statusCommand(command);
        } else if (strcmp(command->command, "exit") == 0) {
          freeCommand(command);
          free(fgPids);
          free(bgPids);
          exitShell();
        } else if (command->command[0] == '#') {
          continue;
        } else {
          execCommand(command);
        }

       freeCommand(command);
   }

   return 0;
}
