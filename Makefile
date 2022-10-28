# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 23:28:49 by xle-boul          #+#    #+#              #
#    Updated: 2022/10/28 23:30:45 by xle-boul         ###   ########.fr        #
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
BONUS := miniRT_bonus

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
OBJ_DIR_BONUS := objs_bonus

EXCL_BONUS := $(wildcard $(SRC_DIR)/bonus/*.c)
EXCL_BASE := $(SRC_DIR)/parsing/read_data_hub.c $(SRC_DIR)/parsing/read_shapes.c $(SRC_DIR)/parsing/parsing.c $(SRC_DIR)/parsing/error_handler.c

#
# INSERT HERE THE NAMES OF THE FOLDERS INTO SOURCES THAT YOU WANT TO COMPILE
#
SUB_DIRS := parsing gnl ray_tracing main shell bonus

SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
SRC_FILES := $(filter-out $(EXCL_BONUS), $(SRC_FILES))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

SRC_FILES_BONUS := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
SRC_FILES_BONUS := $(filter-out $(EXCL_BASE), $(SRC_FILES_BONUS))
OBJ_FILES_BONUS := $(addprefix $(OBJ_DIR_BONUS)/,$(notdir $(SRC_FILES_BONUS:.c=.o)))

RM := rm -rf
MKDIR := mkdir -p


VPATH := $(SOURCEDIRS)

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(LIB) $(OBJ_FILES)
	@printf "$(YELLOW)Linking miniRT...\n\n$(END)"
	$(CC) $(CFALGS) $(OBJ_FILES) -o $@ $(INCLUDES) $(EXTRA_FLAGS) -lm
	@printf "\n$(GREEN)miniRT compiled.\n$(END)"

$(BONUS): $(LIB) $(OBJ_FILES_BONUS)
	@printf "$(YELLOW)Linking $@...\n\n$(END)"
	$(CC) $(CFALGS) $(OBJ_FILES_BONUS) -o $@ $(INCLUDES) $(EXTRA_FLAGS) -lm
	@printf "\n$(GREEN)$@ compiled.\n$(END)"

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(CFLAGS) $(INCLUDES) $(D_OS) -Imlx -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(OBJ_DIR_BONUS)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR_BONUS)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(CFLAGS) $(INCLUDES) $(D_OS) -Imlx -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(LIB):
	@printf "$(YELLOW)Compiling $(LIB)...\n$(END)"
	cd $(LIB_DIR) && make
	@printf "$(GREEN)$(LIB) compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_DIR_BONUS)
	cd $(LIB_DIR) && make clean
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, miniLibX and miniRT executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(BONUS)
	$(RM) $(LIB)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

norm:
	@norminette includes sources/gnl sources/parsing sources/ray_tracing sources/main sources/shell

.PHONY: clean fclean all re
