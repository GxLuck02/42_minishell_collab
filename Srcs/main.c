/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:52:08 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/03 16:03:33 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmd = NULL;
	data->token = NULL;
	data->exit_code = 0;
}

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

void	creat_fictive_list(t_data *data)
{
	t_list	*tmp;

	tmp = NULL;
	append_node(&tmp, "USER=root");
	append_node(&tmp, "HOME=/root");
	append_node(&tmp, "VARIABLE1234=bah non");
	append_node(&tmp, "SHELL=/bin/bash");
	append_node(&tmp, "VAR_23=rip");
	append_node(&tmp, "VAR=Theo");
	data->env = tmp;
}

int	main()
{
	char	*cmd_line;
	t_data	data;

	init_data(&data);
	creat_fictive_list(&data);
	while (1)
	{
		cmd_line = get_prompt();
		printf("%s§\n", cmd_line);
		if (cmd_line == NULL)
			continue ;
		if (is_pars(&data, cmd_line) == 0)
			continue ;
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	return (0);
}
