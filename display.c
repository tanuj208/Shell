#include "headers.h"

int display(char HOME_DIRECTORY[])
{
	char complete_pathname[PATH_MAX] = {'\0'};
	char pathname[PATH_MAX] = {'\0'};
	char hostname[HOST_NAME_MAX] = {'\0'};
	struct passwd *pw;
	pw = getpwuid(geteuid());

	// getting pathname and converting it to relative pathname using convert function
	if(getcwd(complete_pathname, sizeof(complete_pathname)) == NULL)
	{
		printf("Some error occurred in getting cwd\n");
		return -1;
	}
	// getting systemname
	if(gethostname(hostname, sizeof(hostname)))
	{
		printf("Some error occurred in getting hostname\n");
		return -1;
	}
	convert(HOME_DIRECTORY, complete_pathname, pathname);
	// getting username
	if(pw)
		printf("\x1b[1;32m" "<%s@%s:" "\x1b[1;34m" "%s>" "\x1b[1;37m ",pw->pw_name, hostname, pathname);
	else
	{
		printf("Some error occurred in getting username\n");
		return -1;
	}	
	return 0;
}
