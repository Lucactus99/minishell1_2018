/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_useful
*/

#include "my.h"

void free_command(struct data data, char *str)
{
    free(data.program_name);
    free(str);
    for (int i = 1; i < data.nbr_args; i++)
        free(data.args[i]);
}

int count_lines(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ':')
            count++;
    }
    count++;
    return (count);
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

int find_line_env(struct data data)
{
    int line = -1;

    for (int i = 0; data.env[i] != 0; i++) {
        if (my_strncmp(data.env[i], data.args[1], my_strlen(data.args[1])) == 0)
            line = i;
    }
    return (line);
}