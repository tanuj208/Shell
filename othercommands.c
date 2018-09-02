#include "headers.h"

void other_commands(char commandName[])
{
    char *token;
    char command[PATH_MAX]={'\0'};
    char tempArray[PATH_MAX][15]={'\0'};
    int i = 0;
    int flag = 0;
    char *buf[PATH_MAX]={NULL};

	token = strtok(commandName, " \t");
    if(token == NULL)
        return;

    // flag == 1 implies & is used and therefore process is a background process
	while(token != NULL)
	{
        if(i == 0)
        {
            strcpy(command, token);
            command[strlen(token)] = '\0';
        }
        strcpy(tempArray[i], token);
        tempArray[i][strlen(token)] = '\0';
        if(!strcmp(token, "&"))
        {
            flag = 1;
            break;
        }
        buf[i] = tempArray[i];
		token = strtok(NULL, " \t");
        i++;
	}

    if(flag == 0)
    {
        // if foreground process then waiting till it gets over
        int pid = fork();
        if(pid == 0)
        {
            execvp(command, buf);
            printf("%s: Command not found\n", commandName);
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
                execvp(command, buf);
                printf("%s: Command not found\n", commandName);
            }
            else
            {
                wait(NULL);
                printf("%s with pid %d exited\n", commandName, 1 + getpid());
                exit(0);
            }
        }
    }
    return;
}