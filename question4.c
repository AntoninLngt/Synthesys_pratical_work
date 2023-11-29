#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 256

int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \nType 'exit' to quit. \n";
    size_t message_Welcome_length = strlen(message_Welcome); //To mesure the lenght of the message for the write function
    write(STDOUT_FILENO, message_Welcome, message_Welcome_length);

    while (1) {
        int end;
        write(STDOUT_FILENO, "enseash % ", strlen ("enseash % "));
        fgets(user_input, sizeof(user_input), stdin); // To save the anwers from the user
        user_input[strcspn(user_input, "\n")] = '\0'; // To suppress the caracter \n
        
        
        if (strcmp(user_input, "exit") == 0) {
            const char *message_Exit = "Bye bye...\n";
            size_t message_Exit_length = strlen(message_Exit); 
            write(STDOUT_FILENO, message_Exit, message_Exit_length);
            break;  // Leave the while loop to be able to quit the shell
        }

        else if ((end = getchar()) == EOF) {
            const char *message_Exit = "Bye bye...\n";
            size_t message_Exit_length = strlen(message_Exit); 
            write(STDOUT_FILENO, message_Exit, message_Exit_length);
            break;  // Leave the while loop to be able to quit the shell
        }

        else if (strcmp(user_input, "") == 0){
        }
        else {
                pid_t pid = fork();
                if (pid == -1) { // If error in the creation in the son process
                perror("fork");
                exit(EXIT_FAILURE);
                } 
                else if (pid == 0) {
                    execl("/bin/sh", "sh", "-c", user_input, NULL);
            
                    perror("execl"); // if there is an error
                    exit(EXIT_FAILURE);
                } 
                else {
                    waitpid(pid, NULL, 0);
                }
            }
            putchar(end);
        }
    return 0;
}

char *displayreturn(int signal_number) {
    char display[10];
    if (signal_number == 0) {
        display="exit:0";
    } 
    else {
        display="sign:"+signal_number;
    }
    return &display[0];
}