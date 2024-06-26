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
#include "commands_gui.h"

/**
* @file run_server.c
* @brief Contains the functions to make the server run
*/

static void notice_client_closing(void)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->graphic == false) {
            dprintf(cli->socket, "Server closed.\n");
            close(cli->socket);
        } else {
            dprintf(cli->socket, "smg Server closed.\n");
            close(cli->socket);
        }
    }
}

void handle_sigint(int sig)
{
    server_t *server = get_instance();

    (void)sig;
    if (server == NULL)
        return;
    printf("\nServer shutting down..\n");
    printf(". . .\nCleaning server data..\n. . .\n");
    notice_client_closing();
    clean_game_struct();
    clean_map_struct();
    clean_client_struct();
    clean_server_data();
    close(server->socket);
    printf("Server closed.\n");
    exit(0);
}

void need_to_sleep(timespec_t *s, timespec_t *end)
{
    game_t *game = get_game_instance();
    long elapsed_ns;
    long interval_ns;

    clock_gettime(CLOCK_MONOTONIC, end);
    elapsed_ns = (end->tv_sec - s->tv_sec) * 1e9 + (end->tv_nsec - s->tv_nsec);
    interval_ns = 1e9 / game->freq;
    if (elapsed_ns >= interval_ns) {
        execute_chrono_tasks();
        clock_gettime(CLOCK_MONOTONIC, s);
    }
}

int server_loop(server_t *server)
{
    select_loop();
    handle_gui_cmd();
    if (FD_ISSET(server->socket, &server->readfs))
        accept_new_client();
    handle_clients();
    execute_cli_cmd();
    return 0;
}

int run_server(void)
{
    server_t *server = get_instance();
    struct timespec start;
    struct timespec end;

    if (server == NULL)
        return 84;
    printf("server launched on port %d\n", server->port);
    signal(SIGINT, handle_sigint);
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (1) {
        server_loop(server);
        need_to_sleep(&start, &end);
    }
    return 0;
}
