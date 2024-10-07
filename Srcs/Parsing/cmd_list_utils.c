/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:32:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/07 16:18:54 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	init_new_cmd(t_cmd **cmd, int infile, int outfile, char **cmd_param)
{
	(*cmd) = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (0);
	(*cmd)->skip_cmd = false;
	(*cmd)->infile = infile;
	(*cmd)->outfile = outfile;
	(*cmd)->cmd_param = cmd_param;
	(*cmd)->next = NULL;
	(*cmd)->prev = NULL;
	return (1);
}

int	append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param)
{
	t_cmd	*new;

	if (!init_new_cmd(&new, infile, outfile, cmd_param))
		return (0);
	if ((*list) == NULL)
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}
