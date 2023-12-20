#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_DATA_SIZE 512

// Function to build RRQ packet
void build_rrq_packet(char *filename, char *mode, char *rrq_packet) {
    // Opcode 1 for RRQ
    short opcode = htons(1);
    // Use memcpy instead of strcat for binary data
    memcpy(rrq_packet, &opcode, sizeof(opcode));
    // Use strlen for filename length, and strncpy to copy the filename
    strncpy(rrq_packet + sizeof(opcode), filename, strlen(filename));
    // Null-terminate the filename
    rrq_packet[sizeof(opcode) + strlen(filename)] = '\0';
    // Use strncpy for mode, including null-terminator
    strncpy(rrq_packet + sizeof(opcode) + strlen(filename) + 1, mode, strlen(mode) + 1);
}

// Function to build ACK packet
void build_ack_packet(short block_number, char *ack_packet) {
    short opcode = htons(4); // Opcode 4 for ACK
    memcpy(ack_packet, &opcode, sizeof(opcode));
    memcpy(ack_packet + sizeof(opcode), &block_number, sizeof(block_number));
}


int main(int argc, char *argv[]) {
    char *host;
    char *file;

    // Check for the correct number of arguments
    if (argc == 3) {
        host = argv[1];
        file = argv[2];
        printf("host = %s\n", host);
        printf("file = %s\n", file);
    } else {
        fprintf(stderr, "Usage: %s <host> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int s;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // Datagram socket for UDP

    // use of getaddrinfo to get the name and address of the host
    s = getaddrinfo(host, "1069", &hints, &res);

    // manage the error if there are no arguments or if the arguments are false
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // Create UDP socket
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("Error during the creation of the socket");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Build RRQ packet
    char rrq_packet[516]; // Maximum size for RRQ packet
    build_rrq_packet(file, "octet", rrq_packet);
    
    printf("Sending RRQ packet to the server...\n");

    // Send RRQ packet to the server
    int res_send= sendto(sockfd, rrq_packet, strlen(rrq_packet), 0, res->ai_addr, res->ai_addrlen);
    if (res_send ==-1) {
        perror("Error sending RRQ packet");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }
    printf("RRQ packet sent successfully.\n");
    printf("Waiting for DATA packet...\n");

    // Receive DAT packet
    char dat_packet[MAX_DATA_SIZE + 4]; // 4 bytes for opcode and block number
    ssize_t bytes_received = recvfrom(sockfd, dat_packet, sizeof(dat_packet), 0, NULL, NULL);

    if (bytes_received == -1) {
        perror("Error receiving DAT packet");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }


    // close the socket and free the memory
    close(sockfd);
    freeaddrinfo(res);

    return 0;
}
   