#ifndef DEFINITIONS
#define DEFINITIONS

// contains definitions of all functions used
int interpretCommands(char ** command, char HOME_DIRECTORY[], int processes[], int *sz_proc);
int display(char HOME_DIRECTORY[]);
void convert(char HOME_DIRECTORY[], char complete_pathname[], char pathname[]);
void convert_to_tilda(char HOME_DIRECTORY[], char pathname[], char complete_pathname[]);
void shell_pinfo(int pid, char HOME_DIRECTORY[]);
void other_commands(char **commandName, int processes[], int *sz_proc);
void reminder(char **token);
void shell_echo(char **token);
void shell_cd(char **token, char HOME_DIRECTORY[]);
void shell_pwd();
void shell_clock(char **token);
void detailedPrint(char filename[], char printableFilename[]);
void print(char *name, int aflag, int lflag);
void shell_ls(char **command, char HOME_DIRECTORY[]);
void setenvir(char **command);
void unsetenvir(char **command);
void shell_jobs(char **command, int processes[]);
void shell_kjobs(char **commands, int processes[]);
void shell_fg(char ** commands, int processes[], int *sz_proc);
void shell_bg(char ** commands, int processes[]);
void shell_overkill(char ** commands, int processes[]);
int redirection_and_pipe(char **command, char HOME_DIRECTORY[], int processes[], int *sz_proc);
#endif
