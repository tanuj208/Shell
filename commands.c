#include "headers.h"

int interpretCommands(char ** commands, char HOME_DIRECTORY[], int processes[], int *sz_proc)
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
	
	else if(!strcmp(commands[0], "quit"))
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

	else if(!strcmp(commands[0], "setenv"))
		setenvir(commands);

	else if(!strcmp(commands[0], "unsetenv"))
		unsetenvir(commands);

	else if(!strcmp(commands[0], "jobs"))
		shell_jobs(commands, processes);

	else if(!strcmp(commands[0], "kjobs"))
		shell_kjobs(commands, processes);

	else if(!strcmp(commands[0], "fg"))
		shell_fg(commands, processes, sz_proc);

	else if(!strcmp(commands[0], "bg"))
		shell_bg(commands, processes);

	else if(!strcmp(commands[0], "overkill"))
		shell_overkill(commands, processes);

	else
		other_commands(commands, processes, sz_proc);
    return exit;
}