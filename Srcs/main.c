/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:52:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/07 17:05:10 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_data	data;

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
