#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

int display(char HOME_DIRECTORY[])
{
	char complete_pathname[PATH_MAX];
	char pathname[PATH_MAX];
	char hostname[HOST_NAME_MAX];
	struct passwd *pw;
	pw = getpwuid(geteuid());

	if(getcwd(complete_pathname, sizeof(complete_pathname)) == NULL)
	{
		printf("Some error occurred in getting cwd\n");
		return -1;
	}
	if(gethostname(hostname, sizeof(hostname)))
	{
		printf("Some error occurred in getting hostname\n");
		return -1;
	}
	int i;
	int flag = 0;
	for(i=0;i<strlen(HOME_DIRECTORY);i++)
	{
		if(HOME_DIRECTORY[i] != complete_pathname[i])
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		pathname[0]='~';
		int k = 1;
		for(i=strlen(HOME_DIRECTORY);i<strlen(complete_pathname);i++)
		{
			pathname[k] = complete_pathname[i];
			k++;
		}
		pathname[k]='\0';
	}
	else
		strcpy(pathname, complete_pathname);
	if(pw)
		printf("<%s@%s:%s> ",pw->pw_name, hostname, pathname);
	else
	{
		printf("Some error occurred in getting username\n");
		return -1;
	}	
	return 0;
}
