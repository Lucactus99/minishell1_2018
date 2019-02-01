/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_command
*/

#include "my.h"

void do_command(struct data data, char *tmp)
{
    int c_pid = fork();
    int status;

    if (c_pid == 0 && data.path[0] != NULL) {
        if (my_strncmp(data.program_name, "./", 2) == 0) {
            data.program_name += 2;
            execve(data.program_name, data.args, data.env);
            my_putstr("./");
            my_putstr(data.program_name);
            my_putstr(": Command not found.\n");
            exit(0);
        }
        if (execve(tmp, data.args, data.env) <= 0) {
            my_putstr(tmp);
            my_putstr(": Pemission denied.\n");
        }
        exit(0);
    } else if (c_pid > 0) {
        wait(&status);
    } else {
        if (data.path[0] != NULL)
            perror("fork failed");
    }
    if (WTERMSIG(status) == 11)
        my_putstr("Segmentation fault (core dumped)\n");
}

int check_error_path(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '/' && (str[i + 1] == '/' || str[i + 1] == '\0'))
            return (1);
    }
    return (0);
}

char *is_existing(struct data data)
{
    char *tmp;
    char *binary = "binary";

    if (my_strncmp(data.program_name, "./", 2) == 0)
        return (binary);
    if (access(data.program_name, F_OK) == 0) {
        tmp = malloc(sizeof(char) * my_strlen(data.program_name) + 1);
        tmp = my_strcpy(tmp, data.program_name);
        return (tmp);
    }
    for (int i = 0; data.path[i] != NULL && data.path[i][0] != 0; i++) {
        tmp = malloc(sizeof(char) * 40);
        tmp = my_strcpy(tmp, data.path[i]);
        tmp = my_strcat(tmp, "/");
        tmp = my_strcat(tmp, data.program_name);
        if (access(tmp, F_OK) == 0 && check_error_path(tmp) == 0)
            return (tmp);
        free(tmp);
    }
    return (NULL);
}

void find_command_3(struct data data)
{
    char *tmp;

    if (my_strcmp(data.program_name, "setenv") == 0) {
        setenv_command(data);
    } else if (my_strcmp(data.program_name, "unsetenv") == 0) {
        unsetenv_command(data);
    } else {
        tmp = is_existing(data);
        if (tmp != NULL) {
            do_command(data, tmp);
        } else {
            my_putstr(data.program_name);
            my_putstr(": Command not found.\n");
        }
    }
}

void find_command_2(struct data data)
{
    if (my_strcmp(data.program_name, "cd") == 0) {
        if (data.args[1] == NULL)
            chdir(get_home(data.env));
        else if (chdir(data.args[1]) < 0) {
            my_putstr(data.args[1]);
            my_putstr(": Not a directory.\n");
        }
    } else if (my_strcmp(data.program_name, "env") == 0) {
        print_env(data.env);
    } else
        find_command_3(data);
}

void find_command(struct data data)
{
    char pwd[128];

    if (my_strcmp(data.program_name, "exit") == 0) {
        my_putstr("exit\n");
        while (1)
            exit(0);
    } else if (my_strcmp(data.program_name, "pwd") == 0) {
        getcwd(pwd, sizeof(pwd));
        my_putstr(pwd);
        my_putchar('\n');
    } else
        find_command_2(data);
}