#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>

char HOME_DIRECTORY[50] = "/home/tanuj/Downloads/Sem-3/OS/Assignment2/Shell";

int display()
{
	char complete_pathname[PATH_MAX];
	char pathname[PATH_MAX];
	char hostname[HOST_NAME_MAX];
	struct passwd *pw;
	pw = getpwuid(geteuid());

	if(getcwd(complete_pathname, sizeof(complete_pathname)) == NULL)
	{
		printf("Some error occurred in getting cwd\n");
		return -1;
	}
	if(gethostname(hostname, sizeof(hostname)))
	{
		printf("Some error occurred in getting hostname\n");
		return -1;
	}
	int i;
	int flag = 0;
	for(i=0;i<strlen(HOME_DIRECTORY);i++)
	{
		if(HOME_DIRECTORY[i] != complete_pathname[i])
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		pathname[0]='~';
		int k = 1;
		for(i=strlen(HOME_DIRECTORY);i<strlen(complete_pathname);i++)
		{
			pathname[k] = complete_pathname[i];
			k++;
		}
		pathname[k]='\0';
	}
	else
		strcpy(pathname, complete_pathname);
	if(pw)
		printf("<%s@%s:%s> ",pw->pw_name, hostname, pathname);
	else
	{
		printf("Some error occurred in getting username\n");
		return -1;
	}	
	return 0;
}

void echo(char *token)
{
	token = strtok(NULL, " \t");
	while(token != NULL)
	{
		printf("%s ",token);
		token = strtok(NULL, " \t");
	}
	printf("\n");
	return;
}

void cd(char *token)
{
	token = strtok(NULL, " \t");
	chdir(token);
	return;
}

void pwd()
{
	char pathname[PATH_MAX];
	getcwd(pathname, sizeof(pathname));
	printf("%s\n",pathname);
}

int main()
{
	while(1)
	{
		int x = display();
		if(x==-1)
			return 0;
		char input[MAX_INPUT];
		char * token;
		char * rest;
		fgets(input, MAX_INPUT, stdin);
		input[strlen(input) - 1] = '\0';
		rest = input;
		token = strtok(rest, " \t");
		if(!strcmp(token, "echo"))
			echo(token);
		else if(!strcmp(token, "cd"))
			cd(token);
		else if(!strcmp(token, "pwd"))
			pwd();
	}
	return 0;
}
