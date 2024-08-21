/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:54:56 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 18:49:34 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"
# include "greatfull_shell.h"

# define INPUT		1		//"<"
# define HEREDOC	2		//"<<"
# define TRUNC		3		//">"
# define APPEND		4		//">>"
# define PIPE		5		//"|"
# define CMD		6
# define ARG		7

# define EXT_MALLOC 3

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_token
{
	char			*str;
	int				token_type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef  struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_data
{
	t_list	*env;
	t_token	*token;
	t_cmd	*cmd;
	bool	sq;
	int		exit_code;
}				t_data;

//data
int			check_pipe(t_data *data);

//prompt
char		*init_prompt(void);
int			is_valide_input(char *input);
char		*get_prompt(void);

//lexer
int			replace_dollar(char **cmd_line, t_data *data);
void		quote_choice(bool *sq, bool *dq, char c);
bool		is_pars(t_data *data, char *cmd_line);
int			open_quote(char *str);
int			ft_search(char *str, char c);
char		*get_value(t_list *env, char *key);
int			exist_in_env(t_data *data, int *i, char *str);
char		*get_dollar_word(char *line, int size);
int			open_pipe(t_data *data);

//tokeniser
bool		creat_token_list(t_token **begin, char *cmd_line);
int			isspecial(char *str);
int			len_token(char *str, int *quotes);
int			append_token(t_token **begin, char *str, int type);
void		free_token(t_token **list);

//cmd_list
int			creat_cmd_list(t_data *data);
int			init_new_cmd(t_cmd **cmd, int infile, int outfile, char **cmd_param);
int			append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param);
int			get_infile(t_data *data, t_token *token, t_cmd *cmd);
int			get_outfile(t_data *data, t_token *token, t_cmd *cmd);
char		**get_params(t_data *data, t_token *token);
int			here_doc(t_data *data, char *end_file);

//free
void		free_cmd(t_cmd **list);
void		free_all(t_data *data, char *err, int ext);

//error
bool		print_error(char *err);

#endif
