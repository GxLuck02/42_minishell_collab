/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:27:27 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/25 17:46:15 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_loop(t_data *data, int i, int len_cmd)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_fd;

	prev_fd = -1;
	while (++i < len_cmd)
	{
		if (i < len_cmd - 1 && pipe(pipe_fd) == -1)
			pipe_error(data);
		pid = fork();
		if (pid < 0)
			fork_fail(data);
		if (pid == 0)
			handle_child(data, len_cmd, prev_fd, pipe_fd, i);
		else
			handle_parent(data, len_cmd, pid, i, &prev_fd, pipe_fd);
		data->cmd = data->cmd->next;
	}
	return ;
}
