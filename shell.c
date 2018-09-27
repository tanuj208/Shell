#include "headers.h"

char HOME_DIRECTORY[PATH_MAX]={'\0'};

void signalHandler(int sig)
{
	return;
}

int main()
{
	int processes[1000];
	int i = 0;
	int sz_proc = 0;
	for(i = 0;i < 1000;i++)
		processes[i] = -1;
	getcwd(HOME_DIRECTORY, sizeof(HOME_DIRECTORY));    // getting the directory where shell.c is present
	while(1)
	{
		char separated_input[15][MAX_INPUT]={'\0'};
		char input[MAX_INPUT]={'\0'};
		char rest[MAX_INPUT]={'\0'};
		char duplicate[MAX_INPUT]={'\0'};
		int length = 0;
		char *token;
		int status;
		int check = waitpid(-1, &status, WNOHANG);
		int x = display(HOME_DIRECTORY);
		signal(SIGINT, signalHandler);
		signal(SIGTSTP, signalHandler);

		if(x==-1)
			return 0;

		if(check > 0)
		{
			if(!WIFEXITED(status))
			{
				for(i = 0;i < 1000;i++)
					if(processes[i] == check)
						processes[i] = -1;
				printf("Process with pid %d exited with exit status : %d\n", check, WEXITSTATUS(status));  // checking for process ending abnormally
			}
		}

		for(i = 0;i < 1000;i++)
		{
			if(kill(processes[i], 0) == -1)
			{
				printf("Process with pid %d exited successfully\n", processes[i]);
				processes[i] = -1;
			}
		}

		i = 0;
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
		int ex = 0;

		// taking each input one by one and separating them on the basis of spaces/tabs
		for(i=0;i<length;i++)
		{
			strcpy(rest, separated_input[i]);
			char **commands=(char **)malloc(1024);
			int j = 0;

			token = strtok(rest, " \t");
			while(token!=NULL)
			{
				commands[j] = token;
				token = strtok(NULL, " \t");
				j++;
			}
			commands[j] = NULL;
			if(commands[0] == NULL)
				continue;

			ex = redirection_and_pipe(commands, HOME_DIRECTORY, processes, &sz_proc);
			if(ex == 1)
				break;
		}
		if(ex == 1)
			break;
	}
	return 0;
}
