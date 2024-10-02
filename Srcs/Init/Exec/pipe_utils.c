#include "../../Includes/minishell.h"

/*recupere les deux commandes a relier
cree le pipe
fork 
dup2 pour rediriger

*/
void	handle_pipe(t_data *data)
{
	ft_putstr_fd("test\n", 2);
	int pipe_fd[2];
	int status;
	pid_t	pid;

		if (pipe(pipe_fd) == -1)
		{
			ft_putstr_fd("pipe error\n", 2);
			exit(0);
		}
	while (data->cmd)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("fork error\n", 2);
			exit(0);
		}
		else if (pid == 0)
		{
			if (!data->cmd)
				exit(0);
			if (data->cmd->next)
			{
				ft_putstr_fd("first_cmd\n", 2);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				make_cmd(data);
				exit(0);
			}
			else if(!data->cmd->next)
			{
				ft_putstr_fd("second\n", 2);
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
				make_cmd(data);
				exit(0);
			}
		}
		else
		{
			ft_putstr_fd("inside\n", 2);
			data->cmd = data->cmd->next;
			waitpid(pid, &status, 0);
		}
	}
}
