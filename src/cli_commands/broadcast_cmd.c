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
    if (coord > 0) {
        coord -= axis;
    } else {
        coord += axis;
    }
    return coord;
}

static int compute_north_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return 1;
    }
    if (distance_x < 0) {
        return (abs(distance_x) >= abs(distance_y)) ? 7 : 8;
    }
    return (abs(distance_x) >= abs(distance_y)) ? 3 : 2;
}

static int compute_south_direction(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return 4;
    }
    if (distance_x < 0) {
        return (abs(distance_x) >= abs(distance_y)) ? 5 : 6;
    }
    return (abs(distance_x) >= abs(distance_y)) ? 3 : 4;
}

static int compute_east_west_direction(int distance_x)
{
    if (distance_x < 0) {
        return 5;
    }
    if (distance_x > 0){
        return 3;
    }
    return 0;
}

static int calculate_direction_bis(int distance_x, int distance_y)
{
    if (distance_y < 0) {
        return compute_north_direction(distance_x, distance_y);
    } else if (distance_y > 0) {
        return compute_south_direction(distance_x, distance_y);
    } else {
        return compute_east_west_direction(distance_x);
    }
}

int calculate_direction(int distance_x, int distance_y)
{
    map_t *map = get_map_instance();

    if (abs(distance_x) > map->width / 2) {
        distance_x = coord_out_of_bounds(distance_x, map->width);
    }
    if (abs(distance_y) > map->height / 2) {
        distance_y = coord_out_of_bounds(distance_y, map->height);
    }
    map->display(map);
    return calculate_direction_bis(distance_x, distance_y);
}

void sending_message(client_t curr_cli, char *message)
{
    int x;
    int y;
    int k;
    client_t *cli;
    server_t *server = get_instance();

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->graphic == false && cli->socket != curr_cli.socket) {
            x = cli->pos.x - curr_cli.pos.x;
            y = cli->pos.y - curr_cli.pos.y;
            k = calculate_direction(x, y);
            dprintf(cli->socket, "message %d, %s\n", k, message);
        }
        if (cli->graphic == true)
            dprintf(cli->socket, "pbc #%d %s\n",
            curr_cli.socket, message);
        if (cli->socket == curr_cli.socket)
            dprintf(cli->socket, "ok\n");
    }
}
