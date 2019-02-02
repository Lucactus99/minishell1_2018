/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_command
*/

#include "my.h"

int do_command(struct data data, char *tmp)
{
    int c_pid = fork();
    int status;

    if (c_pid == 0 && data.path[0] != NULL) {
        if (my_strncmp(data.program_name, "./", 2) == 0)
            do_binary(data);
        if (execve(tmp, data.args, data.env) <= 0) {
            my_putstr_err(tmp);
            my_putstr_err(": Permission denied.\n");
        }
        exit(1);
    } else if (c_pid > 0) {
        wait(&status);
    } else {
        if (data.path[0] != NULL)
            perror("fork failed");
    }
    data.exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status) == 1) {
        data.exit_status = status;
        print_error(status);
    }
    return (data.exit_status);
}

void cd_command(struct data data)
{
    char pwd[128];

    if (data.args[1] == NULL) {
        getcwd(pwd, sizeof(pwd));
        data.env = put_old_pwd(data.env, pwd);
        if (chdir(get_home(data.env)) < 0) {
            if (errno == 14)
                my_putstr_err("cd: No home directory.\n");
            else if (errno == 20) {
                my_putstr_err(data.args[1]);
                my_putstr_err(": Not a directory.\n");
            } else
                my_putstr_err("cd: Can't change to home directory.\n");
        }
        return;
    }
    if (my_strcmp(data.args[1], "-") == 0) {
        data.old_pwd = get_old_pwd(data.env);
        if (data.old_pwd == NULL) {
            my_putstr_err(": No such file or directory.\n");
            return;
        }
        getcwd(pwd, sizeof(pwd));
        if (chdir(data.old_pwd) < 0)
            my_putstr_err(": No such file or directory.\n");
        else
            data.env = put_old_pwd(data.env, pwd);
        return;
    }
    getcwd(pwd, sizeof(pwd));
    if (my_strcmp(data.args[1], ".") != 0)
        data.env = put_old_pwd(data.env, pwd);
    if (chdir(data.args[1]) < 0) {
        if (errno == 20) {
            my_putstr_err(data.args[1]);
            my_putstr_err(": Not a directory.\n");
        } else if (errno == 2) {
            my_putstr_err(data.args[1]);
            my_putstr_err(": No such file or directory.\n");
        }
    }
}

int find_command_2(struct data data)
{
    char *tmp;

    if (my_strcmp(data.program_name, "setenv") == 0) {
        setenv_command(data);
    } else if (my_strcmp(data.program_name, "unsetenv") == 0) {
        unsetenv_command(data);
    } else {
        tmp = is_existing(data);
        if (tmp != NULL) {
            data.exit_status = do_command(data, tmp);
        } else {
            my_putstr_err(data.program_name);
            my_putstr_err(": Command not found.\n");
            data.exit_status = 1;
        }
    }
    return (data.exit_status);
}

int find_command(struct data data)
{
    if (my_strcmp(data.program_name, "exit") == 0) {
        if (isatty(0))
            my_putstr("exit\n");
        while (1)
            exit(0);
    } else {
        if (my_strcmp(data.program_name, "cd") == 0)
            cd_command(data);
        else if (my_strcmp(data.program_name, "env") == 0)
            print_env(data.env);
        else
            data.exit_status = find_command_2(data);
    }
    return (data.exit_status);
}