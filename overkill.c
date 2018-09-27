#include "headers.h"

void shell_overkill(char **command, int processes[])
{
    int i = 0;
    for(i = 0 ; i < 1000 ; i ++)
    {
        if(processes[i] != -1)
        {
            kill(processes[i], 9);
            processes[i] = -1;
        }
    }
    return;
}