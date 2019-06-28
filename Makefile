# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/19 20:53:55 by david             #+#    #+#              #
#    Updated: 2019/06/28 07:52:55 by srobert-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework Appkit  -framework OpenCL 
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD) -I$(MINILIBX_HEAD)

LIBFT_DIR = ./libft/
LIBFT_HEAD = $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a

MINILIBX_DIR = ./minilibx_macos/
MINILIBX_HEAD = $(MINILIBX_DIR)
MINILIBX = $(MINILIBX_DIR)libmlx.a

HEADERS_LIST = fract.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRCS_DIR = ./srcs/
SRCS_LIST = main.c util.c init.c weird_shit4cl.c control.c control2.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)obj files have been created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) has been created$(RESET)"
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GREEN)$(OBJ_DIR) has been created$(RESET)"

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@$(MAKE) -sC $(MINILIBX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) has been deleted$(RESET)"
	@echo "$(NAME): $(RED)object files have been deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(NAME): $(RED)$(MINILIBX) has been deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) has been deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) has been deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all