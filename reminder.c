#include "headers.h"

void reminder(char *token)
{
    int time;
    token = strtok(NULL, " \t");
    // atoi converts string to integer
    time = atoi(token);
    token = strtok(NULL, "");
    int pid = fork();
    if(pid == 0)
    {
        sleep(time);
        printf("%s\n", token);
        exit(0);
    }
    return;
}