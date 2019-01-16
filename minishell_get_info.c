/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_get_info
*/

#include "my.h"

char **put_path(struct data data)
{
    int j;

    for (j = 0; my_strncmp(data.env[j], "PATH", 4) != 0; j++);
    for (int i = 0; i < data.nbr_args; i++) {
        if (i == 0) {
            data.env[j] = my_strcpy(data.env[j], data.path[i]);
            data.env[j] = my_strcat(data.env[j], "=");
        } else
            data.env[j] = my_strcat(data.env[j], data.path[i]);
    }
    return (data.env);
}

char **modify_path(struct data data)
{
    for (int i = 0; data.path[i + 1] != NULL; i++)
        free(data.path[i]);
    for (int i = 0; i < data.nbr_args; i++)
        data.path[i] = malloc(sizeof(char) * 20);
    for (int i = 0; i < data.nbr_args; i++) {
        data.path[i] = my_strcpy(data.path[i], data.args[i + 1]);
    }
    data.env = put_path(data);
    return (data.path);
}

char **get_path(char **env)
{
    char **path;
    int i = 0;
    int a = 0;
    int b = 0;

    for (i = 0; my_strncmp(env[i], "PATH", 4) != 0; i++);
    path = malloc(sizeof(char *) * count_lines(env[i]));
    for (int j = 0; j < count_lines(env[i]); j++)
        path[j] = malloc(sizeof(char) * 20);
    for (int j = i - 1; env[i][j] != 0; j++) {
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