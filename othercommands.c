#include "headers.h"

void other_commands(char **commandName)
{
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
            signal(SIGINT, SIG_DFL);
            execvp(buf[0], buf);
            printf("%s: Command not found\n", buf[0]);
            exit(0);
        }
        else
        {
            int status;
            while(wait(&status) != pid)
                continue;
        }
    }
    else
    {
        // if background process then forking it again and after it gets over the new parent will tell us it is over
        // in first parent process we can execute other commands
        int pid = fork();
        if(pid == 0)
        {
            int pid2 = fork();
            if(pid2 == 0)
            {
                signal(SIGINT, SIG_DFL);
                execvp(buf[0], buf);
                printf("%s: Command not found\n", buf[0]);
                exit(0);
            }
            else
            {
                wait(NULL);
                printf("%s with pid %d exited\n", buf[0], 1 + getpid());
                exit(0);
            }
        }
    }
    return;
}