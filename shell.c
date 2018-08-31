#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "builtin.h"
#include "display.h"
#include "othercommands.h"
#include "reminder.h"
#include "pinfo.h"
#include "tilda.h"
#include "ls.h"

char HOME_DIRECTORY[PATH_MAX]={'\0'};

int main()
{
	getcwd(HOME_DIRECTORY, sizeof(HOME_DIRECTORY));
	while(1)
	{
		char separated_input[15][MAX_INPUT]={'\0'};
		char input[MAX_INPUT]={'\0'};
		char rest[MAX_INPUT]={'\0'};
		char duplicate[MAX_INPUT]={'\0'};
		int i = 0;
		int length = 0;
		char *token;
		// char *tok;
		int x = display(HOME_DIRECTORY);
		if(x==-1)
			return 0;

		fgets(input, MAX_INPUT, stdin);

		input[strlen(input) - 1] = '\0';         // it was "\n" which was causing problems
		strcpy(duplicate, input);

		token = strtok(duplicate, ";");
		while(token != NULL)
		{
			strcpy(separated_input[i], token);
			i++;
			token = strtok(NULL, ";");
		}
		token = NULL;
		length = i;
		for(i=0;i<length;i++)
		{
			strcpy(rest, separated_input[i]);
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
			else if(!strcmp(token, "pinfo"))
			{
				token = strtok(NULL, " \t");
				if(token != NULL)
					shell_pinfo(atoi(token), HOME_DIRECTORY);
				else
					shell_pinfo(getpid(), HOME_DIRECTORY);
			}
			else if(!strcmp(token, "ls"))
				shell_ls(separated_input[i]);
			else
				other_commands(separated_input[i]);
		}
	}
	return 0;
}
