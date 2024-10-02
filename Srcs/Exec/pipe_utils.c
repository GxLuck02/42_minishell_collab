#include "../../Includes/minishell.h"


/*
si il y a une cmd prev
dup2(pipe_fd)
*/
void	set_redirections(t_data *data, pipe_fd)
{
	if ()
}









/*
gere toute l'execution en cas de pipe

*/
void	handle_pipe(t_data *data)
{
	int	pipe_fd[2];
	pid_t	pid;
	int		flag;

	while(data->cmd)
	{
		if(pipe(pipe_fd) == -1)
		{
			ft_putstr_fd("pipe error\n", 2);
			return ;
		}
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("fork error\n", 2);
			exit(0);
		}
		else if(pid == 0)
			set_redirections(data, pipe_fd);
	}
}
