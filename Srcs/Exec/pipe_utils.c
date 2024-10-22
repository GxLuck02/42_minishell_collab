/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:33 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/22 18:16:37 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	handle_parent(int *pipe_fd)
{
	close(STDIN_FILENO);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	handle_child(int *pipe_fd, t_data *data)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (is_builtin(data))
	{
		execute_builtin(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		make_cmd(data, 1);
		exit(EXIT_SUCCESS);
	}
}

void	execute_pipe(t_data *data)
{
	int			pipe_fd[2];
	static	int	i;

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("pipe Error\n", 2);
		return ;
	}
	data->pid_tab[i] = fork();
	if (data->pid_tab[i] < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_putstr_fd("error fork\n", 2);
		exit(0);
	}
	else if (data->pid_tab[i] == 0)
		handle_child(pipe_fd, data);
	else
	{
		i++;
		handle_parent(pipe_fd);
	}
}

