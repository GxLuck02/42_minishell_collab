/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:41 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/31 08:57:58 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_data	*g_data_ptr = NULL;

void	handle_ctrl_d(char *cmd_line)
{
	if (!cmd_line)
	{
		if (g_data_ptr)
			g_data_ptr->heredoc = 0;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// lorsque control c est appele si des child process sont en cours
//exit les child process et affiche un nouveau prompt
//sinon
//affiche un nouveau prompt
void	setup_signals(void)
{
	if (signal(SIGINT, &handle_sigint) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("signal error\n", 2);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	if (g_data_ptr)
	{
		g_data_ptr->heredoc_interrupted = true;
		g_data_ptr->exit_code = 1;
		g_data_ptr->heredoc = 0;
	}
	rl_replace_line("", 0);
	rl_redisplay();
	ft_putstr_fd("\n", STDERR_FILENO);
	close(STDIN_FILENO);
}

//Fonction d'installation du gestionnaire de signal avec sigaction
void	*signal_heredoc(t_data *data)
{
	struct sigaction	sa;
	struct sigaction	*prev_handler;

	prev_handler = malloc(sizeof(struct sigaction));
	g_data_ptr = data;
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, prev_handler);
	return (prev_handler);
}
