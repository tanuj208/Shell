

void convert(char HOME_DIRECTORY[], char complete_pathname[], char pathname[]);
void shell_pinfo(int pid, char HOME_DIRECTORY[]);
void other_commands(char commandName[]);
int display(char HOME_DIRECTORY[]);
void reminder(char *token);
void shell_echo(char *token);
void shell_cd(char *token, char HOME_DIRECTORY[]);
void shell_pwd();
void convert_to_tilda(char HOME_DIRECTORY[], char pathname[], char complete_pathname[]);

