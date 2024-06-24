/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** time_cmd
*/


#include "my.h"
#include "get_instance.h"

int cmd_sgt(char *command_type, int gui_socket)
{
    game_t *game = get_game_instance();

    (void)command_type;
    dprintf(gui_socket, "sgt %d\n", game->freq);
    return 0;
}

int cmd_sst(char *command_type, int gui_socket)
{
    game_t *game = get_game_instance();
    char *time_parameter = strtok(command_type, " ");
    int time_nb;

    time_parameter = strtok(NULL, " #");
    time_nb = atoi(time_parameter);
    dprintf(gui_socket, "sst %d\n", time_nb);
    game->freq = time_nb;
    return 0;
}
