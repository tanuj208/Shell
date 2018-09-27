#include "headers.h"

int anotherSignalFlag = 0;
int foreground_pid;

void anotherSignalHandler(int sig)
{
    anotherSignalFlag = 1;
    kill(foreground_pid,SIGTSTP);
    return;
}

void other_commands(char **commandName, int processes[], int *sz_proc)
{
    anotherSignalFlag = 0;
    int i = 0;
    int flag = 0;
    char *buf[PATH_MAX] = {NULL};

    if(commandName[0] == NULL)
        return;

    // flag == 1 implies & is used and therefore process is a background process
	while(commandName[i] != NULL)
	{
        if(commandName[i][0] == '&')
        {
            flag = 1;
            break;
        }
        buf[i] = commandName[i];
        i++;
	}

    if(flag == 0)
    {
        // if foreground process then waiting till it gets over
        int pid = fork();
        if(pid == 0)
        {
            execvp(buf[0], buf);
            printf("%s: Command not found\n", buf[0]);
            exit(0);
        }
        else
        {
            int status;
            foreground_pid = pid;
            signal(SIGTSTP, anotherSignalHandler);
            waitpid(pid, &status, WUNTRACED);
            if(anotherSignalFlag == 1)
            {
                processes[*sz_proc] = pid;
                (*sz_proc)++;
            }
        }
    }
    else
    {
        // if background process then forking it again and after it gets over the new parent will tell us it is over
        // in first parent process we can execute other commands
        int pid = fork();
        processes[*sz_proc] = pid;
        (*sz_proc)++;
        setpgid(0,0);
        if(pid == 0)
        {
            execvp(buf[0], buf);
            printf("%s: Command not found\n", buf[0]);
            exit(0);
        }
    }
    return;
}