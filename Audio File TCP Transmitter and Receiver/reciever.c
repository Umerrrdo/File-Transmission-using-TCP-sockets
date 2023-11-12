#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define OUTPUT_FILE "received_audio.wav"  
#define PORT 12345                       // Same as the sender's port number
#define BUFF_SIZE 1024

int main() {
    int sockfd, newsock;
    struct sockAddress_in serverAddress, newAddress;
    socklen_t addSize;
    FILE *output_file;
    char buffer[BUFF_SIZE];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    addSize = sizeof(newAddress);
    newsock = accept(sockfd, (struct sockaddr*)&newAddress, &addSize);

    // Open a new audio file for writing
    output_file = fopen(OUTPUT_FILE, "wb");
    if (output_file == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int bytesRead = recv(newsock, buffer, BUFF_SIZE, 0);
        if (bytesRead <= 0) {
            // End of file
            break;
        }

        // Write received segment to the output file
        fwrite(buffer, 1, bytesRead, output_file);
    }

    // Close the file and socket
    fclose(output_file);
    close(newsock);
    close(sockfd);

    return 0;
}
