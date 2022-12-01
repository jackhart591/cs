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
   return buffer;
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


int main(int argc, char* argv[]) {
    int socketFD, portNumber, charsWritten, charsRead;
    struct sockaddr_in serverAddress;
    char buffer[1024];

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

    int buffit = 0;
    do {
        // Clear out the buffer array
        memset(buffer, '\0', sizeof(buffer));

        // Copy the next portion of the string into buffer
        memcpy(buffer, &plaintext[buffit], (strlen(&plaintext[buffit]) >= 1023) ? 1023 : strlen(&plaintext[buffit]));
        buffer[1023] = '\0';

        // Send message to server
        // Write to the server
        charsWritten = send(socketFD, buffer, strlen(buffer), 0);
        if (charsWritten < 0) {
            error("CLIENT: ERROR writing to socket");
        }

        buffit += charsWritten;

    } while (buffit < strlen(plaintext));

    char endMsg[] = "Message End.\0";
    if (send(socketFD, endMsg, strlen(endMsg), 0) != strlen(endMsg)) {
        error("CLIENT: ERROR sending end message to socket");
    }

    // Get return message from server
    // Clear out the buffer again to reuse
    memset(buffer, '\0', sizeof(buffer));

    // Read data from the socket, leaving \0 at end
    charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
    if (charsRead < 0) {
        error("CLIENT: ERROR reading from socket");
    }

    printf("CLIENT: I recieved this from the server: \"%s\"\n", buffer);

    // Close the socket
    close(socketFD);
    return 0;
}