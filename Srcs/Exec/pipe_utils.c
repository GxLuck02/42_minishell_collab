#include "../../Includes/minishell.h"
void	handle_parent(int *pipe_fd, int status, pid_t pid)
{
		waitpid(pid, &status, 0);
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
			make_cmd(data);
			exit(EXIT_SUCCESS);
		}
}
void	execute_pipe(t_data *data)
{
	pid_t	pid;
	int		status;
	int	pipe_fd[2];

	status = 0;
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("pipe Error\n", 2);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_putstr_fd("error fork\n", 2);
		exit(0);
	}
	else if (pid == 0)
		handle_child(pipe_fd, data);
	else
		handle_parent(pipe_fd, status, pid);
}

void	handle_pipe(t_data *data)
{
	execute_pipe(data);
}
