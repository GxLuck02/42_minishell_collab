/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:41 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/28 18:01:56 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

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
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 1;
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
		ft_putstr_fd("signal error\n", 2);
}
