#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[ ]) {
    if (argc==3){
        char *host = argv[1];
        char *file = argv[2];
        printf("host = %s\n",host);
        printf("file = %s\n",file);
    }

    return 0;
}