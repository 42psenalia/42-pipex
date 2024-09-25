# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 18:15:33 by psenalia          #+#    #+#              #
#    Updated: 2024/09/25 17:59:22 by psenalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------
#			Directories
#------------------------------------------------------------------------------

SRC		= pipe_xcavate.c pipe_xpress.c pipe_xpunge.c main.c

OBJ		= $(SRC:.c=.o)

#------------------------------------------------------------------------------
#			Variables
#------------------------------------------------------------------------------

NAME		= pipex
LIBFT		= ./libft
HEADERS		= -I $(LIBFT)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -rf

#------------------------------------------------------------------------------
#			Targets
#------------------------------------------------------------------------------

all: $(NAME) 

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) -L. $(LIBFT)/libft.a

%.o: %.c $(HEADER_FILE)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)  && printf " Compiling: $(notdir $<)"

clean:
	@rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re
