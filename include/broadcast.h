/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** broadcast_orientation
*/

#ifndef BROADCAST_H_
    #define BROADCAST_H_

    #include "struct_server.h"
    #include "get_instance.h"
    #include "my.h"
    #include "server.h"
    #include "struct_client.h"

int compute_direction(int dist_x, int dist_y, orientation_t orientation);
int calculate_direction(int dist_x, int dist_y, orientation_t orientation);
void send_message_to_client(client_t *cli, client_t *c_cli, int dir, char *m);
void sending_message(client_t *c_cli, char *message);

int coord_out_of_bounds(int coord, int axis);
int compute_direction_west(int dist_x, int dist_y);
int compute_direction_east(int dist_x, int dist_y);
int compute_direction_south(int dist_x, int dist_y);
int compute_direction_north(int dist_x, int dist_y);

#endif /* !BROADCAST_H_ */
