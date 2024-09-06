/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:18:25 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/06 07:09:21 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	load_default_env(t_data *data, t_env **new_env)
{
	
}

void	creat_env_list(t_env **head, char **envp)
{
	t_env	*new_node;
	char	**var;
	int		i;

	new_node == NULL;
	i = -1;
	while (envp[++i])
	{
		var = ft_envsplit(envp[i]);
	}
	

}

int	load_env(t_data *data, char **envp)
{
	int		i;
	t_env	*new_env;

	i = -1;
	new_env = NULL;
	if (!envp)
		load_default_env(&data, new_env);
	else
		creat_env_list(&new_env, envp);
	return (1);
}

