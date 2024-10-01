#include "../../Includes/minishell.h"

/*recupere les deux commandes a relier
*/
void	handle_pipe(t_cmd *cmd1, t_cmd *cmd2)
{
	pid_t pid;
	int	status;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_putstr("error_pipe\n");
	
	pid = fork();
    if (pid < 0)
    {
		perror("fork failed");
    	exit(0);
	}
	if (pid == 0)
	{
		
	}
}