#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 256

int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \n Type 'exit' to quit. \n";
    size_t message_Welcome_length = strlen(message_Welcome); //To mesure the lenght of the message for the write function


    while (1) {
        write(STDOUT_FILENO, message_Welcome, message_Welcome_length);
        fgets(user_input, sizeof(user_input), stdin); // To save the anwers from the user
        user_input[strcspn(user_input, "\n")] = '\0'; // To suppress the caractère \n

        if (strcmp(user_input, "exit") == 0) {
            const char *message_exit="Bye bye ...";
            size_t message_exit_length = strlen(message_exit);
            write(STDOUT_FILENO, message_exit, message_exit_length);
            break;  // Leave the while loop to be able to quit the shell
        }
        else if (strcmp(user_input, "fortune") == 0){

        }
        else if (strcmp(user_input, "date") == 0){

        }
    }

    return 0;
}