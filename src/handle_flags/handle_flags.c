/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_flags
*/

#include "../../include/my.h"
#include "../../include/handle_flags.h"
#include "../../include/get_instance.h"

/**
* @file handle_flags.c
* @brief functions to handle the flags, hub and error handling part
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

void check_av(int i, int ac, char **av)
{
    if (i + 1 >= ac) {
        fprintf(stderr, "Error: flag %s has no definition\n", av[i]);
        exit(84);
    }
    if (av[i + 1][0] == '-') {
        fprintf(stderr, "Error: flag %s has no definition\n", av[i]);
        exit(84);
    }
}

void handle_fp(int flags_present)
{
    int required_flags = 0x1F;

    if ((flags_present & required_flags) != required_flags) {
            fprintf(stderr, "Error: missing required flags:\n");
        if (!(flags_present & (1 << 0)))
            fprintf(stderr, "-p flag is missing\n");
        if (!(flags_present & (1 << 1)))
            fprintf(stderr, "-x flag is missing\n");
        if (!(flags_present & (1 << 2)))
            fprintf(stderr, "-y flag is missing\n");
        if (!(flags_present & (1 << 3)))
            fprintf(stderr, "-n flag is missing\n");
        if (!(flags_present & (1 << 4)))
            fprintf(stderr, "-c flag is missing\n");
        exit(84);
    }
}

int handle_flags(int ac, char **av)
{
    int flags_present = 0;
    int i;
    game_t *game = get_game_instance();

    if (ac == 2 && (strcmp(av[1], "-help") == 0 || strcmp(av[1], "-h") == 0))
        display_help();
    for (i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0) {
            check_av(i, ac, av);
            handle_p(av[i + 1]);
            flags_present |= 1 << 0;
            continue;
        }
        handle_x_y(ac, &i, av, &flags_present);
        handle_n_c_f(ac, &i, av, &flags_present);
    }
    handle_fp(flags_present);
    if (flags_present & (1 << 5))
        game->freq = 100;
    return 0;
}
