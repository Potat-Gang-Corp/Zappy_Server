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
void notice_graphic_client(client_t *cli, char *team_name);
void notice_graphic_init(client_t *cli);
void notice_graphic_move_cmd(client_t *cli);
void notice_graphic_player_ejection(client_t *cli);
void notice_gui_end_incantation(int x, int y, int status);
void notice_gui_incantation(int x, int y, int level, int *tab);
void notice_player_death_event(client_t *cli);
void notice_graphic_client_fork_spawn(int egg_id);

#endif /* !NOTIFICATIONS_H_ */
