/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 05:40:00 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/11 16:05:52 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmd = NULL;
	data->token = NULL;
	data->exit_code = 0;
}

int	init_minishell(t_data *data, char **envp)
{
	init_data(data);
	if (load_env(data, envp) == 0)
		return (0);
	return (1);
}
