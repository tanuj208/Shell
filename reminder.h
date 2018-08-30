#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void reminder(char *token)
{
    int time;
    token = strtok(NULL, " \t");
    time = atoi(token);
    token = strtok(NULL, "");
    int pid = fork();
    if(pid == 0)
    {
        sleep(time);
        printf("%s\n", token);
        return;
    }
    return;
}