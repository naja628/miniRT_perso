# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 23:28:49 by xle-boul          #+#    #+#              #
#    Updated: 2022/10/29 13:08:32 by xle-boul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
UNDERLINE	= \e[4m
RESET		= \033[0m
END			= \e[0m

OS = $(shell uname -s)

NAME := miniRT

CC := gcc
CFLAGS := -Werror -Wall -Wextra

ifeq ($(OS),Linux)
	D_OS := -D LINUX
	LIB_DIR := mlx/mlx_linux
	EXTRA_FLAGS := -L$(LIB_DIR) -lmlx -lXext -lX11 -lm
else
	D_OS := -D MAC 
	LIB_DIR	:= mlx/mlx
	EXTRA_FLAGS := -L$(LIB_DIR) -lmlx -lXext -lX11 -lm
endif

MLX := $(LIB_DIR)/libmlx.a
INCLUDES := -I includes/ -I$(LIB_DIR)

SRC_DIR := sources

OBJ_DIR := objs


#
# INSERT HERE THE NAMES OF THE FOLDERS INTO SOURCES THAT YOU WANT TO COMPILE
#

SUB_DIRS := parsing gnl ray_tracing main shell bonus

SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))


RM := rm -rf
MKDIR := mkdir -p

VPATH := $(SOURCEDIRS)

all: $(NAME)

$(MLX): 
	(cd $(LIB_DIR) && make); exit 0 # silence test error

$(NAME): $(OBJ_FILES) $(MLX)
	@printf "$(YELLOW)Linking $@...\n\n$(END)"
	$(CC) $(CFALGS) $(OBJ_FILES) -o $@ $(INCLUDES) $(EXTRA_FLAGS) -lm
	@printf "\n$(GREEN)$@ compiled.\n$(END)"

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(CFLAGS) $(INCLUDES) $(D_OS) -Imlx -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	cd $(LIB_DIR) && make clean
	$(RM) $(OBJ_DIR)
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects and miniRT executable...\n$(END)"
	$(RM) $(NAME)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

norm:
	@norminette includes sources/gnl sources/parsing sources/ray_tracing sources/main sources/shell

.PHONY: clean fclean all re bonus mlx
