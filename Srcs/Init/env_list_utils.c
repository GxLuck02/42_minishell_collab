/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:46:55 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/14 16:08:14 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int ft_lstsize_env(t_env *lst)
{
    int result = 0;

    while (lst) {
        lst = lst->next;
        result++;
    }
    return result;
}

/*
fais une copie de l'environnement sous forme de double tableau pour execve
aussi utilisée pour faire une autre copie pour executer les absolute_path
*/
char	**creat_env_copy(t_env *env)
{
	int		len_lst;
	char	**env_tab;
	char	*line;
	char	*key;
	int		i;
	
	i = 0;
	len_lst = ft_lstsize_env(env);
	env_tab = malloc(sizeof (char *) * (len_lst + 1));
	while (env)
	{
		key = ft_strjoin(env->key, "=");
		line = ft_strjoin(key, env->value);
		env_tab[i] = ft_strdup(line);
		if(!env_tab[i])
			return (NULL);
		i++;
		free(line);
		free(key);
		env = env->next;
	}
	env_tab[i] = NULL;
	return(env_tab);
}
void	incr_shell_level(t_data *data)
{
	t_env 	*SHLVL;
	int		sh_level;
	char	*new_value;

	SHLVL = ft_getenv("SHLVL", data->env);
	sh_level = ft_atoi(SHLVL->value);
		if (sh_level < 0)
			sh_level = 0;
		sh_level += 1;
		new_value = ft_itoa(sh_level);
		if (!new_value)
			return ;
		free(SHLVL->value);
		SHLVL->value = new_value;
	return ;
}

void	key_var_to_node(char **var, t_env **node)
{
	if (!var)
		return ;
	(*node)->key = ft_strdup(var[0]);
	(*node)->value = ft_strdup(var[1]);
	(*node)->next = NULL;
	if (!(*node)->key || !(*node)->value)
	{
		if ((*node)->key)
			free((*node)->key);
		if ((*node)->value)
			free((*node)->value);
		free(*node);
		*node = NULL;
	}
}

void	add_node_env(t_env **head, t_env *node)
{
	t_env	*tmp;

	tmp = *head;
	if (!*head)
		*head = node;
	else
	{
		while ((tmp)->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}
