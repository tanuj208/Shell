#include "headers.h"

void reminder(char **command)
{
    int time;
    int i;
    if(command[1] == NULL || command[2] == NULL)
    {
        printf("Usage remindme <number> <message>\n");
        return;
    }
    for(i=0;i<strlen(command[1]);i++)
    {
        if(command[1][i] < '0' || command[1][i] > '9')
        {
            printf("Usage remindme <number> <message>\n");
            return;
        }
    }
    // atoi converts string to integer
    time = atoi(command[1]);
    int pid = fork();
    if(pid == 0)
    {
        sleep(time);
        printf("%s\n", command[2]);
        exit(0);
    }
    return;
}