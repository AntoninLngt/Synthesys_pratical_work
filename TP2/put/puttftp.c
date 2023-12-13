#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[ ]) {
    if (argc==3){
        char *host = argv[1];
        char *file = argv[2];
        printf("host = %s\n",host);
        printf("file = %s\n",file);
    }
}