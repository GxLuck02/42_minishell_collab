/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:07:13 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/28 17:38:23 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
			data->exit_code = WEXITSTATUS(status);
		i++;
	}
}

void	pipe_error(t_data *data)
{
	perror("pipe");
	free(data->pid_tab);
	exit(EXIT_FAILURE);
}
