#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_INPUT_SIZE 256

int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \nType 'exit' to quit. \n";
    size_t message_Welcome_length = strlen(message_Welcome); //To mesure the lenght of the message for the write function
    write(STDOUT_FILENO, message_Welcome, message_Welcome_length);

    while (1) {
        write(STDOUT_FILENO, "enseash % ", strlen ("enseash % "));
        fgets(user_input, sizeof(user_input), stdin); // To save the anwers from the user
        user_input[strcspn(user_input, "\n")] = '\0'; // To suppress the caractère \n

        if (strcmp(user_input, "exit") == 0) {
            const char *message_exit="Bye bye ...\n";
            size_t message_exit_length = strlen(message_exit);
            write(STDOUT_FILENO, message_exit, message_exit_length);
            break;  // Leave the while loop to be able to quit the shell
        }
        else if (strcmp(user_input, "fortune") == 0){
            const char *message_fortune="Today is what happened to yesterday.\n";
            size_t message_fortune_length = strlen(message_fortune);
            write(STDOUT_FILENO, message_fortune, message_fortune_length);
        }
        else if (strcmp(user_input, "date") == 0){
            time_t now;
            time(&now); // To get the actual time
            struct tm *local_time= localtime(&now);
            char time_str[90]; //default value that we can change
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
            // function that gives the time in a readable way


            write(STDOUT_FILENO, time_str , strlen(time_str)); // View the date
            write(STDOUT_FILENO, "\n", strlen("\n")); // Line break
        }
    }
    return 0;
}