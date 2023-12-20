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

// Function to build WRQ packet
void build_wrq_packet(char *filename, char *mode, char *wrq_packet) {
    // Opcode 2 for WRQ
    short opcode = htons(2);
    // Use memcpy instead of strcat for binary data
    memcpy(wrq_packet, &opcode, sizeof(opcode));
    // Use strlen for filename length, and strncpy to copy the filename
    strncpy(wrq_packet + sizeof(opcode), filename, strlen(filename));
    // Null-terminate the filename
    wrq_packet[sizeof(opcode) + strlen(filename)] = '\0';
    // Use strncpy for mode, including null-terminator
    strncpy(wrq_packet + sizeof(opcode) + strlen(filename) + 1, mode, strlen(mode) + 1);
}

// Function to send data packet and receive acknowledgment
int send_data_packet(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, char *data, int data_size, int block_number) {
    char data_packet[MAX_DATA_SIZE + 4];
    short opcode = htons(3);  // Opcode 3 for DATA
    short block_num = htons(block_number);

    memcpy(data_packet, &opcode, sizeof(opcode));
    memcpy(data_packet + sizeof(opcode), &block_num, sizeof(block_num));
    memcpy(data_packet + sizeof(opcode) + sizeof(block_num), data, data_size);

    if (sendto(sockfd, data_packet, data_size + 4, 0, server_addr, addr_len) == -1) {
        perror("Error sending DATA packet");
        return -1;
    }

    // Wait for acknowledgment
    char ack_packet[4];
    if (recvfrom(sockfd, ack_packet, sizeof(ack_packet), 0, server_addr, &addr_len) == -1) {
        perror("Error receiving ACK");
        return -1;
    }

    // Check if the received ACK corresponds to the sent block number
    short received_block_num;
    memcpy(&received_block_num, ack_packet + 2, sizeof(received_block_num));
    if (ntohs(received_block_num) != block_number) {
        fprintf(stderr, "Received ACK with unexpected block number\n");
        return -1;
    }

    return 0;
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

    // Build WRQ packet
    char wrq_packet[516]; // Maximum size for wRQ packet
    build_wrq_packet(file, "octet", wrq_packet);

    FILE *file_ptr = fopen(file, "rb");
    if (!file_ptr) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Send WRQ packet to the server
    if (sendto(sockfd, wrq_packet, strlen(wrq_packet), 0, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Error sending WRQ packet");
        fclose(file_ptr);
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Initialize block number for DATA packets
    int block_number = 1;

    size_t bytes_read;

    // Read the file and send data packets until the end of file
    do {
        char data_buffer[MAX_DATA_SIZE];
        bytes_read = fread(data_buffer, 1, sizeof(data_buffer), file_ptr);

        if (send_data_packet(sockfd, res->ai_addr, res->ai_addrlen, data_buffer, bytes_read, block_number) == -1) {
            fprintf(stderr, "Error sending file data\n");
            fclose(file_ptr);
            close(sockfd);
            freeaddrinfo(res);
            exit(EXIT_FAILURE);
        }

        block_number++;
    } while (bytes_read == MAX_DATA_SIZE);

    // Close the file
    fclose(file_ptr);

    // close the socket and free the memory
    close(sockfd);
    freeaddrinfo(res);

    return 0;
}