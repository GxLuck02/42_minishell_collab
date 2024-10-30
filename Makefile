# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 02:11:07 by tmontani          #+#    #+#              #
#    Updated: 2024/10/30 16:44:42 by tmontani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= minishell

# Directories
SRCDIR  		= Srcs
LIBFTDIR		= libft
INCDIR 	 		= Srcs/Includes
READLINE_PATH	= $(HOME)/.brew/opt/readline/

# Source files
BUILTINS		= cd echo env exit export_utils export pwd unset

EXEC			= exec exec_loop exec_loop_utils utils4 utils utils2 signals utils3

INIT			= env_list_utils init_minishell list_env load_env

PARSING			= cmd_list_param cmd_list_utils create_cmd_list create_token_list \
				  dollars_utils fd_utils here_doc lexer quotes_utils \
				  replace_dollar token_list_utils check_syntax
				  
PROMPT			= prompt
UTILS			= bubble_sort data_utils free_cmd free
MAIN			= main


SRCS 			= $(addsuffix .c, $(addprefix Srcs/Builtins/, $(BUILTINS))) \
				  $(addsuffix .c, $(addprefix Srcs/Init/, $(INIT))) \
				  $(addsuffix .c, $(addprefix Srcs/Exec/, $(EXEC))) \
	   			  $(addsuffix .c, $(addprefix Srcs/, $(MAIN))) \
	   			  $(addsuffix .c, $(addprefix Srcs/Parsing/, $(PARSING))) \
				  $(addsuffix .c, $(addprefix Srcs/Prompt/, $(PROMPT))) \
				  $(addsuffix .c, $(addprefix Srcs/Utils/, $(UTILS))) \
	  
OBJS    = $(SRCS:.c=.o)

# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I$(INCDIR)

# Detection automatique du chemin de readline
ifeq ($(shell test -d /opt/homebrew/opt/readline/include && echo found),found)
    READLINE_INC = -I/opt/homebrew/opt/readline/include
    READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(shell test -d /usr/include/readline/ && echo found),found)
    READLINE_INC = -I/usr/include/readline/
    READLINE_LIB = -L/usr/lib/x86_64-linux-gnu/ -lreadline
else ifeq ($(shell test -d $(READLINE_PATH)/include && echo found),found)
    READLINE_INC = -I$(READLINE_PATH)/include
    READLINE_LIB = -L$(READLINE_PATH)/lib -lreadline
else
    $(error Readline library not found)
endif

CFLAGS += $(READLINE_INC)

# Libraries
LIBFT   = $(LIBFTDIR)/libft.a
LIBS    = -L$(LIBFTDIR) -lft $(READLINE_LIB)

# Colors
YELLOW  = \033[33m
GREEN   = \033[32m
RED     = \033[31m
RESET   = \033[0m

# Progress bar variables
TOTAL_FILES = $(words $(OBJS))
COMPILED_FILES = 0
PROGRESS_BAR_LENGTH = 100

MAKEFLAGS += --silent

%.o: %.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

all: header $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)----Compiling minishell----$(RESET)\n"
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@echo ""
	@make -C ./libft 
	@echo ""
	@echo "$(YELLOW)Linking objects...$(RESET)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Minishell Compiled! ᕦ($(RED)♥$(GREEN)_$(RED)♥$(GREEN))ᕤ$(RESET)\n"

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "                                                                                                 "
	@echo "   ______     __              __       ___     ______                      __              _ "
	@echo "  / ____/  __/ /  __  _______/ /__    ( _ )   /_  __/___ ___  ____  ____  / /_____ _____  (_)"
	@echo " / / __| |/_/ /  / / / / ___/ //_/   / __ \    / / / __ \`__ \/ __ \/ __ \/ __/ __ \`/ __ \/ /  "
	@echo "/ /_/ />  </ /__/ /_/ / /__/ ,<     / /_/ /   / / / / / / / / /_/ / / / / /_/ /_/ / / / / /   "
	@echo "\____/_/|_/_____|__,_/\___/_/|_|    \____/   /_/ /_/ /_/ /_/\____/_/ /_/\__/\__,_/_/ /_/_/    "
	@echo "$(RESET)"
	
clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re: fclean all

.PHONY: all clean fclean re
