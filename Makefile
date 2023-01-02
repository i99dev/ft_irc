# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isaad <isaad@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#              #
#    Updated: 2023/01/02 16:31:35 by isaad            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NAME = ircserv

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m


PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

SANITIZE = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls



SRC =	main.cpp \
		./src/Server.cpp \
		./src/Client.cpp \
		./src/Message.cpp \
		./src/Channel.cpp  \
		./src/Mask.cpp \
		./src/cmd/Join.cpp \
		./src/cmd/User.cpp \
		./src/cmd/Nick.cpp \
		./src/cmd/PrivMsg.cpp \
		./src/cmd/Cap.cpp \
		./src/cmd/Whois.cpp \
		./src/cmd/Mode.cpp \
		./src/cmd/Ping.cpp \
		./src/cmd/Pong.cpp \
		./src/cmd/Part.cpp \
		./src/cmd/Kick.cpp \
		./src/cmd/Notice.cpp \
		./src/cmd/Invite.cpp \
		./src/cmd/Topic.cpp \
		./src/cmd/List.cpp \
		./src/cmd/Quit.cpp \
		./src/cmd/Pass.cpp 


OBJ_DIR = obj
OBJ_NAME = $(SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

CXX = g++  
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(FT_NAME)

$(FT_NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/cmd
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

clean: 
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(FT_NAME)

re: fclean all

.PHONY: all clean fclean re
