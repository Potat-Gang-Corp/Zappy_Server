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

/**
 * @brief Function to compute the direction of the broadcast
 * @param int dist_x distance between the two sender and receiver
 * on the x axis
 * @param int dist_y distance between the two sender and receiver
 * on the y axis
 *
 * @details will determine with a matrix the direction of the broadcast
 * related to the orientation of the receiver.
 * @return the orientation value to join the sender.
 */
int compute_direction(int dist_x, int dist_y, orientation_t orientation);

/**
 * @brief Function to correct distance value between the sender and the receiver
 * @param int dist_x distance between the two sender and receiver
 * on the x axis
 * @param int dist_y distance between the two sender and receiver
 * on the y axis
 *
 * @details will determine if the distance is out of bounds and correct it.
 * @return the orientation value to join the sender.
 */
int calculate_direction(int dist_x, int dist_y, orientation_t orientation);

/**
 * @brief Function to send a message to a client
 * @param client_t *cli the sender
 * @param client_t *c_cli the receiver
 * @param int dir the direction of the message
 * @param char *m the message to send
 *
 * @details will send the right message to the receiver due to his role.
 * @return nothing.
 */
void send_message_to_client(client_t *cli, client_t *c_cli, int dir, char *m);

/**
 * @brief Function to send a message to all clients
 * @param client_t *cli the sender
 * @param char *m the message to send
 *
 * @details will send the broadcast message to all clients on the map.
 * @return nothing.
 */
void sending_message(client_t *c_cli, char *message);

/**
 * @brief Function to check if the coordinates are out of bounds
 * @param int coord the coordinate to check
 * @param int axis the axis to check
 *
 * @details will check if the coordinate is out of bounds and correct it.
 * @return the corrected coordinate.
 */
int coord_out_of_bounds(int coord, int axis);

/**
 * @brief Function to order a broadcast action.
 * @param client_t *cli the client who sent the command
 * @param char *command the command sent by the client
 *
 * @details will send a message to all clients on the map,
 * by calculating the direction of the message send.
 */
void sending_message(client_t *cli, char *message);

#endif /* !BROADCAST_H_ */
