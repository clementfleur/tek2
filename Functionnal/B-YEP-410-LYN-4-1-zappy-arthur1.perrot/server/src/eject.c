/*
** EPITECH PROJECT, 2021
** zappy
** File description:
** eject
*/

#include "server.h"

void ejected(server_t *s, map_t *m, dir_t dir)
{
    if (dir == NORTH) {
        if (s->players->y - 1 < 0)
            s->players->y = m->height - 1;
        else
            s->players->y -= 1;
    }
    if (dir == SOUTH) {
        if (s->players->y + 1 > m->height - 1)
            s->players->y = 0;
        else
            s->players->y += 1;
    }
    if (dir == EAST) {
        if (s->players->x + 1 > m->width - 1)
            s->players->x = 0;
        else
            s->players->x += 1;
    }
    if (dir == WEST) {
        if (s->players->x - 1 < 0)
            s->players->x = m->width - 1;
        else
            s->players->x -= 1;
    }
    dprintf(s->gui_fd, "ppo %d %d %d %d\n", s->players->pos, s->players->x,
    s->players->y, s->players->dir);
}

void eject(server_t *s, map_t *m)
{
    int pos;
    dir_t dir;
    int x;
    int y;
    bool found = false;

    go_previous(s);
    for (; s->players->next != NULL; s->players = s->players->next)
        if (s->players->fd == s->acs->player->fd)
            break;
    pos = s->players->pos;
    dir = s->players->dir;
    x = s->players->x;
    y = s->players->y;
    go_previous(s);
    for (; s->players->next != NULL; s->players = s->players->next) {
        if (s->players->x == x && s->players->y == y && s->players->pos != pos) {
            dprintf(s->players->fd, "eject: %d\n", dir);
            ejected(s, m, dir);
            found = true;
        }
    }
    go_pos(s, pos);
    if (found == true)
        dprintf(s->players->fd, "ok\n");
    else
        dprintf(s->players->fd, "ko\n");
}