/*
** EPITECH PROJECT, 2019
** transform_2d
** File description:
** transform_2d
*/

#include "my.h"

int count_lines(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n' && str[i + 1] != '\0')
            count++;
    }
    return (count);
}

int strlen_line(char *str, int i)
{
    int count = 0;
    int a = 0;

    while (count < i) {
        if (str[a] == '\0')
            return (-1);
        if (str[a] == '\n' && str[a + 1] != '\0')
            count++;
        a++;
    }
    count = 0;
    a++;
    while (str[a] != '\n' && str[a + 1] != '\0') {
        count++;
        a++;
    }
    count++;
    return (count);
}

char **transform_2d(char *str)
{
    char **str_2d = malloc(sizeof(char *) * (count_lines(str) + 1));
    int j = 0;
    int k = 0;

    for (int i = 0; i < count_lines(str) + 1; i++)
        str_2d[i] = malloc(sizeof(char) * (strlen_line(str, i) + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            j++;
            k = 0;
        } else {
            str_2d[j][k] = str[i];
            k++;
        }
    }
    return (str_2d);
}