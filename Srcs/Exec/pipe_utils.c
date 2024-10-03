#include "../../Includes/minishell.h"


/*
si il y a une cmd prev
dup2(pipe_fd)
*/

void	execute_pipe(t_data *data, int pipe_fd[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("error fork\n", 2);
		exit(0);
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		make_cmd(data);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	handle_pipe(t_data *data)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("pipe Error\n", 2);
		return ;
	}
	execute_pipe(data, pipe_fd);
}
