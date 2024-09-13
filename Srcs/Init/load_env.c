/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:18:25 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/13 18:38:53 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_var(char **var)
{
	free(var[0]);
	free(var[1]);
	free(var);
}

/*int creat_node(t_env **head, char *str)
{
	t_env	*new_node;
	char	**var;

	new_node = NULL;
	var = ft_envsplit(str);
	key_var_to_node(var, &new_node);
	free_var(var);
	if (!new_node)
		return (0);
	add_node_env(head, new_node);
	return (1);
}*/

int	load_default_env(/*t_env **head*/)
{
	/*if (head)
		return (0);
	if (!create_node("CC=/usr/bin/gcc"))
		return (0);
	if (!create_node("OLDPWD"))
		return (0);
	if (!create_node("PWD=/Users/theo/Desktop/minishell_collab"))
		return (0);
	if (!create_node("SHLVL=1"))
		return (0);*/
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
	if (!envp)
	{
		if (!load_default_env())
			return (0);
		data->env = new_env;
	}
	else
	{
		if (!creat_env_list(&new_env, envp))
			return (0);
		data->env = new_env;
		incr_shell_level(data->env);
	}
	return (1);
}
