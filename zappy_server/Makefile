##
## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-valentin.nouri
## File description:
## Makefile
##

CC				=	gcc

EXTENSION		=	.c

INCLUDEFLAGS	=	-I./include/ -I./libs/include/ -I./libs/utils/include/ \
					-I./libs/network/include/

CXXFLAGS		=	-Wall -Wextra -Werror -Werror=format-truncation=0 -g3

LDFLAGS			=	-L./libs/ -lutils -lnetwork -lm

SRC_DIR			=	./src

BUILDDIR		=	./obj

SRC				=	./src/ais/free_ais.c \
					./src/app/ai_management/cmd/broadcast/broadcast.c \
					./src/app/ai_management/cmd/broadcast/broadcast_calcul.c \
					./src/app/ai_management/cmd/eject/eject_eggs.c \
					./src/app/ai_management/cmd/eject/eject_players.c \
					./src/app/ai_management/cmd/eject/eject.c \
					./src/app/ai_management/cmd/look/look_get.c \
					./src/app/ai_management/cmd/look/look_gettors.c \
					./src/app/ai_management/cmd/look/look_parse.c \
					./src/app/ai_management/cmd/look/look.c \
					./src/app/ai_management/cmd/connect_nbr.c \
					./src/app/ai_management/cmd/fork.c \
					./src/app/ai_management/cmd/forward.c \
					./src/app/ai_management/cmd/incantation.c \
					./src/app/ai_management/cmd/inventory.c \
					./src/app/ai_management/cmd/left.c \
					./src/app/ai_management/cmd/right.c \
					./src/app/ai_management/cmd/set.c \
					./src/app/ai_management/cmd/take.c \
					./src/app/ai_management/ai_command_begin.c \
					./src/app/ai_management/ai_command.c \
					./src/app/ai_management/ai_food.c \
					./src/app/ai_management/ai_protocol.c \
					./src/app/ai_management/connections_infos.c \
					./src/app/ai_management/disconnect_ai.c \
					./src/app/clients_management/new_ai_management.c \
					./src/app/clients_management/new_client.c \
					./src/app/clients_management/new_gui_management.c \
					./src/app/gui_management/cmd/bct.c \
					./src/app/gui_management/cmd/ebo.c \
					./src/app/gui_management/cmd/edi.c \
					./src/app/gui_management/cmd/eht.c \
					./src/app/gui_management/cmd/enw.c \
					./src/app/gui_management/cmd/mct.c \
					./src/app/gui_management/cmd/msz.c \
					./src/app/gui_management/cmd/pbc.c \
					./src/app/gui_management/cmd/pdi.c \
					./src/app/gui_management/cmd/pdr.c \
					./src/app/gui_management/cmd/pex.c \
					./src/app/gui_management/cmd/pfk.c \
					./src/app/gui_management/cmd/pgt.c \
					./src/app/gui_management/cmd/pic.c \
					./src/app/gui_management/cmd/pie.c \
					./src/app/gui_management/cmd/pin.c \
					./src/app/gui_management/cmd/plv.c \
					./src/app/gui_management/cmd/pnw.c \
					./src/app/gui_management/cmd/ppo.c \
					./src/app/gui_management/cmd/sbp.c \
					./src/app/gui_management/cmd/seg.c \
					./src/app/gui_management/cmd/sgt.c \
					./src/app/gui_management/cmd/smg.c \
					./src/app/gui_management/cmd/sst.c \
					./src/app/gui_management/cmd/suc.c \
					./src/app/gui_management/cmd/tna.c \
					./src/app/gui_management/disconnect_gui.c \
					./src/app/gui_management/gui_protocol.c \
					./src/app/input_commands/cmd/clear.c \
					./src/app/input_commands/cmd/clients.c \
					./src/app/input_commands/cmd/infos.c \
					./src/app/input_commands/cmd/pause.c \
					./src/app/input_commands/cmd/quit.c \
					./src/app/input_commands/cmd/start.c \
					./src/app/input_commands/input_protocol.c \
					./src/app/map/map_utils.c \
					./src/app/map/map_refill.c \
					./src/app/map/ressource_utils.c \
					./src/app/zappy_command.c \
					./src/app/zappy_protocol_final.c \
					./src/app/zappy_protocol.c \
					./src/arg_parsing/arg_getters.c \
					./src/arg_parsing/arg_parsing_opt.c \
					./src/arg_parsing/arg_parsing.c \
					./src/drones/drones_creation.c \
					./src/eggs/eggs_creation.c \
					./src/guis/free_guis.c \
					./src/incantations/free_incantations.c \
					./src/incantations/incantations_creation.c \
					./src/incantations/incantations_post_validation.c \
					./src/incantations/incantations_validation.c \
					./src/incantations/insert_incantations.c \
					./src/incantations/remove_incantations.c \
					./src/informations/client.c \
					./src/informations/display.c \
					./src/teams/display_teams.c \
					./src/teams/free_teams.c \
					./src/teams/teams_management.c \
					./src/time/time_management.c \
					./src/time/timer_management.c \
					./src/main.c \
					./src/should_run.c \
					./src/utils_rand.c \
					./src/zappy_server.c

OBJ				=	$(SRC:$(SRC_DIR)/%$(EXTENSION)=$(BUILDDIR)/%.o)

TEST_DIR		=	tests/

TEST_SRC		=	\

TESTS_NAME		=	unit_tests

$(BUILDDIR)/%.o: $(SRC_DIR)/%$(EXTENSION)
	@mkdir -p $(dir $@)
	$(CC) -MD $(CXXFLAGS) $(INCLUDEFLAGS) -c $< -o $@

NAME	=	zappy_server

$(NAME):	libs $(OBJ)
	@echo -e "\033[1;38;5;92mCompile \033[21m$(NAME)\033[0m"
	$(CC) -o $(NAME) $(INCLUDEFLAGS) $(CXXFLAGS) $(OBJ) $(LIBFLAGS) $(LDFLAGS)

all:	$(NAME)

clean: clean_zappy_server tests_clean

clean_zappy_server:
	@echo -e "\033[1;31mCleaning \033[21m$(NAME)\033[1;24m OBJ\033[0m"
	rm -rf $(BUILDDIR)

fclean:	fclean_zappy_server libs_fclean

fclean_zappy_server: clean tests_clean
	@echo -e "\033[1;31mcleaning \033[21m$(NAME)\033[1;24m binary\033[0m"
	rm -f $(NAME)

re:	fclean all

libs:
	@make --no-print-directory -C ./libs/

libs_clean:
	@make --no-print-directory clean -C ./libs/

libs_fclean:
	@make --no-print-directory fclean -C ./libs/

libs_re:
	@make --no-print-directory re -C ./libs/

tests_clean:
	@echo -e "\033[1;31mcleaning unit tests files\033[0m"
	rm -f *.gcda
	rm -f *gcno
	rm -f $(TESTS_NAME)

unit_tests:
	$(CC) -o $(TESTS_NAME) $(TEST_SRC) $(INCLUDEFLAGS) \
	-lcriterion --coverage $(LDFLAGS)

tests_run:	tests_clean unit_tests
	./$(TESTS_NAME)
	gcovr --exclude $(TEST_DIR) --branches

-include $(OBJ:%.o=%.d)

.PHONY:	all \
		clean clean_zappy_server \
		fclean fclean_zappy_server \
		re libs libs_clean libs_fclean libs_re \
		tests_clean unit_tests tests_run
