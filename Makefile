# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#              #
#    Updated: 2022/11/28 22:47:24 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NAME = ircserv

SRC =	main.cpp \
		./src/Server.cpp \
		./src/Client.cpp \
		./src/Message.cpp \
		./src/cmd/Join.cpp \
		./src/cmd/User.cpp \
		./src/cmd/Cap.cpp \
		./src/cmd/PrivMsg.cpp \
		./src/Channel.cpp


OBJ_DIR = obj
OBJ_NAME = $(SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

CC = g++ -g  -std=c++98 
CFLAGS = -Wall -Wextra -Werror

all: $(FT_NAME)

$(FT_NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/cmd
	@$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(FT_NAME)

re: fclean all

.PHONY: all clean fclean re
