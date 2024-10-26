/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 05:40:00 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/26 16:13:16 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmd = NULL;
	data->token = NULL;
	data->env_tab = NULL;
	data->absolute_path = NULL;
	data->exit_code = 0;
	data->heredoc = 0;
}

int	init_minishell(t_data *data, char **envp)
{
	init_data(data);
	if (load_env(data, envp) == 0)
		return (0);
	return (1);
}
