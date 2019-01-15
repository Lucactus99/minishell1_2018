/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_useful
*/

#include "my.h"

void free_command(char *program_name, char *const *args, char *str)
{
    free(program_name);
    for (int i = 0; args[i + 1] != NULL; i++)
        free(args[i]);
    free(str);
}

int count_lines_path(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ':')
            count++;
    }
    count++;
    return (count);
}