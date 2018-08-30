#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

void other_commands(char commandName[])
{
    char *token;
    char command[PATH_MAX];
    char tempArray[PATH_MAX][15];
    int i = 0;
    int flag = 0;
    char *buf[PATH_MAX];

	token = strtok(commandName, " \t");
    if(token == NULL)
        return;
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
        int pid = fork();
        if(pid == 0)
        {
            execvp(command, buf);
            printf("Command not found\n");
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
        int pid = fork();
        if(pid == 0)
        {
            execvp(command, buf);
            printf("Command not found\n");
        }
    }
    return;
}