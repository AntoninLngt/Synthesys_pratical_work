#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    // Getting the arguments host and file
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *host = argv[1];
    char *file = argv[2];
    printf("host = %s\n", host);
    printf("file = %s\n", file);

    int s;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;  // Specify UDP
    struct addrinfo *res;

    // Use getaddrinfo to get address information
    s = getaddrinfo(host, NULL, &hints, &res);

    // Manage errors if there are no arguments or if the arguments are false
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // Iterate through the results and create a socket for each result
    struct addrinfo *p;
    for (p = res; p != NULL; p = p->ai_next) {
        int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("Error creating socket");
            continue;  // Try the next result
        }

        // Print information about the address
        char ipstr[INET6_ADDRSTRLEN];
        void *addr;
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("Address: %s\n", ipstr);
        printf("Protocol: %i (17 = UDP)\n", p->ai_protocol);
        

        // Close the socket
        close(sockfd);
    }

    // Free the memory
    freeaddrinfo(res);

    return EXIT_SUCCESS;
}