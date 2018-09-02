shell.c  ==> main file
builtin.c ==> contains implementation of cd, echo and pwd commands
clock.c ==> implementation of clock (bonus) command
definitions.h ===> contains definition of all functions used
display.c ===> contains code for prompt display
header.h ===> contains all headers
ls.c ===> contains implementation of ls command
reminder.c ===> contains implementation of reminme (bonus) command
tilda.c ===> contains functions to convert a relative path to absolute and vice-versa
Type make to compile all files and use ./shell to start shell
clock command can be exited using ctrl C but using ctrl Z will exit the shell
time(NULL) is used only to tackle the problem of total time flag. Total time flag is optional if ctrl C can exit the clock.
