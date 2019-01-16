/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_

#include <string.h>
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
void do_command(char **, char *, char *const *);
int find_command(struct data);
void print_env(char **);
char **modify_path(struct data);
extern char *strsignal(int __sig) __THROW;

#endif //MY_H_
