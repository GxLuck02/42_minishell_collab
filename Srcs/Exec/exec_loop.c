/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:27:27 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/29 15:45:19 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_loop(t_data *data, int len_cmd)
{
	pid_t	pid;
	int		i;

	i = -1;
	data->prev_fd = -1;
	init_pid_tab(data, len_cmd);
	while (++i < len_cmd)
	{
			if(data->cmd->skip_cmd == 0)
			{
			if (i < len_cmd - 1 && pipe(data->pipe_fd) == -1)
				pipe_error(data);
			pid = fork();
			if (pid < 0)
				fork_fail(data);
			if (pid == 0)
				handle_child(data, len_cmd, i);
			else
				handle_parent(data, len_cmd, pid, i);
			}
		data->cmd = data->cmd->next;
	}
	return ;
}
