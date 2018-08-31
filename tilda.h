#include <string.h>

// changes string according to tilda and store pathname in 'pathname'
void convert(char HOME_DIRECTORY[], char complete_pathname[], char pathname[])
{
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
}