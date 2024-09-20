/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:45:51 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/13 18:20:29 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_list	*create_node(char *str)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

// Helper function to append a node to the list
void	append_node(t_list **head, char *str)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node(str);
	current = *head;
	if (current == NULL)
	{
		*head = new_node;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}

int	open_pipe(t_data *data)
{
	if (data->token && data->token->prev->token_type == PIPE)
	{
		write(2, "Error: syntax error pipe unclosed\n", 35);
		data->exit_code = 2;
		free_token(&data->token);
		return (0);
	}
	return (1);
}

int	check_pipe(t_data *data)
{
	if (data->token->token_type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	return (1);
}

//Calculate the length of a chained list
int	len_list(t_env *list)
{
	int		len;
	t_env	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	len = 1;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
