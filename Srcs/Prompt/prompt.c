/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:53:28 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/25 16:07:02 by tmontani         ###   ########.fr       */
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

char	*get_path_prompt(t_data *data)
{
	t_env	*pwd;
	t_env	*home;
	char	*prompt;
	char	*tmp;

	pwd = ft_getenv("PWD", data->env);
	home = ft_getenv("HOME", data->env);
	if (home == NULL || pwd == NULL)
		return (ft_strdup("xX-Minishell-Xx > "));
	if (ft_strstr(pwd->value, home->value) == NULL)
		prompt = ft_strjoin(pwd->value, " → ");
	else
	{
		tmp = ft_strjoin("~", pwd->value + ft_strlen(home->value));
		prompt = ft_strjoin(tmp, " → ");
		free(tmp);
	}
	tmp = ft_strjoin("xX-Minishell-Xx ", prompt);
	free(prompt);
	prompt = ft_strjoin("\001\e[1;32m\002", tmp);
	free(tmp);
	tmp = ft_strjoin(prompt, "\001\e[1;36m\002");
	free(prompt);
	return (tmp);
}

char	*init_prompt(t_data *data)
{
	char	*input;
	char	*prompt;

	prompt = get_path_prompt(data);
	rl_on_new_line();
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (NULL);
	rl_replace_line("", 0);
	return (input);
}

char	*get_prompt(t_data *data)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = init_prompt(data);
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
