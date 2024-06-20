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
    if (coord > (axis / 2)) {
        coord = -coord;
    } else if (coord < (-axis / 2)) {
        coord = -coord;
    }
    return coord;
}

static int compute_north_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        if (distance_y < 0)
            return 1;
        if (distance_y > 0)
            return 5;
    }
    if (distance_x < 0) {
        if (distance_y < 0)
            return 2;
        if (distance_y == 0)
            return 3;
        if (distance_y > 0)
            return 4;
    }
    if (distance_x > 0) {
        if (distance_y < 0)
            return 8;
        if (distance_y == 0)
            return 7;
        if (distance_y > 0)
            return 6;
    }
    return 0;
}

static int compute_south_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        if (distance_y < 0)
            return 5;
        if (distance_y > 0)
            return 1;
    }
    if (distance_x < 0) {
        if (distance_y < 0)
            return 6;
        if (distance_y == 0)
            return 7;
        if (distance_y > 0)
            return 8;
    }
    if (distance_x > 0) {
        if (distance_y < 0)
            return 4;
        if (distance_y == 0)
            return 3;
        if (distance_y > 0)
            return 2;
    }
    return 0;
}

static int compute_east_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        if (distance_y > 0)
            return 7;
        if (distance_y < 0)
            return 3;
    }
    if (distance_x < 0) {
        if (distance_y < 0)
            return 4;
        if (distance_y == 0)
            return 5;
        if (distance_y > 0)
            return 6;
    }
    if (distance_x > 0) {
        if (distance_y < 0)
            return 2;
        if (distance_y == 0)
            return 1;
        if (distance_y > 0)
            return 8;
    }
    return 0;
}

static int compute_west_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        if (distance_y > 0)
            return 3;
        if (distance_y < 0)
            return 7;
    }
    if (distance_x < 0) {
        if (distance_y < 0)
            return 8;
        if (distance_y == 0)
            return 1;
        if (distance_y > 0)
            return 2;
    }
    if (distance_x > 0) {
        if (distance_y < 0)
            return 6;
        if (distance_y == 0)
            return 5;
        if (distance_y > 0)
            return 4;
    }
    return 0;
}

static int calculate_direction_bis(int dist_x, int dist_y, int orientation)
{
    switch (orientation) {
        case 0:
            return compute_north_direction(dist_x, dist_y);
        case 1:
            return compute_east_direction(dist_x, dist_y);
        case 2:
            return compute_south_direction(dist_x, dist_y);
        case 3:
            return compute_west_direction(dist_x, dist_y);
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
    int x;
    int y;
    int k;
    client_t *cli;
    server_t *server = get_instance();

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->graphic == false && cli->socket != c_cli->socket) {
            x = c_cli->pos.x - cli->pos.x;
            y = c_cli->pos.y - cli->pos.y;
            k = calculate_direction(x, y, cli->pos.orientation);
            dprintf(cli->socket, "message %d, %s\n", k, message);
        }
        if (cli->graphic == true)
            dprintf(cli->socket, "pbc #%d %s\n", c_cli->socket, message);
        if (cli->socket == c_cli->socket)
            dprintf(cli->socket, "ok\n");
    }
}
