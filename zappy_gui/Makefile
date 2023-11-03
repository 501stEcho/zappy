##
## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-valentin.nouri
## File description:
## Makefile
##

CC				=	g++

SFMLFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RAYFLAGS		=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CXXFLAGS		=	-iquote Include -Wall -Wextra -Werror -std=c++20

LDFLAGS			=	\

LDLIBS			=	\

SRC_DIR			=	./Src

BUILDDIR		=	./Obj

SRC				=		$(SRC_DIR)/Main.cpp \
						$(SRC_DIR)/AnimationManager/AnimationManager.cpp \
						$(SRC_DIR)/GameState/Types/Drone.cpp \
						$(SRC_DIR)/GameState/Types/Tile.cpp \
						$(SRC_DIR)/GameState/GameManager.cpp \
						$(SRC_DIR)/GameState/GameState.cpp \
						$(SRC_DIR)/Interpreter/HandlersImpl.cpp \
						$(SRC_DIR)/Network/Client/Client.cpp \
						$(SRC_DIR)/Parsing/Parser.cpp \
						$(SRC_DIR)/Core/Core3D.cpp \
						$(SRC_DIR)/Core/CoreDebug.cpp \
						$(SRC_DIR)/Core/MapHandler.cpp \
						$(SRC_DIR)/Raylib/CollisionPoint.cpp \
						$(SRC_DIR)/Raylib/Entity.cpp \
						$(SRC_DIR)/Raylib/ParticlesManager.cpp \
						$(SRC_DIR)/Raylib/Renderer.cpp


OBJ				= 	$(patsubst $(SRC_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))

$(BUILDDIR)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -MD $(CXXFLAGS) -c $< $(LDLIBS) $(LDFLAGS)

NAME	=	zappy_gui

$(NAME):	$(OBJ)
	@echo -e "\033[1;38;5;92mCompile \033[21m$(NAME)\033[0m"
	$(CC) -o $(NAME) $(CXXFLAGS) $(OBJ) $(LDLIBS) $(LDFLAGS) $(SFMLFLAGS) $(RAYFLAGS)

all:	$(NAME)

clean: clean_zappy_gui

clean_zappy_gui:
	@echo -e "\033[1;31mCleaning \033[21m$(NAME) OBJ\033[0m"
	rm -rf $(BUILDDIR)

fclean:	fclean_zappy_gui

fclean_zappy_gui: clean
	rm -f $(NAME)

re:	fclean all

-include $(OBJ:%.o=%.d)

.PHONY:	all \
		clean clean_zappy_gui \
		fclean fclean_zappy_gui \
		re \

# --------------------------------------------------------------

TESTS_CXXFLAGS		=	-I./Include -Wall -Wextra -Werror -g3 -std=c++17

TESTS_LDFLAGS		=	-lcriterion --coverage

TESTS_LDLIBS		=	\

TESTS_SRC_DIR			=	./Tests

TESTS_BUILDDIR		=	./TestsObj

TESTS_SRC		=	$(wildcard $(TESTS_SRC_DIR)/*.cpp) \
					$(wildcard $(TESTS_SRC_DIR)/**/*.cpp) \
					$(wildcard $(TESTS_SRC_DIR)/**/**/*.cpp)

TESTS_OBJ		=	$(SRC:$(SRC_DIR)/%.cpp=$(TESTS_BUILDDIR)/%.o) \
					$(TESTS_SRC:$(TESTS_SRC_DIR)/%.cpp=$(TESTS_BUILDDIR)/%.o)

$(TESTS_BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(TESTS_CXXFLAGS) -c $< $(TESTS_LDLIBS) $(TESTS_LDFLAGS)

$(TESTS_BUILDDIR)/%.o:	$(TESTS_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(TESTS_CXXFLAGS) -c $< $(TESTS_LDLIBS) $(TESTS_LDFLAGS)

TESTS_NAME	=	unit_tests

$(TESTS_NAME):	$(TESTS_OBJ)
	@echo -e "\033[1;38;5;92mCompile \033[21m$(NAME)\033[1;24m unit tests\033[0m"
	$(CC) -o $(TESTS_NAME) $(TESTS_CXXFLAGS) \
	$(TESTS_OBJ) $(TESTS_LDLIBS) $(TESTS_LDFLAGS)

all_tests:	$(TESTS_NAME)

tests_clean:
	@echo -e "\033[1;31mCleaning \033[21m$(NAME)\033[1;24m unit tests Obj\033[0m"
	rm -rf $(TESTS_BUILDDIR)

tests_fclean:	tests_clean
	@echo -e "\033[1;31mCleaning \033[21m$(NAME)\033[1;24m all unit tests\033[0m"
	rm -f $(TESTS_NAME)

tests_run:	all_tests
	./$(TESTS_NAME)
	gcovr --exclude $(TESTS_SRC_DIR) --branches

.PHONY:	all_tests tests_clean tests_fclean tests_run
