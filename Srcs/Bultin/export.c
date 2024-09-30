/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:41 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/30 18:56:54 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	fill_tab(t_env *current, char **tab)
{
	char	*tmp;

	*tab = ft_strdup(current->key);
	tmp = ft_strjoin(*tab, "=");
	free(*tab);
	*tab = ft_strjoin(tmp, current->value);
	free(tmp);
}

int	env_lenthg(t_env *env)
{
	int	len;

	len = 0;
	while (env != NULL)
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
		tab_env[i] = malloc((ft_strlen(current->value) + ft_strlen(current->key) + 2) * sizeof(char ));
		if (tab_env[i] == NULL)
			return (NULL);
		fill_tab(current, &tab_env[i]);
		current = current->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

int	export_no_args(t_env *env)
{
	char	**new_tab;
	int		i;
	
	if (!env)
		return (EXIT_SUCCESS);
	i = 0;
	new_tab = creat_table(env);
	while (new_tab[i] != NULL)
	{
		printf("%s\n",new_tab[i]);
		free(new_tab[i]);
		i++;
	}
	free(new_tab);
	return (EXIT_SUCCESS);
}

int	export(t_env **env, char **args)
{
	if (!args[1])
		return (export_no_args(*env));
	return (EXIT_SUCCESS);
}
