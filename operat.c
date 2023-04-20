#include "shell.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

int main() {
    char *command;
    char **args = malloc(MAX_ARGUMENTS * sizeof(char *));
    int status;

    while ((command = read_command()) != NULL) {
        int num_args = parse_command(command, args);
        if (num_args > 0) {
            if (strcmp(args[0], "exit") == 0) {
                if (num_args > 1) {
                    status = atoi(args[1]);
                }
                exit(status);
            } else if (strcmp(args[0], "cd") == 0) {
                if (num_args > 1) {
                    chdir(args[1]);
                } else {
                    chdir(getenv("HOME"));
                }
            } else if (strcmp(args[0], "&&") == 0) {
                execute_and(args);
            } else if (strcmp(args[0], "||") == 0) {
                execute_or(args);
            } else {
                status = execute_command(args);
            }
        }

        cleanup_args(args);
        free(command);
    }

    free(args);
    return 0;
}

int execute_command(char **args) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror(args[0]);
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
}

int execute_and(char **args) {
    int status = 0;
    int i = 1;

    while (args[i] != NULL) {
        if (status == 0) {
            status = execute_command(&args[i]);
        }

        i++;
    }

    return status;
}

int execute_or(char **args) {
    int status = 0;
    int i = 1;

    while (args[i] != NULL) {
        if (status != 0) {
            status = execute_command(&args[i]);
        }

        i++;
    }

    return status;
}

char *read_command() {
    char *buffer = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    char *result = fgets(buffer, MAX_COMMAND_LENGTH, stdin);

    if (result == NULL) {
        free(buffer);
    }

    return result;
}

int parse_command(char *command, char **args) {
    int num_args = 0;
    char *token = strtok(command, " \n");

    while (token != NULL) {
        args[num_args] = token;
        num_args++;
        token = strtok(NULL, " \n");
    }

    args[num_args] = NULL;

    return num_args;
}

void cleanup_args(char **args) {
    int i = 0;

    while (args[i] != NULL) {
        args[i] = NULL;
        i++;
    }
}
