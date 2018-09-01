#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include "definitions.h"

void shell_pinfo(int pid, char HOME_DIRECTORY[])
{
    FILE *fp;
    int i;
    char path[PATH_MAX] = "/proc/";
    char copy[PATH_MAX];
    char string_pid[] = "";
    char memory[15];
    char status[5];
    char tmp1[100] = {'\0'};
    char tmp2[100] = {'\0'};
    char exePath[PATH_MAX] = {'\0'};
    char exepath[PATH_MAX] = {'\0'};
    sprintf(string_pid, "%d", pid);

    strcat(path, string_pid);
    strcpy(copy, path);
    strcat(path, "/stat");

    fp = fopen(path, "r");
    // error handling in case pid entered is invalid
    if(fp == NULL)
    {
        printf("There is no process with pid %d\n", pid);
        return;
    }
    // third word of stat file contains current status of process
    fscanf(fp, "%s %s %s", tmp1, tmp2, status);

    strcpy(path, copy);
    strcat(path, "/statm");
    fp = fopen(path, "r");
    if(fp == NULL)
    {
        printf("There is no process with pid %d\n", pid);
        return;
    }
    // first word of statm file contains virtual memory used
    fscanf(fp, "%s", memory);

    strcpy(path, copy);
    strcat(path, "/exe");
    // readlink reads the symlink exe which is pointed to executable path of process
    readlink(path, exepath, sizeof(exepath));
    convert(HOME_DIRECTORY, exepath, exePath);

    printf("pid -- %d\n", pid);
    printf("Process Status -- %s memory\n", status);
    printf("- %s {Virtual Memory}\n", memory);
    printf("- Executable Path - %s\n", exePath);

    return;
}