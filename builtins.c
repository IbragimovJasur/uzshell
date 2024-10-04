#include <stdio.h>
#include <unistd.h>

int uzshell_cd(char **args)
{
    if (args[0] == NULL)
    {
        fprintf(stderr, "'kir' buyruqga argument topilmadi");
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
    if (args[0] == NULL)
    {
        fprintf(stderr, "'aks' buyruqga argument topilmadi");
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
    return 1;
}
