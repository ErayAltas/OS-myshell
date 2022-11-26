#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Dosya içine system saatini, pid ve ppid değerini tek satır halinde yazmalıdır.

int main(int argc, char *argv[])
{

    int times = atoi(argv[2]);
    int fileName = atoi(argv[argc - 1]);

    while (times > 0)
    {
        size_t n = 10;
        char *input = malloc(sizeof(char) * n);
        printf("input: ");
        getline(&input, &n, stdin);

        char pid[10];
        char ppid[10];
        sprintf(pid, "%d", getpid());
        sprintf(ppid, "%d", getppid());

        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        FILE *fptr;
        char ch;
        char *totalProcessInfo[100];
        char *processInfo[6];
        processInfo[0] = "System time:";
        processInfo[1] = asctime(timeinfo);
        processInfo[2] = "Pid:";
        processInfo[3] = pid;
        processInfo[4] = " PPid:";
        processInfo[5] = ppid;

        strcat(totalProcessInfo, processInfo[0]);
        strcat(totalProcessInfo, processInfo[1]);
        strcat(totalProcessInfo, processInfo[2]);
        strcat(totalProcessInfo, processInfo[3]);
        strcat(totalProcessInfo, processInfo[4]);
        strcat(totalProcessInfo, processInfo[5]);
        strcat(totalProcessInfo, "\n");

        fptr = fopen(fileName, "a");

        if (fptr != NULL)
        {
            fprintf(fptr, "%s\n", input);
            fprintf(fptr, "%s\n", totalProcessInfo);
            fclose(fptr);

            fptr = fopen(fileName, "r");
            while ((ch = fgetc(fptr)) != EOF)
            {
                printf("%c", ch);
            }

            fclose(fptr);
            return 0;
        }

        fprintf(fptr, "%s\n", input);
        fprintf(fptr, "%s\n", totalProcessInfo);
        fclose(fptr);

        //read
        fptr = fopen(fileName, "r");
        while ((ch = fgetc(fptr)) != EOF)
        {
            printf("%c", ch);
        }

        //free up
        fclose(fptr);
        free(totalProcessInfo);
        free(processInfo);
        free(input);
        times--;
    }

    return 0;
}