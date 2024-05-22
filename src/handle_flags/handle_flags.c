/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_flags
*/

#include "../../include/my.h"

/**
* @file handle_flags.c
* @brief function that display_help
*/
void display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1"
    " name2 ... -c clientsNb -f freq\n");
    printf("\t-p port port number\n");
    printf("\t-x width width of the world\n");
    printf("\t-y height height of the world\n");
    printf("\t-n name1 name2 ... name of the team\n");
    printf("\t-c clientsNb number of authorized clients per team\n");
    printf("\t-f freq reciprocal of time unit for execution of actions\n");
    exit(0);
}

/**
* @file handle_flags.c
* @brief function that checks if every flags has a valid definition
*/

void check_av(int i, int ac, char **av)
{
    if (i + 1 >= ac) {
        printf("Chou\n");
        fprintf(stderr, "Error: flag %s has no definition\n", av[i]);
        exit(84);
    }
    if (av[i + 1][0] == '-') {
        fprintf(stderr, "Error: flag %s has no definition\n", av[i]);
        exit(84);
    }
}

/**
* @file handle_p.c
* @brief handle the port 
*/
void handle_p(int i, char *av)
{
    (void)i;
    (void)av;
    return;
}

/**
* @file handle_flags.c
* @brief hub to handle differents flags
*/
int handle_flags(int ac, char **av)
{
    if (ac == 2 && (strcmp(av[1], "-help") == 0 || strcmp(av[1], "-h") == 0))
        display_help();
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0) {
            check_av(i, ac, av);
            handle_p(i, av[i] + 1);
            continue;
        }
        handle_x_y(ac, &i, av);
    }
    return 0;
}
