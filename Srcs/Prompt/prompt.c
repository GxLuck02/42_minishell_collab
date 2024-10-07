/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:53:28 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/07 16:43:37 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	is_valide_input(char *input)
{
	if (!input)
		return (0);
	if (*input == '\0')
		return (0);
	while (*input)
	{
		if (ft_isspace(*input) == 0)
			return (1);
		input++;
	}
	return (0);
}

char	*get_path_prompt(void)
{
	char	*pwd;
	char	*home;
	char	*prompt;
	char	*tmp;

	pwd = getenv("PWD");
	home = getenv("HOME");
	if (home == NULL || pwd == NULL)
		return ("minishell > ");
	if (ft_strstr(pwd, home) == NULL)
		prompt = ft_strjoin(pwd, " → ");
	else
	{
		tmp = ft_strjoin("~", pwd + ft_strlen(home));
		prompt = ft_strjoin(tmp, " → ");
		free(tmp);
	}
	tmp = prompt;
	prompt = ft_strjoin("xX-Minishell-Xx ", prompt);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin("\001\e[00;35m\002", prompt);
	free(tmp);
	return (prompt);
}

char	*init_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = get_path_prompt();
	rl_on_new_line();
	input = readline(prompt);
	if (!input)
		return (NULL);
	return (input);
}

char	*get_prompt(void)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = init_prompt();
		if (cmd_line == NULL)
			break ;
		if (is_valide_input(cmd_line) == 0)
		{
			free(cmd_line);
			continue ;
		}
		add_history(cmd_line);
		return (cmd_line);
	}
	return (NULL);
}
