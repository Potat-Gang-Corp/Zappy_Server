/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** run_server
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/my.h"

void handle_sigint(int sig)
{
    server_t *server = get_instance();

    (void)sig;
    if (server == NULL)
        return;
    close(server->socket);
    exit(0);
}

int run_server(void)
{
    server_t *server = get_instance();
    clock_t time_req;
    game_t *game = get_instance();

    if (server == NULL)
        return 84;
    printf("server launched on port %d\n", server->port);
    signal(SIGINT, handle_sigint);
    //time_req = clock();
    while (1) {
        select_loop();
        if (FD_ISSET(server->socket, &server->readfs))
            accept_new_client();
        handle_clients(); //la jrecup les commandes
        execute_cli_cmd();
        if (clock() - time_req != 1 / game->freq)
            wait(); // la dedans quand tu vas boucler sur tes commandes, celles deja en cours vont avoir leur cd réduit de 1
    } // ici tu regardes si ta clock moins la clock atm est >= a 1/f sinon boucle jusqu'a l'atteindre
    //okay donc au finale ma vraie question c'était ça, je fais des tours de durée 1/f // c'était ma pièce de puzzle manquante
    //merci je me sent mieux
    return 0;
}
//np