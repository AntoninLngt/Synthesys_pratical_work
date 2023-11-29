#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main (){
    const char* welcom = "Welcom to ENSEA Tiny Shell. \n";
    write (STDOUT_FILENO,welcom,strlen(welcom));
}