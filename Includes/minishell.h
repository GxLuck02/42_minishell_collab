/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:54:56 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/14 14:34:56 by ttreichl         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

# define INPUT		1		//"<"
# define HEREDOC	2		//"<<"
# define TRUNC		3		//">"
# define APPEND		4		//">>"
# define PIPE		5		//"|"
# define CMD		6
# define ARG		7

# define EXT_MALLOC 3

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			equal;
	struct s_env	*next;
}				t_env;

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
	bool			quoted;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd
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
	t_env	*env;
	char	**env_tab;
	char	**absolute_path;
	t_token	*token;
	t_cmd	*cmd;
	bool	sq;
	int		exit_code;
}				t_data;

//data
int			init_minishell(t_data *data, char **envp);
int			check_pipe(t_data *data);
t_list		*create_node(char *str);
void		append_node(t_list **head, char *str);

//prompt
char		*init_prompt(t_data *data);
int			is_valide_input(char *input);
char		*get_prompt(t_data *data);

//env
int			load_env(t_data *data, char **envp);
char		**ft_envsplit(char *env_str);
int			create_node_env(t_env **head, char *str);
void		free_var(char **var);
void		add_node_env(t_env **head, t_env *node);
void		incr_shell_level(t_data *data);

//bultin
int			ft_env(t_env *const env, char **cmd_param);
int			ft_export(t_env **env, char **args);
void		change_value(t_env **env, t_env *new_node);
int			is_builtin(t_data *data);
int			ft_pwd(void);
int			ft_echo(t_data *data);
int			ft_exit(t_data *data);
int			ft_cd(t_data *data);
int			ft_unset(t_env **env, char **args);
char		**creat_table(t_env *env);
bool		var_already_exist(t_env *env, char *key);
int			is_valid_var(char *var);
void		invalid_var(char *var);

//lexer
int			replace_dollar(char **cmd_line, t_data *data);
void		quote_choice(bool *sq, bool *dq, char c);
bool		is_pars(t_data *data, char *cmd_line);
int			open_quote(char *str);
int			ft_search(char *str, char c);
char		*get_value(t_env *env, char *key);
int			exist_in_env(t_data *data, int *i, char *str);
char		*get_dollar_word(char *line, int size);
int			open_pipe(t_data *data);

//tokeniser
bool		creat_token_list(t_token **begin, char *cmd_line);
int			ft_isspecial(char *str);
int			len_token(char *str, int *quotes);
int			append_token(t_token **begin, char *str, int type, bool quoted);
void		free_token(t_token **list);

//cmd_list
int			creat_cmd_list(t_data *data);
int			init_new_cmd(t_cmd **cmd, int infile, \
							int outfile, char **cmd_param);
int			append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param);
int			get_infile(t_data *data, t_token *token, t_cmd *cmd);
int			get_outfile(t_data *data, t_token *token, t_cmd *cmd);
char		**get_params(t_data *data, t_token *token);
int			here_doc(t_data *data, char *end_file, bool quoted);
int			len_list(t_env *list);

//free
void		free_cmd(t_cmd **list);
void		free_all(t_data *data, char *err, int ext);
void		free_table(char **table);

//utils
int			env_lenthg(t_env *env);
void		bubble_sort(char **tab, int len_env);
void		equal_check(t_env **env, char *str);
void		key_var_to_node(char **var, t_env **node);

//error
bool		print_error(char *err);

//execution
void		exec(t_data *data);
int 		ft_lstsize_env(t_env *lst);
char		**ft_split_path(char const *path, char c);
void		ft_print_array(char **array);
char		**creat_env_copy(t_env *env);
void		execute_absolute_path(char *path, char **cmd_param, char **absolute_path);
void		handle_pipe(t_data *data);
void   		make_cmd(t_data *data);
int			ft_lstsize_circular(t_cmd	*cmd);
void		handle_child(int *pipe_fd, t_data *data);
void		handle_parent(int *pipe_fd, int status, pid_t pid);
t_env 		*ft_getenv(char *var, t_env *env);
int			execute_builtin(t_data *data);

#endif
