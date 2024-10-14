/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:19:57 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/14 16:08:51 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int len_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}
int	exit_error(char *arg)
{
    ft_putstr_fd("bash: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}
bool	ft_is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

/*
1. verifier si l'argument de exit est un nombre
2. afficher exit
3. gerer les cas
    pas d'arg exit(0)
    1 arg verifier si c'est un nb et quitter avec
    plusieurs args error
*/
void    ft_exit(t_data *data)
{
    int exit_code;

    exit_code = 0;
    if (len_array(data->cmd->cmd_param) == 1)
    {
        free_all(data, 0, 0);
        exit(0);
    }
    if (len_array(data->cmd->cmd_param) >= 2)
    {
        if(!ft_is_numeric(data->cmd->cmd_param[1]))
        {
            printf("bash: exit: %s: numeric argument required\n", data->cmd->cmd_param[1]);
            exit_code = ft_atoi(data->cmd->cmd_param[1]) % 256;
            free_all(data, 0, 0);
            exit(exit_code);
        }
    }
        if (len_array(data->cmd->cmd_param) > 2)
        {   printf("exit\nbash: exit too many arguments\n");
            return ;
        }
        exit_code = ft_atoi(data->cmd->cmd_param[1]) % 256;
            free_all(data, 0, 0);
        exit(exit_code);
}
