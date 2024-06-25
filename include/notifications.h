/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications
*/

#ifndef NOTIFICATIONS_H_
    #define NOTIFICATIONS_H_

    #include "server.h"

/**
* @file notification.h
* @brief defines function for the server to notify the graphic client
*/

/**
 * @brief Notify the graphic client that a player has taken an object
 *
 * @param cli the client that took the object
 * @param type the type of the object
 */
void notice_player_take_object(client_t *cli, item_type_t type);

/**
 * @brief Notify the graphic client that a player has dropped an object
 *
 * @param cli the client that dropped the object
 * @param type the type of the object
 */
void notice_player_set_object(client_t *cli, item_type_t type);

/**
 * @brief Notify the graphic client that a player has died
 *
 * @param cli the client that died
 */
void notice_graphic_egg_destruction(int egg_id);

/**
 * @brief Notify the graphic client when a gui joined
 *
 * @param cli the client that died
 * @param char *team_name the name of the team
 */
void notice_graphic_client(client_t *cli, char *team_name);

/**
 * @brief Notify the graphic client that a gui joined
 *
 * @param cli the client that died
 */
void notice_graphic_init(client_t *cli);

/**
 * @brief Notify the graphic client that a player has moved
 *
 * @param cli the client that died
 */
void notice_graphic_move_cmd(client_t *cli);

/**
 * @brief Notify the graphic client that a player has died
 *
 * @param cli the client that died
 */
void notice_graphic_player_ejection(client_t *cli);

/**
 * @brief Notify the graphic client that the incantation ended
 *
 * @param cli the client that died
 * @param int x the x position of the player
 * @param int y the y position of the player
 * @param int status if it's a success or not
 */
void notice_gui_end_incantation(int x, int y, int status);

/**
 * @brief Notify the graphic client that a player started an incantation
 *
 * @param x the x position of the player
 * @param y the y position of the player
 * @param level the level of the incantation
 * @param tab the tab containing the players in the tile
 */
void notice_gui_incantation(int x, int y, int level, int *tab);

/**
 * @brief Notify the graphic client that a player has died
 *
 * @param cli the client that died
 */
void notice_player_death_event(client_t *cli);

/**
 * @brief Notify the graphic client that a player spawned
 *
 * @param int egg_id the id of the egg that made the player spawn
 */
void notice_graphic_client_fork_spawn(int egg_id);

/**
 * @brief print all the teams eggs
 *
 * @param client_t *cli the GUI client that will receive the message
 */
void print_all_teams_eggs(client_t *cli);

#endif /* !NOTIFICATIONS_H_ */
