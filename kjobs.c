#include "headers.h"

void shell_kjobs(char **commands, int processes[])
{
    int i = 0;
    int total_commands = 0;
    while(commands[total_commands] != NULL)
        total_commands++;
    if(total_commands != 3)
    {
        perror("Usage: kjobs <jobnumber> <signalNumber>\n");
        return;
    }
    while(commands[1][i] != '\0')
    {
        if(commands[1][i] < '0' || commands[1][i] > '9')
        {
            perror("Usage: kjobs <jobnumber> <signalNumber>\n");
            return;
        }
        i++;
    }
    i = 0;
    while(commands[2][i] != '\0')
    {
        if(commands[2][i] < '0' || commands[2][i] > '9')
        {
            perror("Usage: kjobs <jobnumber> <signalNumber>\n");
            return;
        }
        i++;
    }
    int jobnumber = atoi(commands[1]);
    int signalNumber = atoi(commands[2]);
    int cntr = 1;
    for(i = 0;i < 1000; i++)
    {
        if(processes[i] == -1)
            continue;
        if(cntr == jobnumber)
        {
            int x = kill(processes[i], signalNumber);
            if(x < 0)
            {
                printf("Invalid signal number\n");
                return;
            }
            break;
        }
        cntr++;
    }
    if(cntr != jobnumber)
        printf("No such job number exists\n");
    return;
}