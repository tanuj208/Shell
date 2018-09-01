#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "definitions.h"

void shell_echo(char *token)
{
	// tokenizing to handle multiple tabs/spaces in between words
	token = strtok(NULL, " \t");
	while(token != NULL)
	{
		printf("%s ",token);
		token = strtok(NULL, " \t");
	}
	printf("\n");
	return;
}

void shell_cd(char *token, char HOME_DIRECTORY[])
{
	int x;
	char output[PATH_MAX]={'\0'};
	token = strtok(NULL, " \t");
	if(token == NULL)
		token = "~";
	convert_to_tilda(HOME_DIRECTORY, token, output);
	x = chdir(output);
	// error handling in case wrong name is entered
	if(x < 0)
		printf("%s: No such directory\n", output);
	return;
}

void shell_pwd()
{
	char pathname[PATH_MAX]={'\0'};
	getcwd(pathname, sizeof(pathname));
	printf("%s\n",pathname);
}
