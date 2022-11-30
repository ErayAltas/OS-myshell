#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int times = 0;
    char *fileName;

    // if called with execx
    if (argc == 6)
    {
        fileName = argv[5];
        times = atoi(argv[2]);
    }
    // if only writef called
    else
    {
        fileName = argv[2];
        times = 1;
    }

    while (times > 0)
    {
        FILE *fptr;
        char character;
        char *systemTime;

        // get pid and ppid values
        int pidValue = getpid();
        int ppidValue = getppid();

        size_t n = 10;
        // allocate memory
        char *buf = malloc(sizeof(char) * n);
        printf(">");
        // get input from user
        getline(&buf, &n, stdin);

        // get time info
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        systemTime = asctime(timeinfo);
        systemTime[strlen(systemTime) - 1] = 0;

        fptr = fopen(fileName, "a");

        // if file exists
        if (fptr != NULL)
        {
            // print input and system hour,pid,ppid
            fprintf(fptr, "%s\n", buf);
            fprintf(fptr, "System time : %s pid : %d ppid : %d\n\n", systemTime, pidValue, ppidValue);

            fclose(fptr);
            return 0;
        }
        // if file doesnt exists
        // print input and system hour,pid,ppid
        fprintf(fptr, "%s\n", buf);
        fprintf(fptr, "System time : %spid : %d ppid : %d\n\n", systemTime, pidValue, ppidValue);

        fclose(fptr);
        free(buf);
        times--;
    }

    return 0;
}