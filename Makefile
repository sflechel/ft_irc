NAME = webserv
CC = c++
CFLAGS = -Wall -Wextra -Werror -g3 -std=c++98

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

I = -I $(INC_DIR)

HEADERS_FILES =	server.hpp
HEADERS = $(addprefix $(INC_DIR), $(HEADERS_FILES))

SRC =	main.cpp\
		server.cpp\

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
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
