/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** msz
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"

void sst_cmd(zappy_server_t *infos, client_t *client, command_t *cmd)
{
    uint16_t freq = infos->freq;

    if (!get_ushort_value(cmd->segments[1], &freq, MIN_FREQ, MAX_FREQ))
        return sbp_event(client);
    infos->freq = freq;
    sgt_all(infos);
}
