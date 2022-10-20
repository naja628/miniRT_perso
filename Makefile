# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 23:28:49 by xle-boul          #+#    #+#              #
#    Updated: 2022/10/20 17:29:28 by xle-boul         ###   ########.fr        #
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

NAME := miniRT

CC := gcc
CFLAGS := -Werror -Wall -Wextra
#EXTRA_FLAGS := -Lmlx_linux -lmlx_Linux -L/usr/local/lib -Imlx_linux -lXext -lX11 -lm
EXTRA_FLAGS := -lmlx -framework OpenGL -framework AppKit


INCLUDES := -I includes

SRC_DIR := sources
OBJ_DIR := objs

#
# INSERT HERE THE NAMES OF THE FOLDERS INTO SOURCES THAT YOU WANT TO COMPILE
#
SUB_DIRS := parsing gnl ray_tracing

SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

RM := rm -rf
MKDIR := mkdir -p

LIB_DIR := sources/mlx
LIB_OBJ := sources/mlx/*.o
LIB := libmlx.a

VPATH := $(SOURCEDIRS)

all: $(NAME)

$(NAME): $(LIB) $(OBJ_FILES)
	@printf "$(YELLOW)Linking miniRT...\n\n$(END)"
	$(CC) $(INCLUDES) $(EXTRA_FLAGS) $(OBJ_FILES) $(LIB) -o $@ -lm
	@printf "\n$(GREEN)miniRT compiled.\n$(END)"

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(INCLUDES) -Imlx -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(LIB):
	@printf "$(YELLOW)Compiling minilibx_linux.a...\n$(END)"
	@make --no-print-directory -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIB) .
	@printf "$(GREEN)$(LIB) compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB_OBJ)
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, miniLibX and miniRT executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(LIB)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

norm:
	@norminette includes sources/gnl sources/parsing sources/ray_tracing

.PHONY: clean fclean all re
