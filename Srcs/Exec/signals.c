#include "../../Includes/minishell.h"

void	handle_ctrl_d(char *cmd_line)
{
	if (!cmd_line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
}

// lorsque control c est appele si des child process sont en cours
//exit les child process et affiche un nouveau prompt
//sinon
//affiche un nouveau prompt
void	handle_sigint()
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	if (signal(SIGINT, &handle_sigint) == SIG_ERR
	|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
	|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("signal erro\n", 2);
}