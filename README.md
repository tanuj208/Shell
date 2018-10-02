# Welcome to MyShell!

# Introduction to the project:
I have implemented a terminal-based shell using C language.

Date: 27th September, 2018.
Place: Room 224, Bakul Nivas, IIIT Hyderabad.
Owner: Tanuj Garg

## Features:
- All commands working on real terminal are working.
- current directory of shell is made home directory
- Some commands listed below are implemented separately
    - echo
    - ls
    - cd
    - pwd
    - clock (a clock appears)
    - fg
    - bg
    - jobs (shows status of background processes)
    - kjobs (sends a signal to a particular process)
    - overkill (kills all background processes)
    - pinfo (shows info of a particular process)
    - remindme (reminds user about something after sometime)
- Processes are made background processes when used '&'
- Pipes and redirection are handled properly

## Running the program:
- Go to the working directory and run `make`
- Use `./shell` to start shell

## Description of all files:
- builtin.c
	- echo
	- pwd
	- cd
- clock.c
	- clock
- environment.c
	- setenv
	- unsetenv
- kjobs.c
	- kjobs
- overkill.c
	- overkill
- reminder.c
	- remindme
- shell.c
	- main loop
- display.c
	- display of shell
- fgbg.c
	- fg
	- bg
- jobs.c
	- jobs
- ls.c
	- ls
- othercommands.c
	- system commands and '&'
- pinfo.c
	- pinfo
- redirection_and_pipe.c
	- redirection
	- pipe
	- their combination
- tilda.c
	- setting home directory to current working directory
