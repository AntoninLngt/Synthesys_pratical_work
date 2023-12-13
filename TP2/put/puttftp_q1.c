#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[ ]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *host;
    char *file;
    if (argc==3){
        host = argv[1];
        file = argv[2];
        printf("host = %s\n",host);
        printf("file = %s\n",file);
    }

    return EXIT_SUCCESS;
}