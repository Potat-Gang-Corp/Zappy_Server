/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** read_write_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"

static char *read_cli_cmd(int cli_socket)
{
    char *cmd = malloc(sizeof(char) * (1024 + 1));
    int n = 0;

    if (cmd == NULL)
        return NULL;
    n = read(cli_socket, cmd, 1024);
    if (n < 0) {
        perror("read");
        return NULL;
    }
    cmd[n] = '\0';
    return cmd;
}

int process_cli_cmd(int cli_socket, int index)
{
    char *cmd = read_cli_cmd(cli_socket); //on lit la commande
    //rajouter dans la queue des commandes
    //du coup la vérif osef ?
    if (cmd == NULL) {
        close(cli_socket);
        server_t *server = get_instance();
        server->clients[index].socket = 0;
        fprintf(stderr, "Client disconnected\n");
        return 84;
    }
    printf("Received command: %s\n", cmd);
    //traiter la commande
    return 0;
}

int handle_clients()
{
    server_t *server = get_instance();
    int cli_socket = 0;
    client_t *cli = NULL;
    int index = 0;

    for (cli = server->clients; cli; cli = cli->next) {
        cli_socket = cli->socket;
        if (cli_socket > 0 && FD_ISSET(cli_socket, &server->readfs)) { //si le client est dans le readfs
            process_cli_cmd(cli_socket, index);
        }
        index++;
    }
    return 0;
}
