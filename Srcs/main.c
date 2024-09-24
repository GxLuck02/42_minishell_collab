/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:52:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/24 10:43:25 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*void	creat_fictive_list(t_data *data)
{
	t_list	*tmp;

	tmp = NULL;
	append_node(&tmp, "USER=root");
	append_node(&tmp, "HOME=/root");
	append_node(&tmp, "VARIABLE1234=bah non");
	append_node(&tmp, "SHELL=/bin/bash");
	append_node(&tmp, "VAR_23=rip");
	append_node(&tmp, "VAR=Theo");
	data->env = tmp;
}*/

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
			continue ;
		if (is_pars(&data, cmd_line) == 0)
			continue ;
		exec(&data);
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	rl_clear_history();
	return (0);
}
