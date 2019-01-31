/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_env
*/

#include "my.h"

void setenv_command(struct data data)
{
    if (data.nbr_args >= 3) {
        my_putstr("setenv: Too many arguments.\n");
        return;
    }
    if (data.nbr_args == 0)
        print_env(data.env);
    else if (my_strncmp(data.args[1], "PATH", 4) == 0)
        data.path = modify_path(data);
    else
        data.env = set_env(data);
}

void unsetenv_command(struct data data)
{
    if (data.args[1] == NULL) {
        my_putstr("unsetenv: Too few arguments.\n");
    } else if (my_strncmp(data.args[1], "PATH", 4) == 0) {
        data.env = rm_path(data);
    } else
        data.env = unset_env(data);
}

char **set_env(struct data data)
{
    int i = 0;
    int length = find_line_env(data);

    if (length >= 0) {
        for (; data.env[length][i] != '='; i++);
        i++;
        for (int j = i; data.env[length][j + 1] != 0; j++)
            data.env[length][j] = 0;
        for (int j = 2; j <= data.nbr_args; j++)
            data.env[length] = my_strcat(data.env[length], data.args[j]);
    } else
        data.env = add_env(data);
    return (data.env);
}

char **unset_env(struct data data)
{
    int j = 0;
    int length = find_line_env(data);

    if (length >= 0) {
        data.env[length] = NULL;
        for (j = length; data.env[j + 1] != 0; j++)
            data.env[j] = data.env[j + 1];
        data.env[j] = 0;
    }
    return (data.env);
}

char *get_home(char **env)
{
    char *str;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "HOME", 4) == 0) {
            str = malloc(sizeof(char) * my_strlen(env[i]));
            str = my_strcpy(str, env[i]);
        }
    }
    while (str[0] != '=')
        str++;
    str++;
    return (str);
}