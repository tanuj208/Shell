#include "headers.h"

void setenvir(char ** command)
{
    int total_commands = 0;
    while(command[total_commands] != NULL)
        total_commands ++;
    if(total_commands == 1 || total_commands > 3)
    {
        perror("Usage: setenv <var> <value> or setenv <var>\n");
        return;
    }
    if(command[2] == NULL)
        command[2] = "";
    setenv(command[1], command[2], 1);
    return;
}

void unsetenvir(char ** command)
{
    int total_commands = 0;
    while(command[total_commands] != NULL)
        total_commands ++;
    if(total_commands != 2)
    {
        perror("Usage: unsetenv <var>\n");
        return;
    }
    unsetenv(command[1]);
    return;
}