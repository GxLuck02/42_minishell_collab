/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:52:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/13 18:42:50 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_data	data;
	struct sigaction sa;
    sa.sa_handler = &handle_c;
    sigaction(SIGINT, &sa, NULL);
	
	if (argc < 1 || !argv)
		return (1);
	if (!init_minishell(&data, envp))
		print_error(RED"Error with init of minishell"NRM);
	while (1)
	{
		cmd_line = get_prompt();
		printf(BLU"%s§\n"NRM, cmd_line);
		if (cmd_line == NULL)
		{
			continue ;
		}
			
		if (is_pars(&data, cmd_line) == 0)
			continue ;
		exec(&data);
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	free_all(&data, "exit", 0);
	rl_clear_history();
	return (0);
}
