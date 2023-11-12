#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define AUDIO_FILE "sample.wav"  
#define PORT 12345             
#define BUFF_SIZE 1024

int main() {
    int sockfd;
    struct sockAdress_in serverAddress;
    FILE *audio_file;
    char buffer[BUFF_SIZE];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  

    if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    audio_file = fopen(AUDIO_FILE, "rb");
    if (audio_file == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        size_t bytesRead = fread(buffer, 1, BUFF_SIZE, audio_file);
        if (bytesRead <= 0) {
            //EOF
            break;
        }

        // Send audio segment over TCP
        send(sockfd, buffer, bytesRead, 0);
    }

    // Indicate the end of the file to the receiver
    send(sockfd, "EOF", 3, 0);
    fclose(audio_file);
    close(sockfd);

    return 0;
}
