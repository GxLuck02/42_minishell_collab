/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:35:37 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/11 14:12:11 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	delet_node(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*current;
	int		flag;
	
	flag = 0;
	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->next->key, str) == 0)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
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
