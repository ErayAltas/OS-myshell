#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define clear() printf("\033[H\033[J")

int isNumber(char *ch)
{
    int i = strlen(ch);
    int isnum = (i > 0);
    while (i-- && isnum)
    {
        if (!(ch[i] >= '0' && ch[i] <= '9'))
        {
            isnum = 0;
        }
    }
    return isnum;
}

int main(int argc, char *argv[])
{
    char input[80];

    while (1)
    {
        int forkVal, execVal;
        int k = 20;
        int command_size = 0;
        const char *command[k];

        printf("myshell>>");

        // get input from user
        gets(input);

        command[0] = strtok(input, " ");

        for (int m = 1; m < k; m++)
        {
            command[m] = strtok(NULL, " ");
        }

        while (command[command_size] != NULL)
        {
            // get command size
            command_size++;
        }
        // if bash called, execute local bash
        if (!strcmp(command[0], "bash"))
        {
            char *newArgv[1];
            newArgv[0] = "bash";

            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("/bin/bash", newArgv, NULL);
                perror("exec error");
            }
            else
            {
                wait(&execVal);
            }

            /* system("/bin/bash"); */
        }
        // if writef called, open file and write into file
        else if (!strcmp(command[0], "writef") && !strcmp(command[1], "-f") && command[2] != NULL && command_size == 3)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("writef", command, NULL);
                perror("exec error");
            }
            else
            {
                wait(&execVal);
            }
        }
        // if execx called, it takes -t times program, it executes the number of times the program
        else if (!strcmp(command[0], "execx") && !strcmp(command[1], "-t") && isNumber(command[2]) == 1 && command_size >= 4)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("execx", command, NULL);
                perror("exec error");
            }
            else
            {
                wait(&execVal);
            }
        }
        // if cat called, read file
        else if (!strcmp(command[0], "cat") && command_size > 1)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("/bin/cat", command, NULL);
                perror("exec error");
            }
            else
            {
                wait(&execVal);
            }
        }
        // if ls called, get files in this file
        else if (!strcmp(command[0], "ls") && command[1] == NULL)
        {
            forkVal = fork();
            if (forkVal == 0)
            {
                execVal = execve("/bin/ls", command, NULL);
                perror("exec error");
            }
            else
            {
                wait(&execVal);
            }
        }
        // if clear called, clear shell
        else if (!strcmp(command[0], "clear") && command[1] == NULL)
        {
            clear();
        }
        // if help called, get commands
        else if (strcmp(command[0], "!help") == 0 && command[1] == NULL)
        {
            printf("--------------------\n\n");
            printf("writef -f fileName -- write into file\n");
            printf("execx -t n program -- execute program n times\n");
            printf("clear -- clear page\n");
            printf("ls -- fetch files in the same directory.\n");
            printf("cat fileName -- read fileName\n");
            printf("bash -- call local bash\n");
            printf("exit -- exit program\n\n");
            printf("--------------------\n");

        }
        // if exit called, exit program
        else if (strcmp(command[0], "exit") == 0)
        {
            exit(0);
        }
        // if wrong argument called
        else
        {
            printf("Wrong command. !help to see commands.\n");
        }
    }

    return 0;
}
