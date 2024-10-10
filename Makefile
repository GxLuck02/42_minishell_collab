# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 02:11:07 by tmontani          #+#    #+#              #
#    Updated: 2024/10/10 16:36:09 by tmontani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

# Directories
SRCDIR  = Srcs
LIBFTDIR= libft
INCDIR  = Srcs/Includes

# Source files
SRCS    = $(SRCDIR)/main.c $(SRCDIR)/Prompt/prompt.c $(SRCDIR)/Parsing/dollars_utils.c $(SRCDIR)/Parsing/lexer.c $(SRCDIR)/Parsing/quotes_utils.c \
				$(SRCDIR)/Parsing/replace_dollar.c $(SRCDIR)/Parsing/token_list_utils.c $(SRCDIR)/Parsing/create_token_list.c \
				$(SRCDIR)/Parsing/cmd_list_param.c $(SRCDIR)/Parsing/cmd_list_utils.c $(SRCDIR)/Parsing/create_cmd_list.c \
				$(SRCDIR)/Parsing/fd_utils.c $(SRCDIR)/Parsing/here_doc.c $(SRCDIR)/Utils/free_cmd.c $(SRCDIR)/Utils/data_utils.c \
				$(SRCDIR)/Utils/free.c $(SRCDIR)/Init/init_minishell.c $(SRCDIR)/Init/load_env.c $(SRCDIR)/Init/list_env.c $(SRCDIR)/Init/env_list_utils.c \
				$(SRCDIR)/Utils/bubble_sort.c \
				$(SRCDIR)/Exec/exec.c $(SRCDIR)/Exec/utils.c $(SRCDIR)/Exec/pipe_utils.c $(SRCDIR)/Exec/utils2.c $(SRCDIR)/Exec/builtins/pwd.c \
				$(SRCDIR)/Exec/builtins/echo.c $(SRCDIR)/Exec/builtins/exit.c $(SRCDIR)/Exec/builtins/env.c $(SRCDIR)/Exec/builtins/export.c \
				$(SRCDIR)/Exec/builtins/export_utils.c $(SRCDIR)/Exec/builtins/cd.c \
				$(SRCDIR)/Exec/ft_free.c

OBJS    = $(SRCS:.c=.o)

# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I$(INCDIR)

# Detection automatique du chemin de readline
ifeq ($(shell test -d /opt/homebrew/opt/readline/include && echo found),found)
    READLINE_INC = -I/opt/homebrew/opt/readline/include
    READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(shell test -d /Users/tmontani/.brew/opt/readline/include && echo found),found)
    READLINE_INC = -I/Users/tmontani/.brew/opt/readline/include
    READLINE_LIB = -L/Users/tmontani/.brew/opt/readline/lib -lreadline
else ifeq ($(shell test -d /Users/ttreichl/.brew/opt/readline/include && echo found),found)
    READLINE_INC = -I/Users/ttreichl/.brew/opt/readline/include
    READLINE_LIB = -L/Users/ttreichl/.brew/opt/readline/lib -lreadline
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

%.o: %.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)----Compiling minishell----$(RESET)"
	@make re -C ./libft
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Minishell Compiled! ᕦ($(RED)♥$(GREEN)_$(RED)♥$(GREEN))ᕤ$(RESET)\n"

clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re: fclean all

.PHONY: all clean fclean re
