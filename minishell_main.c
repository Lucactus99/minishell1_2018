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

char *remove_useless(char *str)
{
    int i = 0;
    char *new_str;

    for (; str[0] == 32 || str[0] == 9; str++);
    for (; (str[i] != 32 || str[i] != 9) && (str[i + 1] != 32 ||
    str[i + 1] != 9) && str[i] != 0; i++);
    str[i + 1] = 0;
    new_str = malloc(sizeof(char) * my_strlen(str));
    new_str = my_strcpy(new_str, str);
    return (new_str);
}

void main_loop(struct data data)
{
    char *str = malloc(sizeof(char) * 100);
    size_t len;
    int tmp = 0;

    while (tmp != -1) {
        str = malloc(sizeof(char) * 100);
        if (isatty(0))
            my_putstr("§> ");
        tmp = getline(&str, &len, stdin);
        str = remove_useless(str);
        str[my_strlen(str) - 1] = 0;
        if (str != NULL && str[0] != 0 && str[0] != 32) {
            data.program_name = get_program_name(str);
            data.nbr_args = get_nbr_args(str);
            data.args = put_args(str, data.nbr_args);
            find_command(data);
            free_command(data, str);
        }
    }
}

int main(int ac, char **av, char **env)
{
    struct data data;

    if (env == NULL)
        return (84);
    (void)ac;
    (void)av;
    data.path = get_path(env);
    data.env = env;
    main_loop(data);
    return (0);
}