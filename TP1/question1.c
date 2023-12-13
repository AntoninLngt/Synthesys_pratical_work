#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 256

int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message = "Welcome to ENSEA Tiny Shell. \nType 'exit' to quit. \n";
    size_t message_length = strlen(message); // To mesure the lenght of the message for the write function
    write(STDOUT_FILENO, message,message_length);

    while (1) {
        write(STDOUT_FILENO, "enseash % ", strlen ("enseash % "));
        ssize_t bytesRead = read(STDIN_FILENO, user_input, sizeof(user_input));
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        user_input[bytesRead - 1] = '\0'; // To suppress the caractère \n

        if (strcmp(user_input, "exit") == 0) {

            break;  // Leave the while loop to be able to quit the shell
        }
    }

    return 0;
}