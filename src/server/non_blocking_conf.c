/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** init_server
*/

#include "struct_server.h"
#include "get_instance.h"
#include "my.h"

int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1) {
        return 84;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return 84;
    }
}
