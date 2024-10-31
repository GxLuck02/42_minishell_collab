/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:13:51 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/31 13:48:52 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	fill_cmd(t_data *data, t_token *tmp)
{
	if (!get_infile(data, tmp, data->cmd->prev) && \
		data->cmd->prev->infile != -1)
		return (0);
	if (data->cmd->prev->infile == -1)
	{
		data->cmd->prev->skip_cmd = true;
		data->cmd->prev->outfile = -1;
		return (1);
	}
	if (!get_outfile(data, tmp, data->cmd->prev) && \
		data->cmd->prev->outfile != -1)
		return (0);
	if (data->cmd->prev->outfile == -1)
	{
		if (data->cmd->prev->infile >= 0)
			close(data->cmd->prev->infile);
		data->cmd->prev->skip_cmd = 1;
		data->cmd->prev->infile = -1;
		return (1);
	}
	data->cmd->prev->cmd_param = get_params(data, tmp);
	if (!data->cmd->prev->cmd_param)
		free_all(data, "error malloc", EXT_MALLOC);
	return (1);
}

int	norm(t_data *data, t_token *tmp)
{
	if (!tmp)
		return (0);
	if (!append_cmd(&data->cmd, -2, -2, NULL))
		free_all(data, "error malloc", EXT_MALLOC);
	if (!fill_cmd(data, tmp))
	{
		g_exit_code = 2;
		return (0);
	}
	return (1);
}

int	creat_cmd_list(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!norm(data, tmp))
		return (0);
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (tmp->prev->token_type == PIPE)
		{
			if (!norm(data, tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
