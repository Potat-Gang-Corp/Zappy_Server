/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_x_y
*/
#include "../../include/my.h"

void handle_x(int i, char *av)
{
    (void)i;
    (void)av;
    return;
}

void handle_y(int i, char *av)
{
    (void)i;
    (void)av;
    return;
}

void handle_x_y(int ac, int *i, char **av)
{
    if (strcmp(av[(*i)], "-x") == 0) {
            check_av((*i), ac, av);
            handle_x((*i), av[(*i)] + 1);
            i++;
        }
        if (strcmp(av[(*i)], "-y") == 0) {
            check_av((*i), ac, av);
            handle_y((*i), av[(*i)] + 1);
            i++;
        }
}
