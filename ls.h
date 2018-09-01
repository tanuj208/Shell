#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// function to handle when lflag is one
void detailedPrint(char filename[], char printableFilename[])
{
    struct passwd *pws;
    struct group *grp;
    int x;
    int tm_sec = 1;
    char time[50] = {'\0'};
    struct stat st = {0};
    stat(filename, &st);

    x = st.st_mode;
    // checking if file is directory or link or a file
    if(S_ISDIR(x))
        printf("d");
    else if(S_ISREG(x))
        printf("-");
    else
        printf("l");

    // checking read/write/execute permissions for user/group/others
    if(x & S_IRUSR)
        printf("r");
    else
        printf("-");
    if(x & S_IWUSR)
        printf("w");
    else
        printf("-");
    if(x & S_IXUSR)
        printf("x");
    else
        printf("-");
    if(x & S_IRGRP)
        printf("r");
    else
        printf("-");
    if(x & S_IWGRP)
        printf("w");
    else
        printf("-");
    if(x & S_IXGRP)
        printf("x");
    else
        printf("-");
    if(x & S_IROTH)
        printf("r");
    else
        printf("-");
    if(x & S_IWOTH)
        printf("w");
    else
        printf("-");
    if(x & S_IXOTH)
        printf("x ");
    else
        printf("- ");

    // getting username and group owner name
    pws = getpwuid(st.st_uid);
    grp = getgrgid(st.st_gid);

    // getting last modified time and converting it to appropriate format
    strftime(time, sizeof(time), "%b %d %H:%M", localtime(&st.st_mtime));     // localtime converts datatype time_t to tm and strftime converts it into required format

    printf("%d %s %s %d %s %s\n",(int)st.st_nlink, pws -> pw_name, grp -> gr_name, (int)st.st_size, time, printableFilename);
    return;
}

void print(char *name, int aflag, int lflag)
{
    int isDirectory = 0;
    struct stat st = {0};
    if(name == NULL)
        name = ".";
    // checking if name consists name of a directory or a file
    stat(name, &st);
    if(S_ISDIR(st.st_mode))
        isDirectory = 1;
    if(isDirectory)
    {
        char duplicate[PATH_MAX]={'\0'};
        DIR *d;
        struct dirent *dir;
        // if last character is not '/' then appending string with '/'
        if(name[strlen(name) - 1] != '/')
        {
            int sz = strlen(name);
            char * newname = malloc(sz + 2);
            strcpy(newname, name);
            newname[sz] = '/';
            newname[sz + 1] = '\0';
            name = newname;
        }
        strcpy(duplicate, name);
        d = opendir(name);
        if(d && lflag == 0)
        {
            while ((dir = readdir(d)) != NULL)
                if((dir -> d_name[0] == '.' && aflag == 1) || (dir -> d_name[0] != '.'))   // if hidden then show only if aflag is one
                    printf("%s\n", dir->d_name);
            closedir(d);
        }
        else if(d && lflag == 1)
        {
            while((dir = readdir(d)) != NULL)
            {
                if((dir -> d_name[0] == '.' && aflag == 1) || (dir -> d_name[0] != '.'))
                {
                    strcat(duplicate, dir -> d_name);
                    detailedPrint(duplicate, dir -> d_name);
                    strcpy(duplicate, name);
                }
            }
        }
    }
    else
    {
        if(lflag == 0)
            printf("%s\n", name);
        else
            detailedPrint(name, name);
    }
    return;
}

void shell_ls(char command[], char HOME_DIRECTORY[])
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
    int flag = 0;
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
    // using getopt to detect whether -l or -a flags are used in command
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
    // checking for each word in command and if it is directory/file/link then printing info about it
    for(i = 0;i < length;i++)
    {
        if(strcmp(commands[i], "ls") && (commands[i][0] != '-' || strlen(commands[i]) == 1))
        {
            char realPath[PATH_MAX] = {'\0'};
            convert_to_tilda(HOME_DIRECTORY, commands[i], realPath);
            flag = 1;
            struct stat st = {0};
            int x = stat(realPath, &st);
            if(x < 0)
                printf("ls: cannot access '%s': No such file or directory\n", commands[i]);
            else
            {
                printf("%s:\n", commands[i]);
                print(realPath, aflag, lflag);
            }
        }
    }
    // if no directory/file/link name is written after ls then printing info about all files in current directory
    if(flag == 0)
        print(NULL, aflag, lflag);
    return;
}