/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:40:27 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/03 16:40:51 by ttreichl         ###   ########.fr       */
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

void	fill_tab(t_env *current, char **tab)
{
	char	*tmp;
	char	*tmp2;

	*tab = ft_strdup(current->key);
	tmp = ft_strjoin(*tab, "=\"");
	free(*tab);
	tmp2 = ft_strjoin(tmp, current->value);
	free(tmp);
	*tab = ft_strjoin(tmp2, "\"");
	free(tmp2);
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

char	**creat_table(t_env *env)
{
	t_env	*current;
	int		nbr_var;
	char	**tab_env;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	current = env;
	nbr_var = env_lenthg(env);
	tab_env = (char **)malloc((nbr_var + 1) * sizeof(char *));
	if (!tab_env)
		return (NULL);
	while (current != NULL)
	{
		tab_env[i] = malloc((ft_strlen(current->value) + ft_strlen(current->key) + 4) * sizeof(char ));
		if (tab_env[i] == NULL)
			return (NULL);
		fill_tab(current, &tab_env[i]);
		current = current->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}
