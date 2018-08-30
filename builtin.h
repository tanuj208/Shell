#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void shell_echo(char *token)
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

void shell_cd(char *token, char HOME_DIRECTORY[])
{
	token = strtok(NULL, " \t");
	if(token == NULL)
		token = "~";
	char output[PATH_MAX];
	strcpy(output, HOME_DIRECTORY);

	if(token[0] == '~')
	{
		strcat(output, token + 1);
		chdir(output);
	}
	else
		chdir(token);
	return;
}

void shell_pwd()
{
	char pathname[PATH_MAX];
	getcwd(pathname, sizeof(pathname));
	printf("%s\n",pathname);
}
