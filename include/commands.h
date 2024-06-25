/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "my.h"

/**
* @file commands.h
* @brief File for the client commands
*/

/**
 * @brief Function to handle the look command
 * @param client_t *cli the client who sent the command
 * @param game_t *game the game structure
 *
 * @details will move the client forward related to his orientation.
 * @return nothing.
 */
void move_player(client_t *cli, game_t *game);

/**
 * @brief Function to handle the fork command
 * @param client_t *cli the client who sent the command.
 *
 * @details will put an egg available on the map and
 * notice the graphic clients.
 * @return nothing.
 */
void client_fork_end(client_t *cli);

/**
 * @brief Function to handle the command sent by the client
 * @param char *cmd the command type
 * @param int cli_socket the client socket
 * @param char *full_cmd the full command sent by the client
 *
 * @details will redirect the program to the right function due
 * to the command type.
 * @return the index of the command in the command table.
 */
int parse_cmd_table(char *cmd, int cli_socket, char *full_cmd);

/**
 * @brief Function to determine the direction to look
 * @param int *x the x position of the client
 * @param int *y the y position of the client
 * @param position_t pos the position entity of the client
 *
 * @details will determine the tiles to observes related to the
 * orientation of the client.
 * @return nothing.
 */
void look_orientation(int *x, int *y, position_t pos, int *stock);

/**
 * @brief Function to append the items to the message
 * @param items_t *item the items to append
 * @param char **msg the current message
 * @param size_t msg_size the size of the message
 *
 * @details will append the items to the message
 * @return 0 if success, 84 if failure.
 */
int cross_items_ll(items_t *item, char **msg, size_t msg_size);
/**
 * @brief Function to check if the message needs a comma
 * @param int offset the offset to check
 * @param char **msg the current message
 * @param size_t msg_size the size of the message
 * @param int cond the condition to check
 *
 * @details will append a comma to the message if a player
 * can see more tiles.
 * @return 0 if success, 84 if failure.
 */
int check_to_append(int offset, char **msg, size_t msg_size, int cond);
/**
 * @brief Function to check content of the tile of the player
 * @param char **msg the current message
 * @param size_t *msg_size the size of the message
 * @param position_t pos the position informations of the player
 *
 * @details will check the content of the tile of the player and
 * append it to the message.
 */
int lvl_zero(char **msg, size_t *msg_size, position_t pos);

/**
 * @brief Function to organize the look command
 * @param char **msg the current message
 * @param map_t *map the map structure
 * @param position_t pos the position informations of the player
 * @param int lvl the level of the player
 *
 * @details will analyze each tile as possible and append the content
 * @return nothing special.
 */
int cmd_lvl(char **msg, map_t *map, position_t pos, int lvl);

/**
 * @brief Function to handle the incantation command
 * @param void
 *
 * @details will launch the incantation process.
 * @return nothing.
 */
void handle_incantation(void);

/**
 * @brief Function to move a player with a specific orientation
 * @param client_t *cli the client who sent the command
 * @param char *command the command sent by the client
 *
 * @details will move a player with a specific orientation
 * @return nothing.
 */
void move_and_restore_orientation(client_t *tmp, game_t *game,
    int new_orientation);

#endif /* !COMMANDS_H_ */
