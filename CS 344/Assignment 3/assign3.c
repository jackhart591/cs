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
int canBg = 0;
int acknowledged = 0;
int instant = 1;
int status = 0;

void freeCommand(struct Command*);

void HandleSigIntParent(int signo) {

   int i;
   for (i = 0; i < MAX_PROCESS; i++) {
      if (fgPids[i] != 0) { // finds a figPid that exists
         const char message[] = "Terminated by signal 2\n";
         write(STDOUT_FILENO, message, sizeof(message)-1);
         kill(fgPids[i], SIGINT);
      }
   }
   
   free(fgPids);
   fgPids = calloc(MAX_PROCESS, sizeof(pid_t)); // reset fgPids list
}

void HandleSigStpParent(int signo) { 
   canBg = (canBg == 0) ? 1 : 0; // toggles foreground mode
   acknowledged = 1;

   if (instant == 0) {
      if (canBg == 1) {
         const char msg[] = "Entering foreground only mode...\n";
         write(STDOUT_FILENO, msg, sizeof(msg)-1);
      } else {
         const char msg[] = "Exiting foreground only mode...\n";
         write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      acknowledged = 0;
   }
}

// Empty method for children that ignore signals
void IgnoreSignal(int signo) {}

// Expands any present variables
char* CheckForExpansion(char* commandText) {
   if (strstr(commandText, "$$") != NULL) { // if commandText contains $$
      char pid[25];
      snprintf(pid, sizeof(pid), "%d", getpid());
      char* newString = malloc(MAX_COMMAND_CHAR);

      int i;
      int j = 0;
      int k = 0;
      for (i = 0; i < MAX_COMMAND_CHAR; i++) {
         if (commandText[i] == '$' && commandText[i+1] == '$') {
            strncpy(newString + k, commandText + j, i-j); // copies everything new before $$
            k += (i-j); // iterates pointer
            newString[k] = '\0'; // adds null char for strcat
            strcat(newString, pid); // appends pid into it
            k += strlen(pid);
            i++;
            j = i+1;
         }

      }

      // Adds any remaining string after all $$ are found
      strcat(newString, commandText + j);
      strcpy(commandText, newString);
      free(newString);
   }

   return commandText;
}

// Handles waiting and parsing user input
struct Command* waitForInput() {
   instant = 0; // Tells SIGTSTP that it can interrupt here
   printf(": ");
   fflush(stdout);
   char* buffer = calloc(MAX_COMMAND_CHAR, sizeof(char));
   char* bufferptr = buffer;
   int offset = 0;
   struct Command* newCommand = malloc(sizeof(struct Command));
   char* commandText = calloc(MAX_COMMAND_CHAR, sizeof(char));

   // Gets the entire input line
   if (fgets(buffer, MAX_COMMAND_CHAR, stdin) == NULL) {
      perror("Error in fgets");
      exit(1);
   }

   // Gets everything until the next space or newline
   if (sscanf(buffer, "%2048s%n", commandText, &offset) < 1) {
      free(newCommand);
      free(commandText);
      return NULL;
   }

   // iterates bufferptr to current position
   bufferptr += offset;

   newCommand->command = malloc(MAX_COMMAND_CHAR * sizeof(char));
   newCommand->numArgs = 0;

   // Parse any $$
   commandText = CheckForExpansion(commandText);
   
   // Sets command variable
   strcpy(newCommand->command, commandText);

   newCommand->args[0] = malloc(MAX_COMMAND_CHAR * sizeof(char));
   strcpy(newCommand->args[0], commandText);
   newCommand->numArgs++;

   // Sets input files to default 0 so can check if they're set
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
         if (checkFinal == 0) { // was the last character an &?
            newCommand->args[i-1] = malloc(MAX_COMMAND_CHAR * sizeof(char));
            strcpy(newCommand->args[i-1], "&");
            checkFinal = 1;
         }
      }

      commandText = CheckForExpansion(commandText);

      bufferptr += offset;
      
      if (nextInput == 0) { // Was the last character a <?
         newCommand->inputFile = open(commandText, O_RDONLY, 0640);
         nextInput = 1;
      } else if (nextOutput == 0) { // was the last character a >?
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

   // Sets last arg as null so exec method knows where to stop
   newCommand->args[newCommand->numArgs] = NULL;

   free(commandText);
   free(buffer);

   instant = 1; // SIGTSTP can no longer interrupt

   return newCommand;
}

int changeDirectory(struct Command* command) {
   if (command->args[1] != NULL) { // if there's a provided directory
      if (chdir(command->args[1]) != 0) {
         perror("Not a valid directory!");
         fflush(stderr);
         return 1;
      }
   } else {
      if (chdir(getenv("HOME")) != 0) {
         perror("Not a valid directory!");
         fflush(stderr);
         return 1;
      }
   }

   return 0;
}

// Prints out status variable which stores the latest
// exit status
int statusCommand(struct Command* command) {
   printf("Exit value %d", status/256);
   fflush(stdout);
   return 0;
}

void exitShell() {
   kill(0, SIGTERM);
   exit(0);
}

// Opens a foreground process
void openFgProcess(struct Command* command, pid_t childId) {
   int i;

   struct sigaction SIGSTP_act = {0};

   SIGSTP_act.sa_handler = IgnoreSignal;
   sigfillset(&SIGSTP_act.sa_mask);
   SIGSTP_act.sa_flags = SA_RESTART;
   sigaction(SIGTSTP, &SIGSTP_act, NULL);

   // If there is an input file
   if (command->inputFile != 0) {

      if (command->inputFile == -1) {
         perror("There was an issue opening the file!");
         fflush(stdout);
         exit(1);
      }     

      int result = dup2(command->inputFile, 0);
      if (result == -1) {
         perror("Error with dup2");
         fflush(stdout);
      }
   }

   // If there is an output file
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
   exit(1); // if process gets here, command didn't work
}

// Opens a background process
void openBgProcess(struct Command* command, pid_t childId) {
   int i, ifd, ofd;

   struct sigaction SIGINT_act = {0};

   SIGINT_act.sa_handler = IgnoreSignal;
   sigfillset(&SIGINT_act.sa_mask);
   SIGINT_act.sa_flags = SA_RESTART;
   sigaction(SIGINT, &SIGINT_act, NULL);

   struct sigaction SIGSTP_act = {0};

   SIGSTP_act.sa_handler = IgnoreSignal;
   sigfillset(&SIGSTP_act.sa_mask);
   SIGSTP_act.sa_flags = SA_RESTART;
   sigaction(SIGTSTP, &SIGSTP_act, NULL);

   if (command->inputFile == 0) { // is there not a input file?
      ifd = open("/dev/null", O_WRONLY);
   } else {
      if (command->inputFile == -1) {
         perror("There was an issue opening this file!\n");
         exit(1);
      }

      ifd = command->inputFile;
   }

   if (command->outputFile == 0) { // is there not an output file?
      ofd = open("/dev/null", O_WRONLY);
   } else {
      ofd = command->outputFile;
   }

   for (i = 0; i < MAX_PROCESS; i++) {
      if (bgPids[i] == 0) {
         bgPids[i] = getpid(); // finds latest elem in list that isn't set

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
         exit(1); // if process reaches here, there was an issue with the command.
      }
   }
}

// Figures out how to execute command
void execCommand(struct Command* command) {
   pid_t spawnpid = fork();
   pid_t childpid;
   int childStatus;

   switch(spawnpid) {
      case -1: // if err
         perror("fork() failed!\n");
         fflush(stdout);
         exit(1);
         break;
      case 0: // if child
         // if isn't background or can't be background
         if (command->background == 1 || canBg == 1) openFgProcess(command, childpid);
         else openBgProcess(command, childpid); // else, open background

         break;
      default: // if parent
         // if isn't background or can't  be background
         if (command->background == 1 || canBg == 1) {
            int i;
            for (i = 0; i < MAX_PROCESS; i++) {
               if (fgPids[i] == 0) { // find latest uninitialized elem in list and init
                  fgPids[i] = spawnpid;
                  break;
               }
            }

            childpid = wait(&childStatus); 
            status = childStatus;

            if (acknowledged == 1) { // acknowledging foreground only mode if necessary
               if (canBg == 1) {
                  printf("Entering foreground only mode...\n");
                  fflush(stdout);
               } else {
                  printf("Exiting foreground only mode...\n");
                  fflush(stdout);
               }
   
               acknowledged = 0;
            }

            fgPids[i] = 0;
            
         // Same stuff for background variant
         } else if (command->background == 0 && canBg == 0) {
            int i;
            for (i = 0; i < MAX_PROCESS; i++) {
               if (bgPids[i] == 0) {
                  bgPids[i] = spawnpid;
                  break;
               }
            }

            printf("Background pid is %d\n", spawnpid);
            fflush(stdout);
         }

         break;
   }

   // Wait for background processes
   int i;
   for (i = 0; i < MAX_PROCESS; i++) {
      if (bgPids[i] != 0) {
         if (waitpid(bgPids[i], &childStatus, WNOHANG) != 0) {
            status = childStatus;
            printf("Background process %d exited with a status code of %d\n", bgPids[i], status);
            fflush(stdout);
            bgPids[i] = 0;
         } 
      }
   }
}

// Frees the command struct
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
   sigaction(SIGTSTP, &SIGSTP_act, NULL);

   while (1) { // Shouldn't exit until specified.
       struct Command* command = waitForInput();
       if (command == NULL) { continue; }

        if (strcmp(command->command, "cd") == 0) {
          status = changeDirectory(command);
        } else if (strcmp(command->command, "status") == 0) {
          status = statusCommand(command);
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
