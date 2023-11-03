# Zappy Server

A server, created in C, that generates the inhabitants’ world.

## Usage

```sh
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq --auto-start on|off --display-eggs true|false
	port		is the port number
	width		is the width of the world
	height		is the height of the world
	nameX		is the name of the team X
	clientsNb	is the number of authorized clients per team
	freq		is the reciprocal of time unit for execution of actions
	auto-start	does the greeting is send automaticly #(see bonus part)
	display-eggs	eggs are visible and destructible
```

|                   SERVER                   |   CLIENT  |                    DETAILS                    |    TO A GUI client    |    TO ALL GUI client    |
|:------------------------------------------:|:---------:|:---------------------------------------------:|:---------------------:|:-----------------------:|
|                  msz X Y\n                 |   msz\n   |                   map size                    | new GUI client connection or msz command | |
|       bct X Y q0 q1 q2 q3 q4 q5 q6\n       | bct X Y\n |               content of a tile               | bct command | |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles |   mct\n   |       content of the map (all the tiles)      | new GUI client connection or mct command or map refill | |
|             tna N\n * nbr_teams            |   tna\n   |             name of all the teams             | new GUI client connection | |
|             pnw #n X Y O L N\n             |           |           connection of a new player          | new GUI client connection | new AI client connection |
|                ppo n X Y O\n               |  ppo #n\n |               player’s position               | ppo command | AI left, right forward action or AI is ejected |
|                  plv n L\n                 |  plv #n\n |                 player’s level                | new GUI client connection or plv command | AI sucessfully incantate |
|      pin n X Y q0 q1 q2 q3 q4 q5 q6\n      |  pin #n\n |               player’s inventory              | new GUI client connection or pin command | new AI client connection or AI set, take action or AI lost food |
|                   pex n\n                  |           |                   expulsion                   | | AI eject action |
|                  pbc n M\n                 |           |                   broadcast                   | | AI broadcast action |
|             pic X Y L n n ...\n            |           | start of an incantation (by the first player) | | AI incantation action |
|                 pie X Y R\n                |           |             end of an incantation             | | AI incatation end |
|                   pfk n\n                  |           |            egg laying by the player           | | AI fork action |
|                  pdr n i\n                 |           |               resource dropping               | | AI set action |
|                  pgt n i\n                 |           |              resource collecting              | | AI take action |
|                   pdi n\n                  |           |               death of a player               | | AI client disconnection or AI lost all it's food |
|                enw e n X Y\n               |           |          an egg was laid by a player          | new GUI client connection | AI fork action end (after 42/f) |
|                   ebo e\n                  |           |          player connection for an egg         | | new AI client connection |
|                   edi e\n                  |           |                death of an egg                | | egg is ejected by an AI |
|                   sgt T\n                  |   sgt\n   |               time unit request               | new GUI client connection or sgt | sst command |
|                   sst T\n                  |  sst T\n  |             time unit modification            | | |
|                   seg N\n                  |           |                  end of game                  | | an AI team reach the victory conditions |
|                   smg M\n                  |           |            message from the server            | | server send a message |
|                    suc\n                   |           |                unknown command                | | empty or unknown command |
|                    sbp\n                   |           |               command parameter               | | invalide command (wrong parameter.s) |
|                   eht e\n                  |           |                 egg is mature                 | new GUI client connection | server create an egg or egg create by an AI become mature |

### Server commands

<br>

The server accepts command in it's standar input.

<br>

|     Command    |           Effect           |
|:--------------:|:--------------------------:|
|    /clients    | list all connected clients |
|      /quit     |       stop the server      |
|  /send_ais msg |   send messages to all AI  |
| /send_guis msg |  send messages to all GUI  |
|      /map      |  display map informations  |
|     /clear     |       clear the shell      |
|     /pause     |   pause the AI's actions   |
|     /start     |      start the server      |
