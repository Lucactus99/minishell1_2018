/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_main
*/

#include "my.h"

char *const *put_args(char *av, int nbr_args)
{
    char **tmp = malloc(sizeof(char *) * (nbr_args + 1));
    int j = 0;
    int k = 0;

    for (int i = 0; i <= nbr_args + 1; i++)
        tmp[i] = malloc(sizeof(char) * 20);
    for (int i = 0; av[i] != '\0'; i++) {
        if (av[i] == ' ') {
            j++;
            k = 0;
        } else {
            tmp[j][k] = av[i];
            k++;
        }
    }
    tmp[j + 1] = NULL;
    return (tmp);
}

void print_env(char **env)
{
    for (int i = 0; env[i] != 0 && env[i] != NULL; i++) {
        my_putstr(env[i]);
        my_putchar('\n');
    }
}

int main(int ac, char **av, char **env)
{
    char *str;
    char *program_name;
    int nbr_args;
    char *const *args;
    char **path = get_path(env);

    while (1) {
        my_putstr("§> ");
        str = get_next_line(0);
        program_name = get_program_name(str);
        nbr_args = get_nbr_args(str);
        args = put_args(str, nbr_args);
        if (find_command(program_name, args, env, path) == 1)
            return (0);
        free_command(program_name, args, str);
    }
    return (0);
}