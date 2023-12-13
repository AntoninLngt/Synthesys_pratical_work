#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[ ]) {
    char *host;
    char *file;
    //getting the arguments host and file
    if (argc==3){
        host = argv[1];
        file = argv[2];
        printf("host = %s\n",host);
        printf("file = %s\n",file);
    }
    else {
        printf("Missing argument for %s :<host> <file> \n", argv[0]);
        exit(EXIT_FAILURE);
    }


    int s;
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    struct addrinfo *res;

    // use of getnameinfo to get the name and adress of the host
    s = getaddrinfo(host,NULL, &hints, &res);

    //manage the error if there are no arguments or if the arguments are false
    if (s != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    // make a socket
    int sockfd = socket(res->ai_family,res-> ai_socktype, res-> ai_protocol);
    

    // errors management
    if (sockfd == -1) {
        perror("Erreur lors de la création du socket");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    //make a connection
    connect(sockfd,res->ai_addr,res->ai_addrlen);

    // errors management
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Erreur lors de la connexion au serveur");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Envoyez une requête au serveur avec write
    const char *request = "";
    if (write(sockfd, request, strlen(request)) == -1) {
        perror("write");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }




    // close the socket and we free the memory
    close(sockfd);
    freeaddrinfo(res);

    return 0;
}