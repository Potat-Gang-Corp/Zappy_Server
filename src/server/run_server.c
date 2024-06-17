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

void execute_chrono_tasks()
{
    lower_cd();
    lower_life();
    
}

void need_to_sleep(timespec_t *start, timespec_t *end, timespec_t *req)
{
    //CHECK IF IT WORKS
    game_t *game = get_game_instance();
    server_t *server = get_instance();

    clock_gettime(CLOCK_MONOTONIC, end);
    long elapsed_ns = (end->tv_sec - start->tv_sec) * 1e9 + (end->tv_nsec - start->tv_nsec);

    // 1/f en nanosecondes
    long interval_ns = 1e9 / game->freq;

    if (elapsed_ns >= interval_ns) {
        execute_chrono_tasks(server);
        clock_gettime(CLOCK_MONOTONIC, start);  // Reset the clock
    }
}

int server_loop(server_t *server, timespec_t st, timespec_t end, timespec_t r)
{
    //CHECK IF IT WORKS
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
    struct timespec req;

    if (server == NULL)
        return 84;
    printf("server launched on port %d\n", server->port);
    signal(SIGINT, handle_sigint);
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (1) {
        server_loop(server, start, end, req);
        need_to_sleep(&start, &end, &req);
    }
    return 0;
}
