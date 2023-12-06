#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 256

int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \nType 'exit' or ctrl+d to quit. \n";
    size_t message_Welcome_length = strlen(message_Welcome);
    write(STDOUT_FILENO, message_Welcome, message_Welcome_length);

    while (1) {
        write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));
        
        ssize_t bytesRead = read(STDIN_FILENO, user_input, sizeof(user_input));
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (bytesRead == 0) {
            const char *message_Exit = "Bye bye...\n";
            size_t message_Exit_length = strlen(message_Exit);
            write(STDOUT_FILENO, message_Exit, message_Exit_length);
            break;
        }

        user_input[bytesRead - 1] = '\0'; // Remove the newline character
        int Redirection=1;
        int i=0;
        while(user_input[i]!='\0'){
            if (user_input[i]=='>'){
            Redirection= 0;
            }
            i++;
        }

        if (strcmp(user_input, "exit") == 0) {
            const char *message_Exit = "Bye bye...\n";
            size_t message_Exit_length = strlen(message_Exit);
            write(Redirection, message_Exit, message_Exit_length);
            break;
        } else if (strcmp(user_input, "") == 0) {
            // Do nothing for an empty input
        } else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE); // in case of an error in the processor
            } else if (pid == 0) {
                execl("/bin/sh", "sh", "-c", user_input, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            } else {
                waitpid(pid, NULL, 0);
            }
            putchar('\n'); // Print a newline character after each command
        }
    }

    return 0;
}