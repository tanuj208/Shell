#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pip[2];
	char *command[] = {"more", "file.txt", NULL};
	char *cc[] = {"wc", NULL};
	pipe(pip);
	if(fork() == 0)
	{
		dup2(pip[1], 1);
		close(pip[0]);
		execvp("more", command);
		exit(0);
	}
	if(fork() == 0)
	{
		dup2(pip[0], 0);
		close(pip[1]);
		execvp("wc",cc);
		exit(0);
	}
	return 0;
}