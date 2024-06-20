/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** broadcast_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"
#include "broadcast.h"

int coord_out_of_bounds(int coord, int axis)
{
    if (coord > axis / 2) {
        return coord - axis;
    } else if (coord < -axis / 2) {
        return coord + axis;
    }
    return coord;
}

int compute_direction(int dist_x, int dist_y, orientation_t orientation)
{
    switch (orientation) {
        case NORTH:
            return compute_direction_north(dist_x, dist_y);
        case EAST:
            return compute_direction_east(dist_x, dist_y);
        case SOUTH:
            return compute_direction_south(dist_x, dist_y);
        case WEST:
            return compute_direction_west(dist_x, dist_y);
        default:
            return 0;
    }
}

int calculate_direction(int dist_x, int dist_y, orientation_t orientation)
{
    map_t *map = get_map_instance();

    dist_x = coord_out_of_bounds(dist_x, map->width);
    dist_y = coord_out_of_bounds(dist_y, map->height);
    return compute_direction(dist_x, dist_y, orientation);
}

void send_message_to_client(client_t *cli, client_t *c_cli, int dir, char *m)
{
    if (!cli->graphic && cli->socket != c_cli->socket) {
        dprintf(cli->socket, "message %d, %s\n", dir, m);
    } else if (cli->graphic) {
        dprintf(cli->socket, "pbc #%d %s\n", c_cli->socket, m);
        return;
    }
    if (cli->socket == c_cli->socket) {
        dprintf(cli->socket, "ok\n");
    }
}

void sending_message(client_t *c_cli, char *message)
{
    client_t *cli;
    server_t *server = get_instance();
    int x;
    int y;
    int direction;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        x = c_cli->pos.x - cli->pos.x;
        y = c_cli->pos.y - cli->pos.y;
        direction = calculate_direction(x, y, cli->pos.orientation);
        send_message_to_client(cli, c_cli, direction, message);
    }
}
