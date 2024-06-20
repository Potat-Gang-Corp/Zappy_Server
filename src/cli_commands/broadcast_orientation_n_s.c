/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** broadcast_orientation_n_s
*/

static int north_vertical(int distance_y)
{
    return (distance_y < 0) ? 1 : 5;
}

static int north_horizontal(int distance_x)
{
    if (distance_x < 0) {
        return 3;
    } else if (distance_x > 0) {
        return 7;
    }
    return 0;
}

static int north_diagonal(int distance_x, int distance_y)
{
    if (distance_x < 0) {
        return (distance_y < 0) ? 2 : 4;
    } else if (distance_x > 0) {
        return (distance_y < 0) ? 8 : 6;
    }
    return 0;
}

int compute_direction_north(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return north_vertical(distance_y);
    } else if (distance_y == 0) {
        return north_horizontal(distance_x);
    } else {
        return north_diagonal(distance_x, distance_y);
    }
}

static int south_vertical(int distance_y)
{
    return (distance_y < 0) ? 5 : 1;
}

static int south_horizontal(int distance_x)
{
    if (distance_x < 0) {
        return 7;
    } else if (distance_x > 0) {
        return 3;
    }
    return 0;
}

static int south_diagonal(int distance_x, int distance_y)
{
    if (distance_x < 0) {
        return (distance_y < 0) ? 6 : 8;
    } else if (distance_x > 0) {
        return (distance_y < 0) ? 4 : 2;
    }
    return 0;
}

int compute_direction_south(int distance_x, int distance_y)
{
    if (distance_x == 0) {
        return south_vertical(distance_y);
    } else if (distance_y == 0) {
        return south_horizontal(distance_x);
    } else {
        return south_diagonal(distance_x, distance_y);
    }
}
