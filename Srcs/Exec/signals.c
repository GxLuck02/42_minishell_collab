/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:41 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/31 16:08:10 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	handle_ctrl_d(char *cmd_line)
{
	if (!cmd_line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	g_exit_code = 1;
}

// lorsque control c est appele si des child process sont en cours
//exit les child process et affiche un nouveau prompt
//sinon
//affiche un nouveau prompt
void	setup_signals(t_data *data)
{
	(void)data;
	if (signal(SIGINT, &handle_sigint) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("signal error\n", 2);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_exit_code = 1;
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

//Fonction d'installation du gestionnaire de signal avec sigaction
void	*signal_heredoc(t_data *data)
{
	struct sigaction	sa;
	struct sigaction	*prev_handler;

	prev_handler = malloc(sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	data->exit_code = g_exit_code;
	sigaction(SIGINT, &sa, prev_handler);
	return (prev_handler);
}
