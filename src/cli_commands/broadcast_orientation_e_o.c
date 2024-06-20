/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** broadcast_orientation_e_o
*/

static int east_vertical(int distance_y)
{
    return (distance_y > 0) ? 7 : 3;
}

static int east_horizontal(int distance_x)
{
    if (distance_x < 0) {
        return 5;
    } else if (distance_x > 0) {
        return 1;
    }
    return 0;
}

static int east_diagonal(int distance_x, int distance_y)
{
    if (distance_x < 0) {
        return (distance_y < 0) ? 4 : 6;
    } else if (distance_x > 0) {
        return (distance_y < 0) ? 2 : 8;
    }
    return 0;
}

int compute_direction_east(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return east_vertical(distance_y);
    } else if (distance_y == 0) {
        return east_horizontal(distance_x);
    } else {
        return east_diagonal(distance_x, distance_y);
    }
}

static int west_vertical(int distance_y)
{
    return (distance_y > 0) ? 3 : 7;
}

static int west_horizontal(int distance_x)
{
    if (distance_x < 0) {
        return 1;
    } else if (distance_x > 0) {
        return 5;
    }
    return 0;
}

static int west_diagonal(int distance_x, int distance_y)
{
    if (distance_x < 0) {
        return (distance_y < 0) ? 8 : 2;
    } else if (distance_x > 0) {
        return (distance_y < 0) ? 6 : 4;
    }
    return 0;
}

int compute_direction_west(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return west_vertical(distance_y);
    } else if (distance_y == 0) {
        return west_horizontal(distance_x);
    } else {
        return west_diagonal(distance_x, distance_y);
    }
}
