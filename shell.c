#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")

int main(int argc, char *argv[])
{
    char input[1000];
    while (1)
    {
        int f, i;
        int command_size = 0;
        printf("myshell>>");
        // get input from user
        gets(input);

        const char *commands[1000];
        commands[1000] = "|";
        commands[0] = strtok(input, "|");
        for (int i = 1; i < 1000; i++)
        {
            commands[i] = strtok(NULL, "|");
        }

        int index = 0;
        while (commands[index] != NULL)
        {

            const char *command[1000];
            command[0] = strtok(commands[index], " ");
            for (int i = 1; i < 1000; i++)
            {
                command[i] = strtok(NULL, " ");
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

                int frk;
                int status;
                frk = fork();
                if (frk == 0)
                {
                    status = execve("/bin/bash", newArgv, NULL);
                    perror("exec2: execve failed\n");
                }
                else
                {
                    wait(&status); // wait the fork f=0
                }

                /* system("/bin/bash"); */
            }
            // if writef called, open file and write into file
            else if (!strcmp(command[0], "writef") && !strcmp(command[1], "-f") && command[2] != NULL && command_size == 3)
            {
                f = fork();
                if (f == 0)
                {
                    i = execve("writef", command, NULL);
                    perror("exec failed");
                }
                else
                {
                    wait(&i);
                }
            }
            // if execx called, it takes -t times program, it executes the number of times the program
            else if (!strcmp(command[0], "execx") && !strcmp(command[1], "-t") && isNumber(command[2]) == 1 && command_size >= 4)
            {
                f = fork();
                if (f == 0)
                {
                    i = execve("execx", command, NULL);
                    perror("exec failed");
                }
                else
                {
                    wait(&i);
                }
            }
            // if cat called, read file
            else if (!strcmp(command[0], "cat") && command_size > 1)
            {
                f = fork();
                if (f == 0)
                {
                    i = execve("/bin/cat", command, NULL);
                    perror("exec failed");
                }
                else
                {
                    wait(&i);
                }
            }
            // if ls called, get files in this file
            else if (!strcmp(command[0], "ls") && command[1] == NULL)
            {
                f = fork();
                if (f == 0)
                {
                    i = execve("/bin/ls", command, NULL);
                    perror("exec failed");
                }
                else
                {
                    wait(&i);
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
                printf("!help\n");
                printf("writef -f fileName\n");
                printf("execx -t times program\n");
                printf("clear\n");
                printf("ls\n");
                printf("cat fileName\n");
                printf("bash\n");
                printf("exit\n");
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
            index++;
        }
    }
    return 0;
}

int isNumber(char *n)
{
    int i = strlen(n);
    int isnum = (i > 0);
    while (i-- && isnum)
    {
        if (!(n[i] >= '0' && n[i] <= '9'))
        {
            isnum = 0;
        }
    }
    return isnum;
}