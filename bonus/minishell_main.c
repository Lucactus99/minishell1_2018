/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_main
*/

#include "my.h"

void do_binary(struct data data)
{
    data.program_name += 2;
    execve(data.program_name, data.args, data.env);
    my_putstr_err("./");
    my_putstr_err(data.program_name);
    my_putstr_err(": Command not found.\n");
    exit(0);
}

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

void main_loop(struct data data)
{
    char *str = "lucas";
    char pwd[128];

    while (str != NULL && my_strcmp(str, "exit") != 0) {
        if (isatty(0)) {
            getcwd(pwd, sizeof(pwd));
            my_putstr("\033[1;36m");
            my_putstr(pwd);
            my_putstr("\033[0m ");
            my_putstr("\033[01;33m§> \033[0m");
        }
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            str = remove_useless(str);
            data.program_name = get_program_name(str);
            data.nbr_args = get_nbr_args(str);
            data.args = put_args(str, data.nbr_args);
            find_command(data);
            free_command(data, str);
        }
    }
}

char **new_path_to_env(char **env)
{
    int j = 0;

    for (; env[j] != NULL; j++);
    env[j] = malloc(sizeof(char) * 50);
    env[j] = my_strcpy(env[j],
    "PATH=/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin");
    env[j + 1] = 0;
    return (env);
}

int main(int ac, char **av, char **env)
{
    struct data data;

    if (env == NULL)
        return (84);
    (void)ac;
    (void)av;
    data.path = get_path(env);
    if (data.path == NULL) {
        env = new_path_to_env(env);
        data.path = get_path(env);
    }
    data.env = env;
    main_loop(data);
    return (0);
}