/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:18:25 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/14 16:35:33 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_var(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
}

int	create_node_env(t_env **head, char *str)
{
	t_env	*new_node;
	char	**var;

	new_node = (t_env *)malloc(sizeof (t_env));
	var = ft_envsplit(str);
	key_var_to_node(var, &new_node);
	free_var(var);
	if (!new_node)
		return (0);
	add_node_env(head, new_node);
	return (1);
}

int	load_default_env(t_env **head)
{
	if (!head)
		return (0);
	if (!create_node_env(head, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"))
		return (0);
	if (!create_node_env(head, "PWD=/home/user"))
		return (0);
	if (!create_node_env(head, "CC=/usr/bin/gcc"))
		return (0);
	if (!create_node_env(head, "SHLVL=1"))
		return (0);
	if (!create_node_env(head, "_=/usr/bin/env"))
		return (0);
	return (1);
}

int	creat_env_list(t_env **head, char **envp)
{
	t_env	*new_node;
	char	**var;
	int		i;

	new_node = NULL;
	i = -1;
	while (envp[++i])
	{
		var = ft_envsplit(envp[i]);
		if (!var)
			return (0);
		new_node = (t_env *)malloc(sizeof (t_env));
		equal_check(&new_node, envp[i]);
		if (!new_node)
		{
			free_var(var);
			return (0);
		}
		key_var_to_node(var, &new_node);
		free_var(var);
		if (!new_node)
			return (0);
		add_node_env(head, new_node);
	}
	return (1);
}

int	load_env(t_data *data, char **envp)
{
	t_env	*new_env;

	new_env = NULL;
	if (!creat_env_list(&new_env, envp))
	{
		if (!load_default_env(&new_env))
		{
			printf("Error: load default env as fail\n");
			return (0);
		}	
	}
	if (new_env)
	{
		data->env = new_env;
		data->env_tab = creat_env_copy(data->env);
		data->absolute_path = creat_env_copy(data->env);
		incr_shell_level(data);
	}
	if (!new_env)
	{
		if (!load_default_env(&new_env))
		{
			printf("Error: load default env as fail\n");
			return (0);
		}
		if (new_env)
			data->env = new_env;
		data->env_tab = creat_env_copy(data->env);
		data->absolute_path = creat_env_copy(data->env);
	}
	return (1);
}
