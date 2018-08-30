#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "builtin.h"
#include "display.h"
#include "othercommands.h"
#include "reminder.h"

char HOME_DIRECTORY[PATH_MAX];

int main()
{
	getcwd(HOME_DIRECTORY, sizeof(HOME_DIRECTORY));
	while(1)
	{
		char input[MAX_INPUT];
		char rest[MAX_INPUT];
		char * token;
		int x = display(HOME_DIRECTORY);
		if(x==-1)
			return 0;

		fgets(input, MAX_INPUT, stdin);

		input[strlen(input) - 1] = '\0';         // it was "\n" which was causing problems
		strcpy(rest, input);
		token = strtok(rest, " \t");

		if(!strcmp(token, "echo"))
			shell_echo(token);
		else if(!strcmp(token, "cd"))
			shell_cd(token, HOME_DIRECTORY);
		else if(!strcmp(token, "pwd"))
			shell_pwd();
		else if(!strcmp(token, "exit"))
			break;
		else if(!strcmp(token, "remindme"))
			reminder(token);
		else
			other_commands(input);
	}
	return 0;
}
