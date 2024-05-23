/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** handle_n_c_f.c
*/

#include "../../include/my.h"
#include "../../include/handle_flags.h"

/**
* @file handle_n_c_f.c
* @brief handle the n, c and f flags
*/
void handle_n(int ac, int *i, char **av, int *fp)
{
    (*fp) |= 1 << 3;
    printf("Teams: ");
    while (*i + 1 < ac && av[*i + 1][0] != '-') {
        printf("%s ", av[++(*i)]);
    }
    printf("\n");
}

void handle_c(char *av, int *fp)
{
    int nb;
    int i;

    (*fp) |= 1 << 4;
    for (i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            printf("Error: flag -c has no definition\n");
            exit(84);
        }
    }
    nb = atoi(av);
    if (nb <= 0) {
        printf("Error: clients per team should be greater than 0\n");
        exit(84);
    }
    printf("Clients per team: %d\n", nb);
    printf("Clients per team: %s\n", av);
    return;
}

void handle_f(char *av, int *fp)
{
    int nb;
    (*fp) |= 1 << 5;
    for (int i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            printf("Error: flag -f has no definition\n");
            exit(84);
        }
    }
    nb = atoi(av);
    if (nb < 0) {
        printf("Error: frequency should be greater than 0\n");
        exit(84);
    }
    printf("Frequency: %s\n", av);
    return;
}

void handle_n_c_f(int ac, int *i, char **av, int *fp)
{
    if (strcmp(av[(*i)], "-n") == 0) {
        check_av((*i), ac, av);
        handle_n(ac, i, av, fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
    if (strcmp(av[(*i)], "-c") == 0) {
        check_av((*i), ac, av);
        handle_c(av[(*i) + 1], fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
    if (strcmp(av[(*i)], "-f") == 0) {
        check_av((*i), ac, av);
        handle_f(av[(*i) + 1], fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
}
