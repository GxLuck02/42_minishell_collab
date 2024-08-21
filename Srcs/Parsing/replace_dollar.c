/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:04:29 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/13 16:00:13 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// in_env - Replaces a dollar sign ($) variable in the command line 
// with its corresponding value from the environment.
int	in_env(t_data *data, char *cmd_line, char **new_str, int size_dollar)
{
	char	*tmp;
	char	*value;
	char	*key;

	key = get_dollar_word(cmd_line, size_dollar);
	value = get_value(data->env, key);
	if (key)
		free(key);
	tmp = ft_strjoin(*new_str, value);
	if (value)
		free(value);
	free(*new_str);
	if (!tmp)
		return (0);
	*new_str = tmp;
	return (1);
}

//replace $? by the last exit status (data->exit_code)
int	dollar_point_interogation(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

// replace_dollar_var -
// Replaces a variable preceded by a dollar sign ($) in command line.
//
// It uses the `exist_in_env` function to determine if 
// the variable exists in the environment variables.
int	replace_dollar_var(char *cmd_line, int *i, t_data *data, char **str)
{
	int		nbr_output;
	int		n;

	n = *i;
	nbr_output = exist_in_env(data, i, cmd_line);
	if (nbr_output == 1)
		return (in_env(data, &cmd_line[n], str, *i - n));
	else if (nbr_output == 2 || nbr_output == 3)
	{
		(*i) += 2;
		if (nbr_output == 2)
			return (dollar_point_interogation(data, str));
		if (nbr_output == 3)
			return (1);
	}
	else
	{
		++(*i);
		while (cmd_line[*i] && (ft_isalnum(cmd_line[*i]) \
			|| cmd_line[*i] == '_'))
			++(*i);
		return (1);
	}
	return (0);
}

//add_char - Adds a character from the command line to a new string.
int	add_char(char *cmd_line, char **new_str, int *index, t_data *data)
{
	char	char_to_str[2];
	char	*tmp;
	int		i;

	i = 0;
	if (cmd_line[i] == '$' && !data->sq && exist_in_env(data, &i, cmd_line))
		return (1);
	char_to_str[0] = *cmd_line;
	char_to_str[1] = '\0';
	(*index)++;
	tmp = ft_strjoin(*new_str, char_to_str);
	free(*new_str);
	if (!tmp)
		return (0);
	*new_str = tmp;
	return (1);
}

// replace_dollar - Replaces variables preceded by a dollar sign ($) 
// in the command line with their values.
//
// This function scans through the command line, identifies variables 
// preceded by a dollar sign, and replaces them with corresponding values. 
// It handles quoted strings, ensures proper memory management for new cmd_line.
int	replace_dollar(char **cmd_line, t_data *data)
{
	bool		dq;
	int			i;
	char		*new_str;

	dq = false;
	data->sq = false;
	i = 0;
	new_str = ft_strdup("");
	while ((*cmd_line)[i] != '\0')
	{
		quote_choice(&data->sq, &dq, (*cmd_line)[i]);
		if ((*cmd_line)[i] && !data->sq && (*cmd_line)[i + 1] \
			&& (*cmd_line)[i] == '$' && \
			((*cmd_line)[i + 1] != '\'') && (*cmd_line)[i + 1] != '"' \
			&& (ft_isalpha((*cmd_line)[i + 1]) || \
			(*cmd_line)[i + 1] == '?' || (*cmd_line)[i + 1] == '_' \
			|| (*cmd_line)[i + 1] == '$') \
			&& !replace_dollar_var((*cmd_line), &i, data, &new_str))
			return (0);
		if ((*cmd_line)[i] && !add_char(&(*cmd_line)[i], &new_str, &i, data))
			return (0);
	}
	free(*cmd_line);
	*cmd_line = new_str;
	return (1);
}
