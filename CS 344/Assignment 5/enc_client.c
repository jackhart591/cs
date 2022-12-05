#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>

void error(const char* msg) {
    perror(msg);
    exit(0);
}

void SendMsg(int socket, const char* msg) {
    int charsSent;
    charsSent = send(socket,
                    msg, strlen(msg), 0);

    if (charsSent < 0) {
        error("ERROR writing to socket");
    }
}

int isValidText(char* file) {
    int i;
    for (i = 0; i < strlen(file); i++) {
        if ((file[i] < 'A' || file[i] > 'Z') && file[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

// Opens the file at the given path. Returns
// a string containing the file's contents.
char* OpenFile(char* filePath) {
   int file_descriptor, fsize;
   ssize_t nread;
   struct stat st;

   file_descriptor = open(filePath, O_RDONLY, 0060);

   stat(filePath, &st);
   fsize = st.st_size; // fsize -> file size

   // If the file failed to open, exit!
   if (file_descriptor == -1) {
      printf("open() failed on \"%s\"\n", filePath);
      perror("in OpenFile()");
      exit(1);
   }

   char* buffer = malloc(fsize + 1);
   nread = read(file_descriptor, buffer, fsize);

   buffer[fsize] = '\0';

   close(file_descriptor);

    if (isValidText(buffer)) {
        return buffer;
    } else {
        perror("Your file had bad characters!");
        exit(1);
    }

}

void setupAddressStruct(struct sockaddr_in* address, int portNumber, char* hostName) {

    // Clear out the address struct
    memset((char*) address, '\0', sizeof(*address));

    // The address should be network capable
    address->sin_family = AF_INET;
    // Store the port number
    address->sin_port = htons(portNumber);

    // Get the DNS entry for this host name
    struct hostent* hostInfo = gethostbyname(hostName);
    if (hostInfo == NULL) {
        fprintf(stderr, "CLIENT: ERROR, no such host\n");
        exit(0);
    }

    // Copy the first IP address from the DNS entry to sin_addr.s_addr
    memcpy((char*) &address->sin_addr.s_addr,
            hostInfo->h_addr_list[0],
            hostInfo->h_length);
}

char* recieveFile(int connectionSocket) {
    int charsRead, totalRead = 0;
    char buffer[1000];
    char* sendStr = NULL;

    printf("getting filesize\n");

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

void SendFile(int socketFD, char* file) {
    char buffer[1000];
    int charsWritten = 0;

    // Send the size of the file
    char filesize[10];
    sprintf(filesize, "%d", strlen(file));
    charsWritten = send(socketFD, filesize, 10, 0);

    if (charsWritten != 10) {
        error("CLIENT: ERROR sending filesize to socket!");
    }

    int buffit = 0;
    do {
        // Clear out the buffer array
        memset(buffer, '\0', sizeof(buffer));

        // Copy the next portion of the string into buffer
        memcpy(buffer, &file[buffit], (strlen(&file[buffit]) >= 999) ? 999 : strlen(&file[buffit]));
        buffer[999] = '\0';

        // Send message to server
        // Write to the server
        charsWritten = send(socketFD, buffer, strlen(buffer), 0);
        if (charsWritten < 0) {
            error("CLIENT: ERROR writing to socket");
        }

        buffit += charsWritten;

    } while (buffit < strlen(file));
}


int main(int argc, char* argv[]) {
    int socketFD, portNumber, charsWritten, charsRead;
    struct sockaddr_in serverAddress;
    char buffer[1000];

    // check args
    if (argc < 4) {
        fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);
        exit(0);
    }

    // Opening plaintext file
    char* plaintext = OpenFile(argv[1]);

    // Opening keygen file
    char* key = OpenFile(argv[2]);

    // Create a socket
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        error("CLIENT: ERROR opening socket");
    }

    // Set up the server address struct
    setupAddressStruct(&serverAddress, atoi(argv[3]), "localhost");

    // Connect to server
    if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        error("CLIENT: ERROR connecting");
    }

    char server[11];
    fflush(stdout);
    charsRead = recv(socketFD, server, 10, 0);

    fflush(stdout);
    // Check to see if this server is the encryption server
    if (charsRead != 10 || strcmp(server, "enc_server") != 0) {
        fflush(stdout);
        close(socketFD);
        perror("Cannot connect to this server!");
        exit(2);
    }

    SendMsg(socketFD, "Ready");

    SendFile(socketFD, plaintext);
    SendFile(socketFD, key);

    // Get return message from server
    // Clear out the buffer again to reuse
    memset(buffer, '\0', sizeof(buffer));

    printf("Going dark\n");

    char* encryption = recieveFile(socketFD);

    printf("CLIENT: Here is the encryption: %s\n", encryption);

    free(encryption);

    // Close the socket
    close(socketFD);
    return 0;
}