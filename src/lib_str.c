/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** lib_str
*/

#include "my.h"

int append_to_msg(char **msg, size_t *current_size, const char *new_content)
{
    size_t new_content_length = strlen(new_content);
    size_t current_length = strlen(*msg);
    size_t new_size = current_length + new_content_length + 1;

    if (new_size > *current_size) {
        *msg = realloc(*msg, new_size);
        if (*msg == NULL) {
            perror("realloc");
            return -1;
        }
        *current_size = new_size;
    }
    strcat(*msg, new_content);
    return 0;
}
