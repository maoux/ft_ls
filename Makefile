# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 15:38:42 by heynard           #+#    #+#              #
#    Updated: 2017/06/15 12:02:14 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

FLAGS = -Wall -Wextra -Werror

FLAGS_LFT = -L ./libft/ -lft

PATH_SRCS = ./srcs/

SRC_FILES = ls_main.c\
			ls_error.c\
			ls_option.c\
			ls_display.c\
			ls_arguments.c\
			ls_handle_dir.c\
			ls_handle_content.c\
			ls_handle_list.c\
			ls_handle_mode.c\
			ls_handle_path.c\
			ls_cmp.c\
			ls_cmp2.c\
			ls_handle_max.c\
			ls_display_l.c\
			ls_exit.c\
			ls_display_m.c\
			ls_tools.c\
			ls_bonus_color.c

SRCS = $(addprefix $(PATH_SRCS), $(SRC_FILES))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@$(CC) $(FLAGS) $(FLAGS_LFT) $^ -o $(NAME)
	@echo "\033[1;34mft_ls\t\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJ)
	@echo "\033[1;34mft_ls\t\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft/ fclean
	@rm -f $(NAME)
	@echo "\033[1;34mft_ls\t\t\033[1;33mCleaning ft_ls\t\t\033[0;32m[OK]\033[0m"

re: fclean all
