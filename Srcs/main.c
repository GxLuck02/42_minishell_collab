/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:52:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/11 16:12:42 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void check_leaks(void)
{
    printf("Checking for memory leaks...\n");
    system("leaks minishell");  // Exécute la commande leaks
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_data	data;

	sleep(10);
	if (argc < 1 || !argv)
		return (1);
	atexit(check_leaks);
	if (!init_minishell(&data, envp))
		print_error(RED"Error with init of minishell"NRM);
	while (1)
	{
		cmd_line = get_prompt(&data);
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
