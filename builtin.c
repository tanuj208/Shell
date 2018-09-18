#include "headers.h"

void shell_echo(char **command)
{
	// tokenizing to handle multiple tabs/spaces in between words
	int i = 1;
	while(command[i]!=NULL)
	{
		printf("%s ",command[i]);
		i++;
	}
	printf("\n");
	return;
}

void shell_cd(char **command, char HOME_DIRECTORY[])
{
	int x;
	char output[PATH_MAX] = {'\0'};
	if(command[1] == NULL)
		command[1] = "~";
	convert_to_tilda(HOME_DIRECTORY, command[1], output);
	x = chdir(output);
	// error handling in case wrong name is entered
	if(x < 0)
		printf("%s: No such directory\n", output);
	return;
}

void shell_pwd()
{
	char pathname[PATH_MAX] = {'\0'};
	getcwd(pathname, sizeof(pathname));
	printf("%s\n",pathname);
}
