/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:20:05 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/07 19:20:09 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"


int check_n(char *cmd_param_1)
{
	int	i;

	i = 0;
	if (cmd_param_1[i] != '-')
		return (0);
	else
	{
		i++;
		while(cmd_param_1 && cmd_param_1[i])
		{
			if (cmd_param_1[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);

}

/*

verifie si le premier element du tableau est -n
si oui imprimer les elements suivants sans \n a la fin
si non imprime les elements suivants du tableau sans \n a la fin
*/
int ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (check_n(data->cmd->cmd_param[1]))
	{
		i = 2;
		while (data->cmd->cmd_param[i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], STDOUT_FILENO);
			if (data->cmd->next != NULL && data->cmd->cmd_param[i + 1])								//ligne pour verifier si il y a un pipe
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		i = 1;
		while (data->cmd->cmd_param[i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], STDOUT_FILENO);
			if (data->cmd->next != NULL && data->cmd->cmd_param[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
			
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}
