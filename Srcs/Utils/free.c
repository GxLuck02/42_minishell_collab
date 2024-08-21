/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:38 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 18:58:08 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	free_list(t_list **list)
{
	t_list *current;
	t_list *tmp;

	if (!(*list))
		return (0);
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
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
		exit(ext);
}
