#include "headers.h"

void shell_clock(char** command)
{
    int i,j = 1;
    int tflag = 0;        // for interval
    int nflag = 0;          // for duration
    // flag == 1 -> argument for number of seconds in pending
    while(command[j] != NULL)
    {
        if(!strcmp(command[j], "-t"))
        {
            if(tflag != 0 || nflag == 1)
            {
                perror("Usage: clock -t <interval in digits> -n <duration in digits>\n");
                return;
            }
            tflag++;
            j++;
            continue;
        }
        if(!strcmp(command[j], "-n"))
        {
            if(nflag != 0 || tflag == 1)
            {
                perror("Usage: clock -t <interval in digits> -n <duration in digits>\n");
                return;
            }
            nflag++;
            j++;
            continue;
        }
        if((tflag == 1 && nflag == 1) || (tflag != 1 && nflag != 1))
        {
            perror("Usage: clock -t <interval in digits> -n <duration in digits>\n");
            return;
        }
        for(i = 0;i < strlen(command[j]);i++)
        {
            if(command[j][i] > '9' || command[j][i] < '0')
            {
                perror("Usage: clock -t <interval in digits> -n <duration in digits>\n");
                return;
            }
        }
        if(tflag == 1)
            tflag = atoi(command[j]);
        else
            nflag = atoi(command[j]);
        j++;
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
            char path[20] = "/proc/driver/rtc";
            char clock[50] = {'\0'};
            FILE *fp = fopen(path, "r");
            for(i = 0;i < 6;i++)
            {
                fscanf(fp, "%s", clock);
                if(i == 2 || i == 5)
                    printf("%s ", clock);
            }
            printf("\n");
            if(nflag + initial_time - time(NULL) <= tflag)
                sleep(nflag + initial_time - time(NULL));
            else
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