/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:13:41 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/01 17:34:33 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_token(t_token **list)
{
	t_token *current;
	t_token *tmp;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
	*list = NULL;
}

void	copy_token(char *str, int len, char *new_token, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && i < len)
	{
		if (str[i + j] == '\'' && j++)
		{
			while (str [i + j] != '\''  && i++)
				new_token[i - 1] = str[(i - 1) + j];
			j++;
		}
		else if (str[i + j] == '"' && j++)
		{
			while (str [i + j] != '"' && i++)
				new_token[i - 1] = str[(i - 1) + j];
			j++;
		}
		else
		{
			new_token[i] = str[i + j];
			i++;
		}
	}
	new_token[i] = '\0';
}

int	add_cmd(t_token **begin, char **str)
{
	int		len;
	int		quotes;
	char	*new_str;

	quotes = 0;
	len = len_token(*str, &quotes);
	if ((len) - (quotes * 2) < 0)
		return (1);
	new_str = malloc(((len + 1) - (2 * quotes)) * sizeof(char ));
	if (!new_str)
		return (0);
	copy_token(*str, len - (2 * quotes), new_str, 0);
	if (!new_str)
		return (0);
	if (!append_token(begin, new_str, 0))
		return (0);
	if ((*begin)->prev == (*begin) || (*begin)->prev->prev->token_type == PIPE)
		(*begin)->prev->token_type = CMD;
	else
		(*begin)->prev->token_type = ARG;
	(*str) += len;
	return (1);
}

int	add_special(t_token **begin, char **str)
{
	int	spe;

	spe = isspecial(*str);
	if (!str)
		return (0);
	if (spe == INPUT && !append_token(begin, ft_strdup("<"), INPUT))
		return (0);
	else if (spe == HEREDOC && !append_token(begin, ft_strdup("<<"), HEREDOC))
		return (0);
	else if (spe == TRUNC && !append_token(begin, ft_strdup(">"), TRUNC))
		return (0);
	else if (spe == APPEND && !append_token(begin, ft_strdup(">>"), APPEND))
		return (0);
	else if (spe == PIPE && !append_token(begin, ft_strdup("|"), PIPE))
		return (0);
	if (spe == PIPE || spe == INPUT || spe == TRUNC)
		(*str)++;
	else if (spe == HEREDOC || spe == APPEND)
		(*str) += 2;
	return (1);
}

bool	creat_token_list(t_token **begin, char *cmd_line)
{
	(*begin) = NULL;
	while (*cmd_line)
	{
		while (*cmd_line && ft_isspace(*cmd_line))
			cmd_line++;
		if (*cmd_line && !isspecial(cmd_line) && !add_cmd(begin, &cmd_line))
		{
			if (*begin)
				free_token(begin);
			return (0);
		}
		else if (*cmd_line && isspecial(cmd_line) && !add_special(begin, &cmd_line))
		{
			if (*begin)
				free_token(begin);
			return (0);
		}
	}
	return (1);
}
