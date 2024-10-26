/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:26:20 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/26 12:21:42 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_isspecial(char *str)
{
	if (str && *str && ft_strlen(str) >= 2)
	{
		if (*str == '>' && *(str + 1) == '>')
			return (APPEND);
		if (*str == '<' && *(str + 1) == '<')
			return (HEREDOC);
	}
	if (str && *str && ft_strlen(str) >= 1)
	{
		if (*str == '<')
			return (INPUT);
		if (*str == '>')
			return (TRUNC);
		if (*str == '|')
			return (PIPE);
	}
	return (0);
}

int	len_token(char *command, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (command[i] && !ft_isspace(command[i]) && !ft_isspecial(command + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quotes)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\'' && \
			!ft_isspace(command[i]) && !ft_isspecial(command + i))
			++i;
	}
	return (i);
}

int	creat_node(t_token **new, char *str, int type, bool quoted)
{
	if (!str)
		return (0);
	(*new) = malloc(sizeof(t_token));
	if (!(*new))
	{
		free(str);
		return (0);
	}
	(*new)->quoted = quoted;
	(*new)->str = str;
	(*new)->token_type = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

void	its_first(t_token **begin, t_token *new)
{
	(*begin) = new;
	(*begin)->prev = *begin;
	(*begin)->next = *begin;
}

int	append_token(t_token **begin, char *str, int type, bool quoted)
{
	t_token	*new;

	if (!creat_node(&new, str, type, quoted))
		return (0);
	if (!(*begin))
		its_first(begin, new);
	else
	{
		new->prev = (*begin)->prev;
		new->next = (*begin);
		(*begin)->prev->next = new;
		(*begin)->prev = new;
	}
	return (1);
}
