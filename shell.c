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

			ex = redirection_and_pipe(commands, HOME_DIRECTORY);
			if(ex == 1)
				break;
		}
		if(ex == 1)
			break;
	}
	return 0;
}
