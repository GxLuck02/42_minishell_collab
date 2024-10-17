/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:40:27 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/17 17:37:37 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	change_value(t_env **env, t_env *new_node)
{
	t_env	*current;

	current = *env;
	if (!env || !new_node)
		return ;
	while (ft_strcmp(current->key, new_node->key) != 0)
		current = current->next;
	free(current->value);
	current->value = ft_strdup(new_node->value);
	current->equal = true;
	free(new_node->key);
	free(new_node->value);
	free(new_node);
}

bool	var_already_exist(t_env *env, char *key)
{
	if (!env)
		return (false);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}


int	env_lenthg(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static char	*copy_key_value(t_env *env)
{
		char	*line;
		char	*key;
		
		if (env->equal == true)
			key = ft_strjoin(env->key, "=\"");
		else
			key = ft_strdup(env->key);
		line = ft_strjoin(key, env->value);
		free(key);
		if (env->equal == true)
			key = ft_strjoin(line, "\"");
		else
			key = ft_strdup(line);
		free(line);
		line = ft_strdup(key);
		free(key);
		return (line);
}

char	**creat_table(t_env *env)
{
	int		len_lst;
	char	**env_tab;
	char	*line;
	int		i;
	
	i = 0;
	len_lst = ft_lstsize_env(env);
	env_tab = malloc(sizeof (char *) * (len_lst + 1));
	while (env)
	{
		line = copy_key_value(env);
		env_tab[i] = line;
		if(!env_tab[i])
			return (NULL);
		i++;
		env = env->next;
	}
	env_tab[i] = NULL;
	return(env_tab);

}
