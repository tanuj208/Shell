#include "headers.h"

// changes pathname to relative pathname
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

// changes relative pathname to complete pathname
void convert_to_tilda(char HOME_DIRECTORY[], char pathname[], char complete_pathname[])
{
	strcpy(complete_pathname, HOME_DIRECTORY);
	if(pathname[0] == '~')
		strcat(complete_pathname, pathname + 1);
	else
		strcpy(complete_pathname, pathname);
	return;
}