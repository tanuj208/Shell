#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>

int display()
{
	char pathname[PATH_MAX];  // will have to change this
	char hostname[HOST_NAME_MAX];
	struct passwd *pw;

	pw = getpwuid (geteuid());
	if(getcwd(pathname, sizeof(pathname)) == NULL)
	{
		printf("Some error occurred in getting cwd\n");
		return -1;
	}
	if(gethostname(hostname, sizeof(hostname)))
	{
		printf("Some error occurred in getting hostname\n");
		return -1;
	}
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
	}
	return 0;
}
