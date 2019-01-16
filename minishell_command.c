/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_command
*/

#include "my.h"

void do_command(char **path, char *program_name, char *const *args)
{
    int c_pid = fork();
    int status;
    char *tmp;

    if (c_pid == 0) {
        for (int i = 0; path[i] != NULL; i++) {
            tmp = malloc(sizeof(char) * 20);
            tmp = my_strcat(path[i], "/");
            execve(my_strcat(tmp, program_name), args, NULL);
            free(tmp);
        }
    } else if (c_pid > 0) {
        if (wait(&status) < 0)
            perror("wait");
    } else
        perror("fork failed");
    if (status != 0)
        my_putstr("Command not found.\n");
}

int find_command_2(struct data data)
{
    if (my_strcmp(data.program_name, "env") == 0) {
        print_env(data.env);
        return (0);
    }
    if (my_strcmp(data.program_name, "setenv") == 0) {
        if (data.nbr_args < 2)
            return (0);
        data.path = modify_path(data);
        return (0);
    } else
        do_command(data.path, data.program_name, data.args);
    return (0);
}

int find_command(struct data data)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (my_strcmp(data.program_name, "exit") == 0)
        return (1);
    if (my_strcmp(data.program_name, "pwd") == 0) {
        my_putstr(pwd);
        my_putchar('\n');
        return (0);
    }
    if (my_strcmp(data.program_name, "cd") == 0) {
        chdir(data.args[1]);
        return (0);
    }
    return (find_command_2(data));
}