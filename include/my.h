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

void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
int my_put_nbr(int);
char *my_strcpy(char *, char const *);
char *get_next_line(int);
char **transform_2d(char *);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
extern char *strsignal(int __sig) __THROW;

#endif //MY_H_
