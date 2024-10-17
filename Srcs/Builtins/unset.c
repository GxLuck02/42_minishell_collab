/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:35:37 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/17 16:58:23 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void    delet_node(t_env **env, char *str)
{
    t_env    *tmp;
    t_env    *current;

    if (!*env || !env)
        return ;
    if (ft_strcmp((*env)->key, str) == 0)
    {
        tmp = *env;
        *env = (*env)->next;
        free_node(tmp);
        return ;
    }
    current = *env;
    while (current && current->next)
    {
        if (ft_strcmp(current->next->key, str) == 0)
        {
            tmp = current->next;
            current->next = tmp->next;
            free_node(tmp);
            return ;
        }
        current = current->next;
    }
}

int	unset_var(t_env **env, char *str)
{
	if (var_already_exist(*env, str) == true)
		delet_node(env, str);
	else
		return (1);
	return (1);
}

int	ft_unset(t_env **env, char **args)
{
	int	i;
	
	i = 1;
	if (!args[1])
		return (1);
	else
	{
		while (args[i] != NULL)
		{
			if (!is_valid_var(args[i]))
			{	
				invalid_var(args[i]);
				return (0);
			}
			else if (!unset_var(env, args[i]))
				return(0);
			i++;
		}
	}
	return (1);
}
