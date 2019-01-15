/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_main
*/

#include "my.h"

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

char **get_path(char **env)
{
    char **path;
    int i = 0;
    int a = 0;
    int b = 0;

    for (i = 0; my_strncmp(env[i], "PATH", 4) != 0; i++);
    printf("%s\n", env[i]);
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
    printf("%s\n", env[i]);
    printf("%s\n", path[1]);
}

int find_command(char *program_name, char *const *args, char **env)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (my_strcmp(program_name, "exit") == 0)
        return (1);
    if (my_strcmp(program_name, "pwd") == 0) {
        my_putstr(pwd);
        my_putchar('\n');
    }
    if (my_strcmp(program_name, "cd") == 0)
        chdir(args[1]);
    if (my_strcmp(program_name, "env") == 0) {
        print_env(env);
        get_path(env);
    }
    return (0);
}

void free_command(char *program_name, char *const *args, char *str)
{
    free(program_name);
    for (int i = 0; args[i + 1] != NULL; i++)
        free(args[i]);
    free(str);
}

int main(int ac, char **av, char **env)
{
    char *str;
    char *program_name;
    int nbr_args;
    char *const *args;

    while (1) {
        my_putstr("§> ");
        str = get_next_line(0);
        if (str == NULL)
            return (0);
        else {
            program_name = get_program_name(str);
            nbr_args = get_nbr_args(str);
            args = put_args(str, nbr_args);
        }
        if (find_command(program_name, args, env) == 1)
            return (0);
        free_command(program_name, args, str);
    }
    return (0);
}