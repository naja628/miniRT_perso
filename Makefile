# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 23:28:49 by xle-boul          #+#    #+#              #
#    Updated: 2022/10/25 22:33:27 by xle-boul         ###   ########.fr        #
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
	LIB_DIR := sources/mlx_linux
	EXTRA_FLAGS := -L$(LIB_DIR) -lmlx -I$(LIB_DIR) -lXext -lX11 -lm
else
	D_OS := -D MAC 
	LIB_DIR	:= sources/mlx
	EXTRA_FLAGS	:= -L$(LIB_DIR) -lmlx -I$(LIB_DIR) -framework OpenGL -framework AppKit
endif

INCLUDES := -I includes -I$(LIB_DIR)
LIB := $(LIB_DIR)/libmlx.a

SRC_DIR := sources
OBJ_DIR := objs

#
# INSERT HERE THE NAMES OF THE FOLDERS INTO SOURCES THAT YOU WANT TO COMPILE
#
SUB_DIRS := parsing gnl ray_tracing main

SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

RM := rm -rf
MKDIR := mkdir -p


VPATH := $(SOURCEDIRS)

all: $(NAME)

$(NAME): $(LIB) $(OBJ_FILES)
	@printf "$(YELLOW)Linking miniRT...\n\n$(END)"
	$(CC) $(OBJ_FILES) -o $@ $(INCLUDES) $(EXTRA_FLAGS) -lm
	@printf "\n$(GREEN)miniRT compiled.\n$(END)"
#ifeq ($(OS),Linux)
#	@printf "$(YELLOW)Linking miniRT...\n\n$(END)"
#	$(CC) $(LIB_OBJ) $(INCLUDES) $(OBJ_FILES) $(LIB) -o $@ -lm $(EXTRA_FLAGS) 
#	@printf "\n$(GREEN)miniRT compiled.\n$(END)"
#else
#	@printf "$(YELLOW)Linking miniRT...\n\n$(END)"
#	$(CC) $(INCLUDES) $(EXTRA_FLAGS) $(OBJ_FILES) $(LIB) -o $@ -lm
#	@printf "\n$(GREEN)miniRT compiled.\n$(END)"
#endif


$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(INCLUDES) $(D_OS) -Imlx -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(LIB):
	@printf "$(YELLOW)Compiling $(LIB)...\n$(END)"
	cd $(LIB_DIR) && make
	@printf "$(GREEN)$(LIB) compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	cd $(LIB_DIR) && make clean
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, miniLibX and miniRT executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(LIB)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

norm:
	@norminette includes sources/gnl sources/parsing sources/ray_tracing sources/main

.PHONY: clean fclean all re
