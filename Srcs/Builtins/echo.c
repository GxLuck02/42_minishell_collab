/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:20:05 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/25 16:09:15 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	check_infile(t_data *data)
{
	int bytes_read;
	char *buf;
	
	bytes_read = 0;
	if (data->cmd->infile != -2 && data->cmd->infile >= 0)	
	{
	    while ((buf = get_next_line(data->cmd->infile)))
		{
			if (!buf)
				break ;
        	printf("%s", buf);
    	}
		return (1);
	}
	return (0);
}

int	check_n(char **cmd_param, int *index)
{
	bool	n_find;

	n_find = false;
	if (cmd_param[*index] == NULL)
		return (0);
	if (cmd_param[*index][0] != '-')
		return (0);
	else
	{
		while (cmd_param[*index] != NULL)
		{
			if (ft_strcmp(cmd_param[*index], "-n") != 0)
				break ;
			n_find = true;
			(*index)++;
		}
	}
	if (n_find == true)
		return (1);
	return (0);
}

/*
verifie si le premier element du tableau est -n
si oui imprimer les elements suivants sans \n a la fin
si non imprime les elements suivants du tableau sans \n a la fin
*/
int	ft_echo(t_data *data)
{
	int	i;

	i = 1;
	if (check_infile(data))
		return (0);
	else if (check_n(data->cmd->cmd_param, &i))
	{
		while (data->cmd->cmd_param[i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], 1);
			if (data->cmd->next != NULL && data->cmd->cmd_param[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	else
	{
		i = 0;
		while (data->cmd->cmd_param[++i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], 1);
			if (data->cmd->next != NULL && data->cmd->cmd_param[i + 1])
				ft_putchar_fd(' ', 1);
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
