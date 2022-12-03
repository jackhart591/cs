#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char* msg) {
    perror(msg);
}

void SendMsg(int socket, const char* msg) {
    int charsSent;
    charsSent = send(socket,
                    msg, strlen(msg), 0);

    if (charsSent < 0) {
        error("ERROR writing to socket");
    }
}

void setupAddressStruct(struct sockaddr_in* address, int portNumber) {

    // Clear out the address struct
    memset((char*) address, '\0', sizeof(*address));

    // The address should be network capable
    address->sin_family = AF_INET;
    // Store the port number
    address->sin_port = htons(portNumber);
    // Allow a client at any address to connect to this server
    address->sin_addr.s_addr = INADDR_ANY;
}

char* recieveFile(int connectionSocket) {
    int charsRead, totalRead = 0;
    char buffer[1000];
    char* sendStr = NULL;

    // Get filesize so we know when to stop
    char filesizestr[10];
    charsRead = recv(connectionSocket, filesizestr, 10, 0);

    if (charsRead < 0) {
        error("ERROR reading file size from socket!");
    }

    int filesize = atoi(filesizestr);

    // Start reading the message
    while (totalRead < filesize) {
        // Get the message from the client and display it
        memset(buffer, '\0', sizeof(buffer));

        // If the remaining bytes is less than size of buffer, don't overread
        int recvSize = (filesize - totalRead < sizeof(buffer)) ? filesize - totalRead : sizeof(buffer);

        // Read the client's message from the socket
        charsRead = recv(connectionSocket, buffer, recvSize, 0);

        if (charsRead < 0) {
            error("ERROR reading from the socket");
        } else if (charsRead == 0) { // If there wasn't anything sent
            break;
        }

        // Make some space for the incoming string
        if (sendStr == NULL) {
            sendStr = malloc(strlen(buffer) + 1);
            sendStr[0] = '\0';
        } else { 
            sendStr = realloc(sendStr, strlen(sendStr) + recvSize + 1); 
        }

        strcat(sendStr, buffer);
        totalRead += charsRead;

    } 

    return sendStr;
}

char* encryptFile(char* text, char* key) {

}

void childProcess(int connectionSocket) {
    char* text = NULL;
    char* key = NULL;
    int charsSent;

    text = recieveFile(connectionSocket);
    key = recieveFile(connectionSocket);
    printf("SERVER: I recieved this from the client: \"%s\"\n", text);
    printf("\n\nSERVER: I recieved this from the client: \"%s\"\n", key);
    //Send a success message back to the client
    SendMsg(connectionSocket, "I am the server, and I got your message");

    if (strlen(text) <= strlen(key)) {
        encryptFile(text, key);
    } else {
        SendMsg(connectionSocket, "SERVER ERROR: Key's length must be at least as large as the file's length!");
    }

    free(text);
    free(key);
    close(connectionSocket);
}

int main(int argc, char* argv[]) {
    int connectionSocket, numChildren;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t sizeOfClientInfo = sizeof(clientAddress);

    // Check args
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s port\n", argv[0]);
        exit(1);
    }

    // Create the socket that will listen for connections
    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0) {
        error("ERROR opening socket");
        exit(1);
    }

    // Set up the address struct for the server socket
    setupAddressStruct(&serverAddress, atoi(argv[1]));

    // Associate the socket to the port
    if (bind(listenSocket,
        (struct sockaddr*) &serverAddress,
        sizeof(serverAddress)) < 0) {
            error("ERROR on binding");
            exit(1);
        }

    // Start listening for connections. Allow up to 5 connections to queue up
    listen(listenSocket, 5);

    numChildren = 0;

    // Accept a connection, blocking if one is not available until one connects
    while (1) {
        int childStatus;

        // hang if there's too many people
        if (numChildren == 5) {
            wait(&childStatus);
            numChildren--;
        }
        
        // Accept the connection request which creates a connection socket
        if (numChildren == 0) { // If there isn't any connection, wait until there is one

            // Unsets the non-blocking flag on the socket
            // This code snippet was repurposed from https://stackoverflow.com/questions/388434/linux-fcntl-unsetting-flag
            int flags = fcntl(listenSocket, F_GETFL);
            fcntl(listenSocket, F_SETFL, flags & ~O_NONBLOCK);

            connectionSocket = accept(listenSocket,
                            (struct sockaddr*) &clientAddress,
                            &sizeOfClientInfo);

            // Sets the socket as non-blocking
            // This code snippet was copied from https://stackoverflow.com/questions/14729007/i-want-to-make-accept-system-call-as-non-blocking-how-can-i-make-accept-system
            flags = fcntl(listenSocket, F_GETFL, 0);
            fcntl(listenSocket, F_SETFL, flags | O_NONBLOCK);
            
        } else { // if there is a connection, then this shouldn't block
            connectionSocket = accept4(listenSocket,
                            (struct sockaddr*) &clientAddress,
                            &sizeOfClientInfo,
                            SOCK_NONBLOCK);

            if (connectionSocket < 0) {
                continue;
            }
        }

        if (connectionSocket < 0) {
            error("ERROR on accept");
        }

        pid_t spawnpid = fork();

        switch(spawnpid) {
            case -1: // if err
                perror("fork() failed!\n");
                fflush(stderr);
                exit(1);
            case 0: // if child
                childProcess(connectionSocket);
                exit(0);
            default: // if parent
                numChildren++;
                break;
        }

        if (numChildren > 0) {
            if (waitpid(0, &childStatus, WNOHANG) != 0) {
                numChildren--;
            }
        }
    }

    // Close the listening socket
    return 0;
}