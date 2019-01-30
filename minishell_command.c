/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_command
*/

#include "my.h"

void display_command_errors(char *program_name, int status)
{
    if (status != 0) {
        my_putstr(program_name);
        my_putstr(": Command not found.\n");
    }
}

void do_command(struct data data)
{
    int c_pid = fork();
    int pid = getpid();
    int status;
    char *tmp;

    if (c_pid == 0 && data.path[0] != NULL) {
        if (my_strncmp(data.program_name, "./", 2) == 0) {
            data.program_name += 2;
            execve(data.program_name, data.args, data.env);
            return;
        }
        for (int i = 0; data.path[i] != NULL; i++) {
            tmp = malloc(sizeof(char) * 20);
            tmp = my_strcat(data.path[i], "/");
            execve(my_strcat(tmp, data.program_name), data.args, data.env);
            free(tmp);
        }
    } else if (c_pid > 0) {
        if (data.path[0] != NULL)
            wait(&status);
        kill(c_pid, SIGKILL);
    } else {
        if (data.path[0] != NULL)
            perror("fork failed");
    }
    display_command_errors(data.program_name, status);
}

void find_command_3(struct data data)
{
    if (my_strcmp(data.program_name, "unsetenv") == 0) {
        if (data.args[1] == NULL) {
            my_putstr("unsetenv: Too few arguments.\n");
        } else if (my_strncmp(data.args[1], "PATH", 4) == 0) {
            data.path[0] = NULL;
            data.env = rm_path(data);
        } else
            data.env = unset_env(data);
        return;
    } else
        do_command(data);
}

void find_command_2(struct data data)
{
    if (my_strcmp(data.program_name, "setenv") == 0) {
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
        return;
    }
    find_command_3(data);
}

void find_command(struct data data)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (my_strcmp(data.program_name, "exit") == 0) {
        my_putstr("exit\n");
        exit(0);
    }
    if (my_strcmp(data.program_name, "pwd") == 0) {
        my_putstr(pwd);
        my_putchar('\n');
        return;
    }
    if (my_strcmp(data.program_name, "cd") == 0) {
        if (data.args[1] == NULL)
            chdir(get_home(data.env));
        else if (chdir(data.args[1]) < 0) {
            my_putstr(data.args[1]);
            my_putstr(": No such file or directory.\n");
        }
        return;
    }
    if (my_strcmp(data.program_name, "env") == 0) {
        print_env(data.env);
        return;
    }
    find_command_2(data);
}