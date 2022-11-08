# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#              #
#    Updated: 2022/11/08 12:25:45 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NAME = ft_irc_FT

SRC =	main.cpp \
		./src/Server.cpp


OBJ_DIR = obj
OBJ_NAME = $(SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

CC = clang++ -g 
CFLAGS = -Wall -Wextra -Werror -std=c++98 

all: $(FT_NAME)

$(FT_NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(FT_NAME)

re: fclean all

.PHONY: all clean fclean re
