/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:31:07 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/13 18:36:02 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	count_args(t_data *data, t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	if (tmp->token_type == CMD || (tmp->token_type == ARG && \
			tmp->prev != data->token->prev && tmp->prev->token_type >= 5))
		count++;
	tmp = tmp->next;
	while (tmp != data->token && tmp->token_type != PIPE)
	{
		if (tmp->token_type == CMD || (tmp->token_type == ARG && \
			tmp->prev != data->token->prev && tmp->prev->token_type >= 5))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	add_cmd_param(char **cmd_param, int *i, char *param)
{
	if (!param)
		return (0);
	cmd_param[*i] = ft_strdup(param);
	if (cmd_param[*i] == NULL)
		return (0);
	(*i)++;
	return (1);
}

void	*free_cmd_param(char **cmd_params, int i)
{
	while (--i != -1)
		free (cmd_params[i]);
	free(cmd_params);
	return (NULL);
}

char	**get_params(t_data *data, t_token *token)
{
	char	**cmd_param;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	cmd_param = malloc((count_args(data, token) + 1) * sizeof(char *));
	if (!cmd_param)
		return (NULL);
	if (tmp->token_type != PIPE && (tmp->token_type == CMD || \
		(tmp->token_type == ARG && tmp->prev != data->token->prev \
	&& tmp->prev->token_type >= 5)) && !add_cmd_param(cmd_param, &i, tmp->str))
		return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp->token_type != PIPE && tmp != data->token)
	{
		if (tmp->token_type != PIPE && \
			(tmp->token_type == CMD || (tmp->token_type == ARG && \
			tmp->prev != data->token->prev && tmp->prev->token_type >= 5)) \
			&& !add_cmd_param(cmd_param, &i, tmp->str))
			return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	return (cmd_param);
}
