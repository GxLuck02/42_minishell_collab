/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:38 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/17 16:51:36 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

 void    free_node(t_env *env)
{
        free(env->key);
        free(env->value);
        free(env);
}

void	free_table(char **table)
{
	int	i;

	i = -1;
	if (!table)
		return ;
	while (table[++i])
		free(table[i]);
	free(table);
}

int	free_list(t_env **list)
{
	t_env	*current;
	t_env	*tmp;

	if (!(*list) || !list)
		return (0);
	current = *list;
	while (current->next)
	{
		tmp = current;
		current = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*list = NULL;
	return (1);
}

bool	print_error(char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

void	free_all(t_data *data, char *err, int ext)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
	if (data->env)
		free_list(&data->env);
	if (err)
		print_error(err);
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(0);
}
