#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int gettftp(int argc, char *argv[ ]) {
    int s;
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    struct addrinfo *res;

    // use of getnameinfo to get the name and adress of the host and the server
    s = getaddrinfo(argv[1],NULL, &hints, &res);

    //manage the error if there are no arguments or if the arguments are false
    if (s != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // make a connection to the good server with socket and connect
    int sockfd = socket(res->ai_family,res-> ai_socktype, res-> ai_protocol);
    connect(sockfd,res->ai_addr,sizeof(struct sockaddr));

    //error management
    if (sockfd == -1) { 
        perror("Erreur lors de la création du socket");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }
    
    if (connect(sockfd, (struct sockaddr *)server_addr, sizeof(*server_addr)) == -1) {
        perror("Erreur lors de la connexion au serveur");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    return 0;
}