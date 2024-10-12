#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"

#define INPUT_BUFFER_SIZE 64
#define TOKENS_BUFFER_SIZE 16

char *builtin_commands[] = {
    "kir",
    "aks",
    "chiq"
};

int num_of_builtin_commands()
{
    return sizeof(builtin_commands) / sizeof(char *);
}

int (*builtin_command_functions[])(char **) = {
    &uzshell_cd,
    &uzshell_echo,
    &uzshell_exit
};

char *read_line_from_stdin()
{
    int bufsize = INPUT_BUFFER_SIZE;
    char *buffer = malloc(bufsize * sizeof(char));
    int i = 0;
    char char_;

    if (buffer == NULL)
    {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char_ = getchar();
    while (char_ != '\n' && (int)char_ != EOF)
    {
        buffer[i] = char_;
        char_ = getchar();
        i++;
        if (i == bufsize && char_ != '\n')
        {
            bufsize = bufsize + INPUT_BUFFER_SIZE;
            buffer = realloc(buffer, bufsize * sizeof(char));
            if (buffer == NULL)
            {
                perror("Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    buffer[i] = '\0';
    return buffer;
}

char **parse_line_from_stdin(char *buffer)
{
    const char delimiter[] = " ";
    int tokens_buffer_size = TOKENS_BUFFER_SIZE;
    char **tokens = malloc(tokens_buffer_size * sizeof(char *));
    int i = 0;
    char *string;

    if (tokens == NULL)
    {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    string = strtok(buffer, delimiter);
    while (string != NULL)
    {
        int token_size = strlen(string) + 1;
        char *token = malloc(token_size * sizeof(char));
        if (token == NULL)
        {
            perror("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        tokens[i] = strcpy(token, string);
        i++;
        string = strtok(NULL, delimiter);

        if (i == tokens_buffer_size)
        {
            tokens_buffer_size = tokens_buffer_size + TOKENS_BUFFER_SIZE;
            tokens = realloc(tokens, tokens_buffer_size * sizeof(char *));
            if (tokens == NULL)
            {
                perror("Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    free(buffer);
    return tokens;
}

int execute_sys_command(char **args)
{
    pid_t pid = fork();
    int status;
    if (pid > 0)
    {
        do
        {
            wait(&status);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("uzshell");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        perror("uzshell");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int execute_command(char **args)
{
    char *command = args[0];
    int i = 0;
    if (args[0] == NULL) // empty args
    {
        return 1;
    }
    do
    {
        if (strcmp(command, builtin_commands[i]) == 0)
        {
            builtin_command_functions[i](args);
            return 0;
        }
        i++;
    } while (i < num_of_builtin_commands());
    execute_sys_command(args);
    free(args);
    return 0;
}

int main()
{
    while (1)
    {
        printf("$ ");
        char *buffer = read_line_from_stdin();
        char **tokens = parse_line_from_stdin(buffer);
        execute_command(tokens);
    }
    return 0;
}
