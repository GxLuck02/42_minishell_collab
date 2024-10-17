/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:19:57 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/17 21:20:16 by tmontani         ###   ########.fr       */
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
    if (str[i] == '-' || str[i] == '+')
        i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

static long long	long_cmp(const char *s1)
{
	char	*longmax;
	char	*longmin;
	int		len;

	longmax = "9223372036854775807";
	longmin = "-9223372036854775808";
	len = ft_strlen(s1);
	if (len > 19 && s1[0] != '-')
		return (1);
	if (len > 20 && s1[0] == '-')
		return (1);
	else if (len == 19)
	{
		if (s1[0] == '-')
		{
			if (ft_strcmp(s1, longmin) > 0)
				return (1);
		}
		else
		{
			if (ft_strcmp(s1, longmax) > 0)
				return (1);
		}
	}
	return (0);
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
        printf("exit\n");
        free_all(data, 0, -1);
        exit(0);
    }
    if (long_cmp(data->cmd->cmd_param[1]) == 1)
    {
        printf("exit\n");
        exit(255);
    }
    if (len_array(data->cmd->cmd_param) >= 2)
    {
        if(!ft_is_numeric(data->cmd->cmd_param[1]))
        {
            printf("bash: exit: %s: numeric argument required\n", data->cmd->cmd_param[1]);
            exit_code = 2;
            free_all(data, 0, -1);
            exit(2);
        }
    }
        if (len_array(data->cmd->cmd_param) > 2)
        {
            printf("exit\nbash: exit too many arguments\n");
            return ;
        }
        exit_code = ft_atoi(data->cmd->cmd_param[1]) % 256;
            free_all(data, 0, -1);
        printf("exit\n");
        exit(exit_code);
}

