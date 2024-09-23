/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:46:55 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/23 17:02:31 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	incr_shell_level(t_env *head)
{
	t_env	*tmp;
	int		sh_level;
	char	*new_value;

	tmp = head;
	while (tmp && ft_strcmp(tmp->key, "SHLVL"))
		tmp = tmp->next;
	if (tmp)
	{
		sh_level = ft_atoi(tmp->value) + 1;
		if (sh_level < 0)
			sh_level = 0;
		new_value = ft_itoa(sh_level);
		if (!new_value)
			return ;
		free(tmp->value);
		tmp->value = new_value;
	}
	return ;
}

void	key_var_to_node(char **var, t_env **node)
{
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
