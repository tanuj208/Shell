#include "headers.h"

int signalFlag22 = 0;
int anotherSignalFlag22 = 0;

void anotherSignalHandler22(int sig)
{
    anotherSignalFlag22 = 1;
    return;
}

void signalHandler22(int sig)
{
    signalFlag22 = 1;
    return;
}

void shell_fg(char ** command, int processes[], int *sz_proc)
{
    signalFlag22 = 0;
    anotherSignalFlag22 = 0;
    int total_commands = 0;
    while(command[total_commands] != NULL)
        total_commands++;
    if(total_commands != 2)
    {
        perror("Usage: fg <jobnumber>\n");
        return;
    }
    int i = 0;
    while(command[1][i] != '\0')
    {
        if(command[1][i] > '9' || command[1][i] < '0')
        {
            perror("Usage: fg <jobnumber>\n");
            return;
        }
        i++;
    }
    int jobnumber = atoi(command[1]);
    int cntr = 1;
    for(i = 0 ; i < 1000 ; i++)
    {
        if(processes[i] == -1)
            continue;
        if(cntr == jobnumber)
        {
            int current_pid = processes[i];
            processes[i] = -1;
            int status;
            signal(SIGINT, signalHandler22);
            signal(SIGTSTP, anotherSignalHandler22);
            kill(current_pid, SIGCONT);
            while(waitpid(current_pid, &status, WNOHANG) != current_pid)
            {
                if(signalFlag22 == 1)
                {
                    kill(current_pid, SIGINT);
                    signalFlag22 = 0;
                    break;
                }
                if(anotherSignalFlag22 == 1)
                {
                    kill(current_pid,SIGSTOP);
                    processes[*sz_proc] = current_pid;
                    (*sz_proc)++;
                    anotherSignalFlag22 = 0;
                    break;
                }
            }
            break;
        }
        cntr++;
    }
    if(cntr != jobnumber)
        perror("Invalid jobnumber\n");
    return;
}

void shell_bg(char ** command, int processes[])
{
    int total_commands = 0;
    while(command[total_commands] != NULL)
        total_commands++;
    if(total_commands != 2)
    {
        perror("Usage: fg <jobnumber>\n");
        return;
    }
    int i = 0;
    while(command[1][i] != '\0')
    {
        if(command[1][i] > '9' || command[1][i] < '0')
        {
            perror("Usage: fg <jobnumber>\n");
            return;
        }
        i++;
    }
    int jobnumber = atoi(command[1]);
    int cntr = 1;
    for(i = 0 ; i < 1000 ; i++)
    {
        if(processes[i] == -1)
            continue;
        if(cntr == jobnumber)
        {
            int status;
            kill(processes[i], SIGCONT);
            break;
        }
        cntr++;
    }
    if(cntr != jobnumber)
        perror("Invalid jobnumber\n");
    return;
}