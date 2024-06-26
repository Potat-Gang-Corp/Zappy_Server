/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications_incantation
*/

#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

/**
* @file notifications_incantation.c
* @brief Contains the functions that send notifications to the graphic clients
* especially for the incantation command
*/

bool append_to_message(char **msg, size_t *msg_size, int *length, int value)
{
    size_t needed = *length + snprintf(NULL, 0, " #%d", value) + 1;
    int ret;
    char *new_message;

    if (needed > *msg_size) {
        new_message = realloc(*msg, needed);
        if (!new_message) {
            free(*msg);
            return false;
        }
        *msg = new_message;
        *msg_size = needed;
    }
    ret = snprintf(*msg + *length, *msg_size - *length, " #%d", value);
    if (ret < 0) {
        free(*msg);
        return false;
    }
    *length += ret;
    return true;
}

void send_incantation_message(client_t *cli, const char *message)
{
    for (; cli != NULL; cli = cli->next) {
        if (cli->graphic && dprintf(cli->socket, "%s", message) < 0) {
            perror("dprintf");
        }
    }
}

bool handle_error(char **msg, const char *error_msg)
{
    free(*msg);
    perror(error_msg);
    return false;
}

static char *follow(int *tab, char **msg, size_t s, int length)
{
    if (length < 0) {
        handle_error(msg, "snprintf");
        return NULL;
    }
    for (int i = 0; tab[i] != -1; i++) {
        if (!append_to_message(msg, &s, &length, tab[i]))
            return NULL;
    }
    if (snprintf((*msg) + length, s - length, "\n") < 0) {
        handle_error(msg, "snprintf");
        return NULL;
    }
    return *msg;
}

char *build_incantation_message(int x, int y, int level, int *tab)
{
    size_t s = 32;
    char *msg = malloc(sizeof(char) * s);
    int length;

    if (!msg) {
        handle_error(&msg, "malloc");
        return NULL;
    }
    length = snprintf(msg, s, "pic %d %d %d", x, y, level);
    if (follow(tab, &msg, s, length) == NULL)
        return NULL;
    return msg;
}

void notice_gui_incantation(int x, int y, int level, int *tab)
{
    client_t *cli = get_instance()->clients;
    char *message = build_incantation_message(x, y, level, tab);

    if (message) {
        send_incantation_message(cli, message);
        free(message);
    }
}
