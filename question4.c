#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 256

char *displayreturn(int signal_number) {
    char *display = (char *)malloc(20);
    if (signal_number==-1){
        sprintf(display,"enseash");
    }
    else if (signal_number == 0) {
        sprintf(display,"enseash [exit:0]");
    } 
    else {
        sprintf(display,"enseash [sign:%i]",signal_number);
    }
    return display;
}


int main() {
    char user_input[MAX_INPUT_SIZE];
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \nType 'exit' to quit. \n";
    size_t message_Welcome_length = strlen(message_Welcome);
    write(STDOUT_FILENO, message_Welcome, message_Welcome_length);
    int signal_number = -1 ;
    int status;


    while (1) {
        char *display=displayreturn(signal_number);
        write(STDOUT_FILENO, display, strlen(display));
        write(STDOUT_FILENO," % ",strlen(" % "));
        ssize_t bytesRead = read(STDIN_FILENO, user_input, sizeof(user_input));
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (bytesRead == 0) {
            const char *message_Exit = "\nBye bye...\n";
            size_t message_Exit_length = strlen(message_Exit);
            write(STDOUT_FILENO, message_Exit, message_Exit_length);
            break;
        }

        user_input[bytesRead - 1] = '\0'; // Remove the newline character

        if (strcmp(user_input, "exit") == 0) {
            const char *message_Exit = "Bye bye...\n";
            size_t message_Exit_length = strlen(message_Exit);
            write(STDOUT_FILENO, message_Exit, message_Exit_length);
            break;
        } else if (strcmp(user_input, "") == 0) {
            // Do nothing for an empty input
        } else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                sleep(30);
                execl("/bin/sh", "sh", "-c", user_input, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            } else {
                char pid_message[50];
                sprintf(pid_message, "Le PID du processus en cours est : %d\n", pid);
                size_t pid_message_length = strlen(pid_message);
                write(STDOUT_FILENO, pid_message, pid_message_length);
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)){
                    signal_number = WEXITSTATUS(status);
                }else if (WIFSIGNALED(status)){
                    signal_number = WTERMSIG(status);
                }
                
            }
            putchar('\n'); // Print a newline character after each command
        }
    }
}