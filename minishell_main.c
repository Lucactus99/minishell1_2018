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
    tmp[j + 1][0] = '\0';
    tmp[j + 1] = NULL;
    return (tmp);
}

void print_env(char **env)
{
    for (int i = 0; env[i] != 0; i++) {
        my_putstr(env[i]);
        my_putchar('\n');
    }
}

int main(int ac, char **av, char **env)
{
    char *str;
    struct data data;

    (void)ac;
    (void)av;
    data.path = get_path(env);
    data.env = env;
    while (str != NULL) {
        if (isatty(0))
            my_putstr("§> ");
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            data.program_name = get_program_name(str);
            data.nbr_args = get_nbr_args(str);
            data.args = put_args(str, data.nbr_args);
            find_command(data);
            free_command(data, str);
        }
    }
    return (0);
}