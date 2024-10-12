#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int uzshell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "'kir' buyruqga argument topilmadi\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("Xatolik");
        }
    }
    return 0;
}

int uzshell_echo(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "'aks' buyruqga argument topilmadi\n");
    }
    else
    {
        int i = 1;
        do {
            printf("%s ", args[i]);
            i++;
        }
        while (args[i] != NULL);
        printf("\n");
    }
    return 0;
}

int uzshell_exit(char *args)
{
    exit(0);
}
