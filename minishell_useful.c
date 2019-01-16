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