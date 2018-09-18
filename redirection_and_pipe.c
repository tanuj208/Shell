#include "headers.h"

int redirection_and_pipe(char **command, char HOME_DIRECTORY[])
{
    int i = 0;
    int j = 0;
    int pipes = 0;
    int append = 0;
    int input_redirection = 0;
    int output_redirection = 0;
    int pipePresent = 0;
    char **commands = (char **)malloc(100);
    char *inputFile = NULL, *outputFile = NULL;
    int wrt = 1;
    int flag = 0;
    int anotherFlag = 0;
    int ekaurFlag = 0;

    while(command[i] != NULL)
    {
        if(!strcmp(command[i], "|"))
        {
            pipes++;
            if(command[i + 1] == NULL)
            {
                perror("Invalid syntax\n");
                exit(0);
            }
        }
        if(!strcmp(command[i], "<"))
        {
            input_redirection = 1;
            if(command[i + 1] == NULL)
            {
                perror("Invalid syntax\n");
                exit(0);
            }
            inputFile = command[i + 1];
            pipes = 0;
        }
        if(!strcmp(command[i], ">") || !strcmp(command[i], ">>"))
        {
            if(!strcmp(command[i], ">>"))
                append = 1;
            output_redirection = 1;
            if(command[i + 1] == NULL)
            {
                perror("Invalid syntax\n");
                exit(0);
            }
            outputFile = command[i + 1];
            break;
        }
        i++;
    }

    if(pipes == 0 && input_redirection == 0 && output_redirection == 0)
        return interpretCommands(command, HOME_DIRECTORY);
    // printf("%d %d %d\n", pipes, input_redirection, output_redirection);

    int pip[2*pipes + 2];
    for(i = 0;i < 2*pipes; i += 2)
        pipe(pip + i);
    i = 0;

    if(input_redirection == 0 && pipes > 0)
        flag = 1;
    if(pipes > 0)
        pipePresent = 1;

    while(command[i] != NULL)
    {
        if(input_redirection == 1)
        {
            if(!strcmp(command[i], "|"))
                j = 0;
            if(!strcmp(command[i], "<"))
            {
                flag = 1;
                int fd = open(inputFile, O_RDONLY);
                if(fd < 0)
                {
                    printf("Cannot access '%s': No such file or directory\n", inputFile);
                    return 0;
                }
                if(pipes >= 1)
                {
                    anotherFlag = 1;
                    if(fork() == 0)
                    {
                        int x = dup2(fd, 0);
                        int y = dup2(pip[wrt], 1);
                        close(pip[wrt - 1]);
                        commands[j] = NULL;
                        execvp(commands[0], commands);
                        printf("%s: Command not found\n", commands[0]);
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        close(pip[wrt]);
                    }
                }
                else if(output_redirection == 1)
                {
                    if(fork() == 0)
                    {
                        int x = dup2(fd, 0);
                        if(append == 0)
                        {
                            int fd2 = open(outputFile, O_WRONLY | O_TRUNC | O_CREAT ,0644);
                            if(fd2 < 0)
                            {
                                printf("Cannot access '%s': No such file or directory\n", outputFile);
                                exit(0);
                            }
                            int y = dup2(fd2, 1);
                            commands[j] = NULL;
                            execvp(commands[0], commands);
                            printf("%s: Command not found\n", commands[0]);
                            exit(0);
                        }
                        else
                        {
                            int fd2 = open(outputFile, O_WRONLY | O_APPEND | O_CREAT ,0644);
                            int y = dup2(fd2, 1);
                            commands[j] = NULL;
                            execvp(commands[0], commands);
                            printf("%s: Command not found\n", commands[0]);
                            exit(0);
                        }
                    }
                    return 0;
                }
                else
                {
                    if(fork() == 0)
                    {
                        int x = dup2(fd, 0);
                        commands[j] = NULL;
                        execvp(commands[0], commands);
                        printf("%s: Command not found\n", commands[0]);
                        exit(0);
                    }
                    return 0;
                }
            }
        }
        if((!strcmp(command[i], ">") || !strcmp(command[i], ">>")) && pipePresent == 1)
        {
            if(pipes == 0)
            {
                if(fork() == 0)
                {
                    int fd;
                    int x = dup2(pip[wrt - 1], 0);
                    close(pip[wrt]);
                    if(append == 0)
                    {
                        fd = open(outputFile, O_WRONLY | O_TRUNC | O_CREAT ,0644);
                        if(fd < 0)
                        {
                            printf("Cannot access '%s': No such file or directory\n", outputFile);
                            exit(0);
                        }
                    }
                    else
                    {
                        fd = open(outputFile, O_WRONLY | O_APPEND | O_CREAT ,0644);
                        if(fd < 0)
                        {
                            printf("Cannot access '%s': No such file or directory\n", outputFile);
                            exit(0);
                        }
                    }
                    int y = dup2(fd, 1);
                    commands[j] = NULL;
                    execvp(commands[0], commands);
                    printf("%s: Command not found\n", commands[0]);
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pip[wrt - 1]);
                }
                return 0;
            }
        }
        if(!strcmp(command[i], "|") && flag == 1)
        {
            pipes--;
            if(ekaurFlag == 0 && anotherFlag == 1)
                ekaurFlag = 1;
            else if(anotherFlag == 1)
            {
                wrt += 2;
                if(fork() == 0)
                {
                    commands[j] = NULL;
                    int x = dup2(pip[wrt - 3], 0);
                    int y = dup2(pip[wrt], 1);
                    close(pip[wrt - 1]);
                    close(pip[wrt - 2]);
                    execvp(commands[0], commands);
                    printf("%s: Command not found\n", commands[0]);
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pip[wrt]);
                    close(pip[wrt - 3]);
                }
            }
            else
            {
                anotherFlag = 1;
                ekaurFlag = 1;
                if(fork() == 0)
                {
                    commands[j] = NULL;
                    int x = dup2(pip[wrt], 1);
                    close(pip[wrt - 1]);
                    execvp(commands[0], commands);
                    printf("%s: Command not found\n", commands[0]);
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pip[wrt]);
                }
            }
            j = 0;
        }
        if(input_redirection == 0 && pipePresent == 0)
        {
            if(!strcmp(command[i], ">"))
            {
                int fd = open(outputFile, O_WRONLY | O_TRUNC | O_CREAT ,0644);
                if(fd < 0)
                {
                    printf("Cannot access '%s': No such file or directory\n", outputFile);
                    return 0;
                }
                if(fork() == 0)
                {
                    int y = dup2(fd, 1);
                    commands[j] = NULL;
                    execvp(commands[0], commands);
                    printf("%s: Command not found\n", commands[0]);
                    exit(0);
                }
                return 0;
            }
            else if(!strcmp(command[i], ">>"))
            {
                int fd = open(outputFile, O_WRONLY | O_APPEND | O_CREAT ,0644);
                if(fd < 0)
                {
                    printf("Cannot access '%s': No such file or directory\n", outputFile);
                    return 0;
                }
                if(fork() == 0)
                {
                    int y = dup2(fd, 1);
                    commands[j] = NULL;
                    execvp(commands[0], commands);
                    printf("%s: Command not found\n", commands[0]);
                    exit(0);
                }
                return 0;
            }
        }
        if(strcmp(command[i], "|") && strcmp(command[i], "<") && strcmp(command[i], ">") && strcmp(command[i], ">>"))
        {
            commands[j] = command[i];
            j++;
        }
        i++;
    }
    if(pipePresent == 1 && output_redirection == 0)
    {
        if(fork() == 0)
        {
            commands[j] = NULL;
            int x = dup2(pip[wrt - 1], 0);
            close(pip[wrt]);
            execvp(commands[0], commands);
            printf("%s: Command not found\n", commands[0]);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(pip[wrt- 1]);
        }
    }
    return 0;
}
