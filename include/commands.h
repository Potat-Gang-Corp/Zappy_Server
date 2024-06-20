/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "my.h"

void handle_left_command(client_t *cli);
void handle_right_command(client_t *cli);
void handle_connect_nbr_command(client_t *cli);
void move_player(client_t *cli, game_t *game);
void handle_forward_command(client_t *cli);
void handle_inventory_command(client_t *cli);
void handle_take_command(client_t *cli, char *command);
void handle_set_command(client_t *cli, char *command);
void sending_message(client_t *cli, char *message);

#endif /* !COMMANDS_H_ */
