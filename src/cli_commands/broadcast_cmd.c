/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** fork_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"

static int coord_out_of_bounds(int coord, int axis)
{
    if (coord > axis / 2) {
        coord -= axis;
    } else if (coord < -axis / 2) {
        coord += axis;
    }
    return coord;
}

static int compute_north_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) return 1;
    if (distance_x < 0) return (abs(distance_x) >= abs(distance_y)) ? 7 : 8;
    return (abs(distance_x) >= abs(distance_y)) ? 3 : 2;
}

static int compute_south_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) return 5;
    if (distance_x < 0) return (abs(distance_x) >= abs(distance_y)) ? 7 : 6;
    return (abs(distance_x) >= abs(distance_y)) ? 3 : 4;
}

static int compute_east_direction(int distance_x, int distance_y)
{
    if (distance_y == 0) return 3;
    if (distance_y < 0) return (abs(distance_y) >= abs(distance_x)) ? 1 : 2;
    return (abs(distance_y) >= abs(distance_x)) ? 5 : 4;
}

static int compute_west_direction(int distance_x, int distance_y)
{
    if (distance_y == 0) return 7;
    if (distance_y < 0) return (abs(distance_y) >= abs(distance_x)) ? 1 : 8;
    return (abs(distance_y) >= abs(distance_x)) ? 5 : 6;
}

static int calculate_direction_bis(int distance_x, int distance_y, int orientation)
{
    switch (orientation) {
        case 0: // NORTH
            return compute_north_direction(distance_x, distance_y);
        case 1: // EAST
            return compute_east_direction(distance_x, distance_y);
        case 2: // SOUTH
            return compute_south_direction(distance_x, distance_y);
        case 3: // WEST
            return compute_west_direction(distance_x, distance_y);
    }
    return 0;
}

int calculate_direction(int distance_x, int distance_y, int orientation)
{
    map_t *map = get_map_instance();

    distance_x = coord_out_of_bounds(distance_x, map->width);
    distance_y = coord_out_of_bounds(distance_y, map->height);

    return calculate_direction_bis(distance_x, distance_y, orientation);
}

void sending_message(client_t *c_cli, char *message)
{
    int x, y, k;
    client_t *cli;
    server_t *server = get_instance();

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->graphic == false && cli->socket != c_cli->socket) {
            x = cli->pos.x - c_cli->pos.x;
            y = cli->pos.y - c_cli->pos.y;
            k = calculate_direction(x, y, cli->pos.orientation);
            dprintf(cli->socket, "message %d, %s\n", k, message);
        }
        if (cli->graphic == true)
            dprintf(cli->socket, "pbc #%d %s\n", c_cli->socket, message);
        if (cli->socket == c_cli->socket)
            dprintf(cli->socket, "ok\n");
    }
}
