NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g3 -std=c++98 -MMD -MP

#__directory__
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

#__src__
SRC_FILES = \
	main.cpp\
	Server.cpp\
	HandlerConnection.cpp\
	HandlerReceive.cpp\
	HandlerRespond.cpp\
	Client.cpp\
	Command.cpp\
	commands/Pass.cpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

#__obj_&_deps__
OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP = $(OBJ:.o=.d)

#__header_&_include__
HEADER_FILES = \
	Server.hpp\
	HandlerConnection.hpp\
	HandlerReceive.hpp\
	HandlerRespond.cpp\
	Client.hpp\
	Command.hpp\
	commands/Pass.hpp

HEADER = $(addprefix $(INC_DIR), $(HEADER_FILES))
INC = -I $(INC_DIR)

#__rule__
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp  Makefile
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

-include $(DEP)
