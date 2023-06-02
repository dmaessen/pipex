# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:56:57 by dmaessen          #+#    #+#              #
#    Updated: 2023/03/13 16:17:02 by dmaessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c paths.c errors_free.c cmd.c \

SRC_B = pipex_bonus.c stdin_bonus.c heredoc_bonus.c getnextline_bonus.c getnextline_utils_bonus.c paths_bonus.c errors_free_bonus.c cmd_bonus.c child_bonus.c \

LIBFT = libft/libft.a

CC = cc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

ifdef BONUS
SRC_FILES   = $(SRC_B)
else
SRC_FILES   = $(SRC)
endif

all: $(NAME)

$(NAME): $(SRC_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft/

bonus:
	@$(MAKE) BONUS=1

clean:
	make clean -C libft/
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus