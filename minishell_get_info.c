/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_get_info
*/

#include "my.h"

char **get_path(char **env)
{
    char **path;
    int i = 0;
    int a = 0;
    int b = 0;

    for (i = 0; my_strncmp(env[i], "PATH", 4) != 0; i++);
    for (int j = 0; j < i - 1; j++)
        env[i]++;
    path = malloc(sizeof(char *) * count_lines_path(env[i]));
    for (int j = 0; j < count_lines_path(env[i]); j++)
        path[j] = malloc(sizeof(char) * 20);
    for (int j = 0; env[i][j] != 0; j++) {
        if (env[i][j] == ':') {
            a++;
            b = 0;
        } else {
            path[a][b] = env[i][j];
            b++;
        }
    }
    return (path);
}

char *get_program_name(char *av)
{
    char *str;
    int i = 0;
    int j = 0;

    for (; av[i] != ' ' && av[i] != '\0'; i++);
    str = malloc(sizeof(char) * (i + 1));
    for (; j < i; j++)
        str[j] = av[j];
    str[j] = '\0';
    return (str);
}

int get_nbr_args(char *av)
{
    int count = 0;

    for (int i = 0; av[i] != 0; i++) {
        if (av[i] == ' ')
            count++;
    }
    return (count);
}