/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** Timer
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

double detect_execution_time(char *command)
{
    game_t *game = get_game_instance();
    double result = 1000000.0;

    if (strcmp(command, "Forward") == 0 || strcmp(command, "Right") == 0 ||
        strcmp(command, "Left") == 0 || strcmp(command, "Look") == 0 ||
        strcmp(command, "Broadcast") == 0 || strcmp(command, "Eject") == 0 ||
        strcmp(command, "Take") == 0 || strcmp(command, "Set") == 0) {
        return 7.0 / game->freq;
    }
    if (strcmp(command, "Inventory") == 0) {
        return 1.0 / game->freq;
    }
    if (strcmp(command, "Fork") == 0) {
        return 42.0 / game->freq;
    }
    if (strcmp(command, "Incantation") == 0) {
        return 300.0 / game->freq;
    }
    return result;
}

double current_time_millis(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
        return ts.tv_sec + (ts.tv_nsec / 1000000000.0);
    }
    return -1;
}
