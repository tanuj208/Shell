#include "headers.h"

char HOME_DIRECTORY[PATH_MAX]={'\0'};

int main()
{
	signal(SIGINT, SIG_IGN);
	getcwd(HOME_DIRECTORY, sizeof(HOME_DIRECTORY));    // getting the directory where shell.c is present
	while(1)
	{
		char separated_input[15][MAX_INPUT]={'\0'};
		char input[MAX_INPUT]={'\0'};
		char rest[MAX_INPUT]={'\0'};
		char duplicate[MAX_INPUT]={'\0'};
		int i = 0;
		int length = 0;
		int exit = 0;
		char *token;
		int status;
		int check = waitpid(-1, &status, WNOHANG);
		int x = display(HOME_DIRECTORY);

		if(x==-1)
			return 0;

		if(check > 0)
			if(!WIFEXITED(status))
				printf("Process with pid %d exited with exit status : %d\n", check, WEXITSTATUS(status));  // checking for process ending abnormally

		fgets(input, MAX_INPUT, stdin);

		input[strlen(input) - 1] = '\0';         // it was "\n" which was causing problems
		strcpy(duplicate, input);           // making duplicate so that original input remains unaffected by strtok
		
		// first separating commands on the basis of ; and storing them in separated_input array
		token = strtok(duplicate, ";");
		while(token != NULL)
		{
			strcpy(separated_input[i], token);
			i++;
			token = strtok(NULL, ";");
		}
		token = NULL;
		length = i;

		// taking each input one by one and separating them on the basis of spaces/tabs
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
			{
				exit = 1;
				break;
			}
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
				shell_ls(separated_input[i], HOME_DIRECTORY);
			else if(!strcmp(token, "clock"))
				shell_clock(token);
			else
				other_commands(separated_input[i]);
		}
		if(exit == 1)
			break;
	}
	return 0;
}
