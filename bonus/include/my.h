/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_
#define GNU_SOURCE

#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


struct data
{
    char *program_name;
    int nbr_args;
    char *const *args;
    char **path;
    char *old_pwd;
    char **env;
};


void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
int my_put_nbr(int);
char *my_strcpy(char *, char const *);
char *get_next_line(int);
int my_strcmp(char const *, char const *);
char *my_strcat(char *, char const *);
int my_strncmp(char const *, char const *, int);
void free_command(struct data, char *);
int count_lines(char *);
char **get_path(char **);
char *get_program_name(char *);
int get_nbr_args(char *);
void do_command(struct data, char *);
void find_command(struct data);
void print_env(char **);
char **modify_path(struct data);
char **put_path(struct data);
char **rm_path(struct data);
int kill(pid_t pid, int sig);
char **add_env(struct data);
int find_line_env(struct data);
char **set_env(struct data);
char **unset_env(struct data);
char *get_home(char **);
void setenv_command(struct data);
void unsetenv_command(struct data);
char *get_old_pwd(char **);
char **put_old_pwd(char **, char *);
void my_putchar_err(char);
int my_putstr_err(char const *);
char *is_existing(struct data);
void do_binary(struct data);
char *remove_useless(char *);

#endif //MY_H_