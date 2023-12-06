#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_INPUT_SIZE 256
#define MILLION 1000000000L

int main() {
    char user_input[MAX_INPUT_SIZE];
    struct timespec start, stop;    
    long long time_ms;
    const char *message_Welcome = "Welcome to ENSEA Tiny Shell. \nType 'exit' to quit. \n";
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
        } 
        else if (strcmp(user_input, "") == 0) {
            // Do nothing for an empty input
        } 
        else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) {
                // Measure the start time
                if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                    perror("clock_gettime");
                    exit(EXIT_FAILURE);
                }

                // Execute the command in the child process
                execl("/bin/sh", "sh", "-c", user_input, NULL);

                // If execl fails
                perror("execl");
                exit(EXIT_FAILURE);
            } 
            else {
                // Wait for the child process to finish
                int status;
                waitpid(pid, &status, 0);

                // Measure the end time
                if (clock_gettime(CLOCK_MONOTONIC, &stop) == -1) {
                    perror("clock_gettime");
                    exit(EXIT_FAILURE);
                }

                // Calculate and print the execution time in milliseconds
                time_ms = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / MILLION;
                char output[50];
                sprintf(output, "[exit:%d|%lldms] %% ", status, time_ms);
                write(STDOUT_FILENO, output, strlen(output));
            }
            putchar('\n'); // Print a newline character after each command
        }
    }

    return 0;
}


