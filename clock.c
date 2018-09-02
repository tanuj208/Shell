#include "headers.h"

void shell_clock(char* token)
{
    int i;
    int tflag = 0;        // for interval
    int nflag = 0;          // for duration
    // flag == 1 -> argument for number of seconds in pending
    token = strtok(NULL, " \t");
    while(token != NULL)
    {
        // printf("%s\n", token);
        if(!strcmp(token, "-t"))
        {
            if(tflag != 0 || nflag == 1)
            {
                printf("Usage: clock -t <interval> -n <duration>\n");
                return;
            }
            tflag++;
            token = strtok(NULL, " \t");
            continue;
        }
        if(!strcmp(token, "-n"))
        {
            // printf("Fuck\n");
            if(nflag != 0 || tflag == 1)
            {
                printf("Usage: clock -t <interval> -n <duration>\n");
                return;
            }
            nflag++;
            token = strtok(NULL, " \t");
            continue;
        }
        if((tflag == 1 && nflag == 1) || (tflag != 1 && nflag != 1))
        {
            printf("Usage: clock -t <interval> -n <duration>\n");
            return;
        }
        for(i=0;i<strlen(token);i++)
        {
            if(token[i] > '9' || token[i] < '0')
            {
                printf("Usage: clock -t <interval> -n <duration>\n");
                return;
            }
        }
        if(tflag == 1)
            tflag = atoi(token);
        else
            nflag = atoi(token);
        token = strtok(NULL, " \t");
    }
    time_t initial_time = time(NULL);
    int pid = fork();
    if(pid == 0)
    {
        if(nflag == 0)
            nflag = 100000;
        if(tflag == 0)
            tflag = 1;
        while(1)
        {
	        signal(SIGINT, SIG_DFL);
            if(time(NULL) - initial_time >= nflag)
                break;
            time_t time_now = time(NULL);
            char clock[50] = {'\0'};
            strftime(clock, sizeof(clock), "%c", localtime(&time_now));     // localtime converts datatype time_t to tm and strftime converts it into required format
            printf("%s\n", clock);
            if(nflag + initial_time - time(NULL) <= tflag)
                break;
            sleep(tflag);
        }
        kill(getpid(), SIGQUIT);
    }
    else
    {
        int status;
        while(wait(&status) != pid)
            continue;
    }
    return;
}