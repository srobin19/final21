# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 17:19:46 by rlucas-d          #+#    #+#              #
#    Updated: 2019/11/22 12:03:09 by bjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs
OBJ_DIR = ./obj
INC_DIR = ./inc

NAME = 21sh

ROOT_FILES = main.c

TERMCAPS_DIR = termcaps
TERMCAPS_FILES = init.c termcaps_controler.c move.c prompt.c key.c history.c \
	edition.c home_end.c maj_key.c modify_command.c print_edition_mode.c \
	utils.c print_command.c
QUENTIN_DIR = quentin
QUENTIN_FILES = cd.c display.c execute_main.c input_main.c input_tools.c \
	redirect.c setenv.c sh21.c testing.c tokens_gather.c tokens_list.c \
	tokens_main.c tokens_split.c tokens_tools.c util_env.c util_pwd.c \
	util_array.c redirect_list.c unsetenv.c echo.c 


SRC_FILES = $(ROOT_FILES)
SRC_FILES += $(addprefix $(TERMCAPS_DIR)/, $(TERMCAPS_FILES))
SRC_FILES += $(addprefix $(QUENTIN_DIR)/, $(QUENTIN_FILES))

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ  = $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(SRC_FILES)))

CC = gcc
CFLAGS = -Wall -Wextra -g -O0 

LIB = -L libft/ -lft
LIBFT_INC = libft/includes

KNRM = "\x1B[0m"
KGRN = "\x1B[1;32m"

.PHONY: all clean fclean re

all:
	@mkdir -p $(OBJ_DIR)
	@make -C libft/
	@make $(NAME)

$(NAME): $(OBJ)
	@echo "Creation de l'executable..."
	@$(CC) $(CLFAGS) $(OBJ) $(LIB) -ltermcap -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilation du fichier "$(KGRN)$(notdir $(subst .c,,$<))$(KNRM)
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -I $(LIBFT_INC) -I $(INC_DIR) -o $@ -c $<

clean:
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)

fclean:
	@make fclean -C libft/
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

re: fclean all
