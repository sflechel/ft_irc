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
	server/Server.cpp\
	server/getters.cpp\
	server/main_loop.cpp\
	server/setters.cpp\
	server/setup.cpp\
	HandlerConnection.cpp\
	HandlerReceive.cpp\
	HandlerRespond.cpp\
	Client.cpp\
	Command.cpp\
	ResponseBuilder.cpp\
	Channel.cpp\
	commands/PrivMsg.cpp\
	commands/Pass.cpp\
	commands/UnknownCommand.cpp\
	commands/Nick.cpp\
	commands/User.cpp\
	commands/Quit.cpp\
	commands/Join.cpp\
	commands/Mode.cpp\
	commands/Topic.cpp\
	commands/Invite.cpp\
	commands/Kick.cpp\
	commands/Part.cpp\

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
	ResponseBuilder.hpp\
	Channel.hpp\
	commands/PrivMsg.hpp\
	commands/Pass.hpp\
	commands/UnknownCommand.hpp\
	commands/Nick.hpp\
	commands/User.hpp\
	commands/Quit.hpp\
	commands/Join.hpp\
	commands/Mode.hpp\
	commands/Topic.hpp\
	commands/Invite.hpp\
	commands/Kick.hpp\
	commands/Part.hpp\

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

bonus:
	$(MAKE) -C bot/

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus

-include $(DEP)
