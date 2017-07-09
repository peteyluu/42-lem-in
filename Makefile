# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/05 13:18:01 by pluu              #+#    #+#              #
#    Updated: 2017/07/09 14:51:19 by pluu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME           = lem-in

LIBFT_DIR      = ./libft
LIBFT_INCS_DIR = ./libft/incs
SRCS_DIR       = ./srcs
OBJS_DIR       = ./objs
INCS_DIR       = ./incs

CC             = gcc
CFLAGS         += -Wall -Wextra -Werror
LDFLAGS        += -Wall -Wextra -Werror

CFLAGS         += -I $(INCS_DIR) -I $(LIBFT_INCS_DIR)

CFLAGS         += -g
LDFLAGS        += -g

FILENAMES      = main.c dispose.c node_vec.c run.c queue.c \
		 bfs.c hash.c parser.c room.c link.c funcs.c

SRCS           = $(addprefix $(SRCS_DIR)/, $(FILENAMES))

OBJS           = $(addprefix $(OBJS_DIR)/, $(FILENAMES:.c=.o))

LIBFT_LINK     = libft/libft.a

all: $(NAME)

objs/%.o: srcs/%.c $(HDRS) | objs
	$(CC) $(CFLAGS) -o $@ -c $<

objs:
	mkdir -p objs

libft/libft.a: libft
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT_LINK) -o $@
	@echo "-> Created executable $(NAME)..."

clean:
	@make -C $(LIBFT_DIR) clean
	@echo "-> Deleted $(LIBFT_DIR) $(OBJS_DIR)..."
	@rm -rf $(OBJS_DIR)
	@echo "-> Deleted $(OBJS_DIR)..."
	@rm -rf *.dSYM

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@echo "-> Deleted $(LIBFT_DIR) libft.a"
	@rm -rf $(NAME)
	@echo "-> Deleted $(NAME)..."
	@rm -rf *.dSYM

re: fclean all

norme:
	@norminette ./srcs/
	@norminette ./incs/

.PHONY: all clean fclean re norme
