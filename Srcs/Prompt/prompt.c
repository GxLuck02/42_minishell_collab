/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:53:28 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 19:00:16 by ttreichl         ###   ########.fr       */
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
	char	*color_prompt;

	pwd = getenv("PWD");
	home = getenv("HOME");
	if (home == NULL || pwd == NULL)
		return (NULL);
	if (ft_strstr(pwd, home) == NULL)
		prompt = ft_strjoin(pwd, " → ");
	else
	{
		prompt = ft_strjoin("~", pwd + ft_strlen(home));
		prompt = ft_strjoin(prompt, " → ");
	}
	prompt = ft_strjoin("xX-Minishell-Xx ", prompt);
	if (!prompt)
	{
		free(prompt);
		return (NULL);
	}
	color_prompt = ft_strjoin("\001\e[00;35m\002", prompt);
	return (color_prompt);
}

char	*init_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = get_path_prompt();
	rl_on_new_line();
	input = readline(prompt);
	free(prompt);
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
			continue ;
		add_history(cmd_line);
		return (cmd_line);
	}
	return (NULL);
}
