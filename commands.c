#include "headers.h"

int interpretCommands(char ** commands, char HOME_DIRECTORY[])
{
    int exit = 0;

	if(!strcmp(commands[0], "echo"))
		shell_echo(commands);

	else if(!strcmp(commands[0], "cd"))
		shell_cd(commands, HOME_DIRECTORY);

	else if(!strcmp(commands[0], "pwd"))
		shell_pwd();

	else if(!strcmp(commands[0], "exit"))
		exit = 1;

	else if(!strcmp(commands[0], "remindme"))
		reminder(commands);

	else if(!strcmp(commands[0], "pinfo"))
	{
		if(commands[1] != NULL)
			shell_pinfo(atoi(commands[1]), HOME_DIRECTORY);
		else
			shell_pinfo(getpid(), HOME_DIRECTORY);
	}

	else if(!strcmp(commands[0], "ls"))
		shell_ls(commands, HOME_DIRECTORY);

	else if(!strcmp(commands[0], "clock"))
		shell_clock(commands);

	else
		other_commands(commands);
    return exit;
}