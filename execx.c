#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define clear() printf("\033[H\033[J")

int main(int argc, char *argv[])
{
    int forkVal, execVal;

    // if clear called with execx, it executes clear number of times
    if (strcmp(argv[3], "clear") == 0)
    {
        clear();
    }
    // if ls called with execx, it executes ls number of times
    else if (strcmp(argv[3], "ls") == 0)
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            system("/bin/ls");
        }
    }
    // if cat called with execx, it executes cat number of times
    else if (strcmp(argv[3], "cat") == 0)
    {

        for (int i = 0; i < atoi(argv[2]); i++)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                // calls the cat command
                execVal = execve("/bin/cat", argv, NULL);
                exit(0);
                perror("exec failed");
            }
            else
            {
                // Waits until the child process has finished
                wait(&execVal);
            }
        }
    }
    // if bash called with execx, it executes bash number of times
    else if (strcmp(argv[3], "bash") == 0)
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            system("/bin/bash");
        }
    }
    // if exit called with execx, it executes exit number of times
    else if (strcmp(argv[3], "exit") == 0)
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            exit(0);
        }
    }
    // if writef called with execx, it executes writef number of times
    else if (strcmp(argv[3], "writef") == 0 && !strcmp(argv[4], "-f") && argv[5] != NULL && argc == 6)
    {

        for (int i = 0; i < atoi(argv[2]); i++)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("writef", argv, NULL);
                exit(0);
                perror("exec failed");
            }
            else
            {
                wait(&execVal);
            }
        }
    }
    else
    {
        printf("Wrong command. !help to see commands.\n");
    }
}