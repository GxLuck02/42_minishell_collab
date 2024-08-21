/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:45:51 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 18:49:43 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	open_pipe(t_data *data)
{
	if (data->token && data->token->prev->token_type == PIPE)
	{
		write(2, "Error: syntax error pipe unclosed\n", 35);
		data->exit_code = 2;
		free_token(&data->token);
		return (0);
	}
	return (1);
}

int	check_pipe(t_data *data)
{
	if (data->token->token_type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	return (1);
}
