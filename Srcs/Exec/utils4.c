/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:07:13 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/31 13:48:41 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	jump_skip_cmd(t_data *data, int *len_cmd)
{
	while (data->cmd->skip_cmd == 1 && *len_cmd)
	{
		data->cmd = data->cmd->next;
		(*len_cmd)--;
	}
}

void	add_pid_tab(t_data *data, pid_t pid)
{
	static int	i = 0;

	if (!data->pid_tab[i])
	{
		data->pid_tab[i] = pid;
		data->pid_index = i;
		i++;
	}
	else
	{
		data->pid_tab[i] = pid;
		data->pid_index = i;
		i++;
	}
}

void	wait_all(t_data *data, int len_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < len_cmd)
	{
		waitpid(data->pid_tab[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
}

void	pipe_error(t_data *data)
{
	perror("pipe");
	free(data->pid_tab);
	exit(EXIT_FAILURE);
}
