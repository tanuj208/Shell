#include "headers.h"

void shell_jobs(char ** command, int processes[])
{
    int i;
    int cntr = 1;
    for(i = 0;i < 1000; i++)
    {
        char temp[100] = {'\0'};
        char temp2[100] = {'\0'};
        char string_pid[] = "";
        char status[100] = {'\0'};
        char path[PATH_MAX] = "/proc/";
        char name[100] = {'\0'};
        if(processes[i] == -1)
            continue;
        printf("[%d]  ", cntr);
        cntr++;
        sprintf(string_pid, "%d", processes[i]);

        strcat(path, string_pid);
        strcat(path, "/stat");
        FILE *fp = fopen(path, "r");
        fscanf(fp, "%s %s %s", temp, temp2, status);
        if(!strcmp(status, "T"))
            printf("Stopped  ");
        else
            printf("Running  ");

        sprintf(string_pid, "%d", processes[i]);
        strcpy(path, "/proc/");
        strcat(path, string_pid);
        strcat(path, "/cmdline");

        fp = fopen(path, "r");
        fscanf(fp, "%s", name);
        printf("%s[%d]\n", name, processes[i]);
    }
    return;
}