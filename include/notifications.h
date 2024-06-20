/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications
*/

#ifndef NOTIFICATIONS_H_
    #define NOTIFICATIONS_H_

    #include "server.h"

void notice_player_take_object(client_t *cli, item_type_t type);
void notice_player_set_object(client_t *cli, item_type_t type);
void notice_graphic_egg_destruction(int egg_id);

#endif /* !NOTIFICATIONS_H_ */
