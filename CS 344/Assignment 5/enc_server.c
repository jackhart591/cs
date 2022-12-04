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

void sendFile(int connectionSocket, const char* file) {
    char buffer[1000];
    int charsWritten = 0;

    // Send the size of the file
    char filesize[10];
    sprintf(filesize, "%d", strlen(file));

    // Tell the socket the size of the file
    SendMsg(connectionSocket, filesize);

    int buffit = 0; // buffer iterator
    do {
        // Clear out the buffer array
        memset(buffer, '\0', sizeof(buffer));

        // Copy the next portion of the string into buffer
        memcpy(buffer, &file[buffit], (strlen(&file[buffit]) >= 999) ? 999 : strlen(&file[buffit]));
        buffer[999] = '\0';

        // Send message to server
        // Write to the server
        charsWritten = send(connectionSocket, buffer, strlen(buffer), 0);
        if (charsWritten < 0) {
            error("CLIENT: ERROR writing to socket");
        }

        buffit += charsWritten;

    } while (buffit < strlen(file));
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
    char* encryptedText = malloc(strlen(text) + 1);

    int i;
    for (i = 0; i < strlen(text); i++) {

        // Get the number of characters in alphabet
        int textCharInt;
        if (text[i] == ' ') {
            textCharInt = 26;
        } else { textCharInt = text[i] - 'A'; }

        printf("Char num: %d\n", textCharInt);

        // Repeat for key
        int keyCharInt;
        if (key[i] == ' ') {
            keyCharInt = 26;
        } else { keyCharInt = key[i] - 'A'; }

        // Encrypt the text
        int newCharInt = textCharInt + keyCharInt;
        if (newCharInt > 26) { newCharInt -= 27; }

        printf("Key num: %d\n", keyCharInt);

        // Parse it into the char
        char newCharChar;
        if (newCharInt == 26) { newCharChar = ' '; }
        else { newCharChar = newCharInt + 'A'; }

        printf("New Num: %d\n", newCharInt);

        encryptedText[i] = newCharChar;
    }

    encryptedText[strlen(text)] = '\0';

    return encryptedText;
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
        char* encryptedFile = encryptFile(text, key);
        sendFile(connectionSocket, encryptedFile);
        free(encryptedFile);
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