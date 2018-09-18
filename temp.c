#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char a[100],b[100],c[100];
	scanf("%s %s %s", a,b,c);
	int fd = open(c, O_RDONLY);
	char **arg=malloc(10);
	arg[0] = a;
	dup2(fd, 0);
	if(fork() == 0)
	{
		execvp(a,arg);
		exit(0);
	}
	return 0;
}