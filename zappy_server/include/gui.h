/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** gui_cmd
*/

#pragma once

    #include "zappy_server.h"
    #include "command.h"

    void msz_event(zappy_server_t* infos, client_t *client);
    void msz_cmd(zappy_server_t *infos, client_t *client,
        command_t *cmd __attribute__((unused)));

    void bct_event(zappy_server_t *infos, client_t *client, int x, int y);
    void bct_all(zappy_server_t *infos, int x, int y);
    void bct_cmd(zappy_server_t *infos, client_t *client, command_t *command);

    void mct_event(zappy_server_t *infos, client_t *client);
    void mct_all(zappy_server_t *infos);
    void mct_cmd(zappy_server_t *infos, client_t *client,
        command_t *cmd __attribute__((unused)));

    void tna_event(zappy_server_t *infos, client_t *client);
    void tna_cmd(zappy_server_t *infos, client_t *client,
        command_t *cmd __attribute__((unused)));

    void pnw_event(ai_t *player, client_t *client);
    void pnw_all(zappy_server_t *infos, ai_t *player);

    bool ppo_event(zappy_server_t *infos, client_t *client, unsigned int id);
    void ppo_all(zappy_server_t *infos, unsigned int id);
    void ppo_cmd(zappy_server_t *infos, client_t *client, command_t *cmd);

    bool plv_event(zappy_server_t *infos, client_t *client, unsigned int id);
    void plv_all(zappy_server_t *infos, unsigned int id);
    void plv_cmd(zappy_server_t *infos, client_t *client, command_t *cmd);

    bool pin_event(zappy_server_t *infos, client_t *client, unsigned int id);
    void pin_all(zappy_server_t *infos, unsigned int id);
    void pin_cmd(zappy_server_t *infos, client_t *client, command_t *cmd);

    void pex_all(zappy_server_t *infos, unsigned int id);

    void pbc_all(zappy_server_t *infos, unsigned int id, char *message);

    void pic_all(zappy_server_t *infos, const incantation_t *incantation);

    void pie_all(zappy_server_t *infos, int x, int y, bool result);

    void pfk_all(zappy_server_t *infos, int id);

    void pdr_all(zappy_server_t *infos, int id, ressources_t ressource);

    void pgt_all(zappy_server_t *infos, int id, ressources_t ressource);

    void pdi_all(zappy_server_t *infos, int id);

    void enw_event(client_t *client, const egg_t *egg);
    void enw_all(zappy_server_t *infos, const egg_t *egg);

    void ebo_all(zappy_server_t *infos, int id);

    void edi_all(zappy_server_t *infos, int id);

    void sgt_event(zappy_server_t *infos, client_t *client);
    void sgt_all(zappy_server_t *infos);
    void sgt_cmd(zappy_server_t *infos, client_t *client,
        command_t *cmd __attribute__((unused)));

    void sst_cmd(zappy_server_t *infos, client_t *client, command_t *cmd);

    void seg_all(zappy_server_t *infos, const char *tean_name);

    void smg_all(zappy_server_t *infos, char *message);

    void suc_event(client_t *client);

    void sbp_event(client_t *client);

    void eht_event(client_t *client, const egg_t *egg);
    void eht_all(zappy_server_t *infos, const egg_t *egg);
