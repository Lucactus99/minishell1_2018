/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_options
*/

#include "my.h"

char *remove_useless(char *str)
{
    int i = 0;
    int a = 0;
    char *new_str;

    new_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    for (; str[0] == 32 || str[0] == 9; str++);
    for (; str[i] != 0; i++) {
        if (str[i] == 9)
            str[i] = 32;
        if (((str[i] == 32 || str[i] == 9) && str[i + 1] != 32 &&
        str[i + 1] != 9) || (str[i] != 32 && str[i] != 9)) {
            new_str[a] = str[i];
            a++;
        }
    }
    new_str[a] = 0;
    for (int d = my_strlen(new_str) - 1; new_str[d] == 32; d--)
        new_str[d] = 0;
    return (new_str);
}