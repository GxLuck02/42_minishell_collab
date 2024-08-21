/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:37:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 15:46:50 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

void	free_all_cmd(t_cmd *list)
{
	if (!(list))
		return ;
	if (list->infile > 0)
		close(list->infile);
	list->infile = -2;
	if (list->outfile > 0)
		close(list->outfile);
	list->outfile = -2;
	free_array(list->cmd_param);
}

void	free_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*current;
	
	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free_all_cmd(tmp);
		free(tmp);
	}
	free_all_cmd(current);
	free(current);
	*list = NULL;
}