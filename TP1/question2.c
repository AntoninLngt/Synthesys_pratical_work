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
        write(STDOUT_FILENO, "enseash % ", strlen ("enseash % "));
        ssize_t bytesRead = read(STDIN_FILENO, user_input, sizeof(user_input));
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        user_input[bytesRead - 1] = '\0';

        if (strcmp(user_input, "exit") == 0) {
            break;  // Leave the while loop to be able to quit the shell
        }
        else if (strcmp(user_input, "") == 0){
        }
        else {
                pid_t pid = fork();
                if (pid == -1) { // Error in the creation in the son process
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
        }
    return 0;
}