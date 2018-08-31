#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void print(char *dirname, char *filename, int aflag, int lflag)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return;
}

void shell_ls(char command[])
{
    char *token = NULL;
    int aflag = 0;
    int lflag = 0;
    char *commands[15]={NULL};
    char tempArray[15][PATH_MAX]={'\0'};
    int i = 0;
    int length;
    int c;
    extern char *optarg;
    extern int optind;
    optind = 0;

	token = strtok(command, " \t");
	while(token != NULL)
	{
        strcpy(tempArray[i], token);
        commands[i] = tempArray[i];
		token = strtok(NULL, " \t");
        i++;
	}
    length = i;
    while((c = getopt(length, commands, "la")) != -1)
    {
        switch (c)
        {
            case 'a':
                aflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case '?':
                return;
        }
    }
    return;
}