/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:59 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/25 17:18:38 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	check_for_first_token(t_token *tmp)
{
	if (!ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<") || \
		!ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<"))
	{
		if (!tmp->next || (ft_strcmp(tmp->next->str, ">") == 0 || \
			ft_strcmp(tmp->next->str, "<") == 0 || \
			ft_strcmp(tmp->next->str, ">>") == 0 || \
			ft_strcmp(tmp->next->str, "<<") == 0))
		{
			printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
			return (0);
		}
	}
	if (ft_strncmp(tmp->str, ">", 1) == 0 || ft_strncmp(tmp->str, "<", 1) == 0)
	{
		if (ft_strlen(tmp->str) > 2 || (!ft_strcmp(tmp->str, "<>") || \
			!ft_strcmp(tmp->str, "><")))
		{
			printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
			return (0);
		}
	}
	return (1);
}

static int	check_token(t_token *tmp)
{
	int	ret;

	ret = 1;
	if (!ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<") || \
		!ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<"))
	{
		if (!tmp->next || (ft_strcmp(tmp->next->str, ">") == 0 || \
			ft_strcmp(tmp->next->str, "<") == 0 || \
			ft_strcmp(tmp->next->str, ">>") == 0 || \
			ft_strcmp(tmp->next->str, "<<") == 0))
		{
			printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
			ret = 0;
		}
	}
	return (ret);
}

static int	check_combination(t_token *tmp)
{
	int	ret;

	ret = 1;
	if (ft_strncmp(tmp->str, ">", 1) == 0 || ft_strncmp(tmp->str, "<", 1) == 0)
	{
		if (ft_strlen(tmp->str) > 2 || (!ft_strcmp(tmp->str, "<>") || \
			!ft_strcmp(tmp->str, "><")))
		{
			printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
			ret = 0;
		}
	}
	return (ret);
}

int	check_syntax(t_data *data)
{
	t_token	*tmp;
	int		ret;

	ret = 1;
	tmp = data->token;
	if (!check_for_first_token(tmp))
	{
		free_token(&data->token);
		return (0);
	}
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (!check_token(tmp) || !check_combination(tmp))
		{
			ret = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
		free_token(&data->token);
	return (ret);
}
