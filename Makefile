NAME = ircserv
CC = c++
CFLAGS = -Wall -Wextra -Werror -g3 -std=c++98

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

I = -I $(INC_DIR)

HEADERS_FILES =	server.hpp\
				Handler_connection.hpp\
				Handler_receive.hpp\
				Client.hpp\

HEADERS = $(addprefix $(INC_DIR), $(HEADERS_FILES))

SRC =	main.cpp\
		server.cpp\
		Handler_connection.cpp\
		Handler_receive.cpp\
		Client.cpp\

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I) -c $< -o $@

$(NAME): $(OBJ_FILES) Makefile
	$(CC) $(CFLAGS) $(OBJ_FILES) $(I) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) --no-print-directory clean
	rm -f $(NAME) a.out

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re
