/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:13:41 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/26 16:11:16 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_token(t_token **list)
{
	t_token	*current;
	t_token	*tmp;

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
	int		j;
	char	quote;

	quote = '\0';
	j = 0;
	while (j < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] != quote && str[i] != '\0')
				new_token[j++] = str[i++];
			i++;
			quote = '\0';
		}
		else
			new_token[j++] = str[i++];
	}
	new_token[j] = '\0';
}

int	add_cmd(t_token **begin, char **str)
{
	int		len;
	int		quotes;
	char	*new_str;
	bool	quoted;

	quotes = 0;
	quoted = false;
	len = len_token(*str, &quotes);
	if ((len) - (quotes * 2) < 0)
		return (1);
	new_str = malloc(((len + 1) - (2 * quotes)) * sizeof(char ));
	if (!new_str)
		return (0);
	copy_token(*str, len - (2 * quotes), new_str, 0);
	if (quotes > 0)
		quoted = true;
	if (!new_str || !append_token(begin, new_str, 0, quoted))
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

	spe = ft_isspecial(*str);
	if (!str)
		return (0);
	if (spe == INPUT && !append_token(begin, ft_strdup("<"), INPUT, false))
		return (0);
	else if (spe == HEREDOC && !append_token \
			(begin, ft_strdup("<<"), HEREDOC, false))
		return (0);
	else if (spe == TRUNC && !append_token(begin, ft_strdup(">"), TRUNC, false))
		return (0);
	else if (spe == APPEND && !append_token \
			(begin, ft_strdup(">>"), APPEND, false))
		return (0);
	else if (spe == PIPE && !append_token(begin, ft_strdup("|"), PIPE, false))
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
		if (*cmd_line && !ft_isspecial(cmd_line) && !add_cmd(begin, &cmd_line))
		{
			if (*begin)
				free_token(begin);
			return (0);
		}
		else if (*cmd_line && ft_isspecial(cmd_line) && \
				!add_special(begin, &cmd_line))
		{
			if (*begin)
				free_token(begin);
			return (0);
		}
	}
	return (1);
}
