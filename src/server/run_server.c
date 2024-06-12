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

void handle_sigint(int sig)
{
    server_t *server = get_instance();

    (void)sig;
    if (server == NULL)
        return;
    clean_game_struct();
    clean_map_struct();
    clean_client_struct();
    clean_server_data();
    close(server->socket);
    exit(0);
}

void need_to_sleep(timespec_t start, timespec_t end, timespec_t req)
{
    //CHECK IF IT WORKS
    game_t *game = get_game_instance();
    long calc = (end.tv_nsec - start.tv_nsec);
    long elapsed_ns = calc < 0 ? 1e9 + calc : calc;
    long sleep_ns = (1e9 / game->freq) - elapsed_ns;

    if (sleep_ns > 0) {
        req.tv_sec = sleep_ns / 1e9;
        req.tv_nsec = sleep_ns % (long)1e9;
        nanosleep(&req, NULL);
    }
}

int server_loop(server_t *server, timespec_t st, timespec_t end, timespec_t r)
{
    //CHECK IF IT WORKS
    select_loop();
    handle_gui_cmd();
    clock_gettime(CLOCK_MONOTONIC, &st);
    if (FD_ISSET(server->socket, &server->readfs))
        accept_new_client();
    handle_clients();
    execute_cli_cmd();
    clock_gettime(CLOCK_MONOTONIC, &end);
    need_to_sleep(st, end, r);
    return 0;
}

int run_server(void)
{
    server_t *server = get_instance();
    struct timespec start;
    struct timespec end;
    struct timespec req;

    if (server == NULL)
        return 84;
    printf("server launched on _cmdport %d\n", server->port);
    signal(SIGINT, handle_sigint);
    while (1) {
        server_loop(server, start, end, req);
    }
    return 0;
}
