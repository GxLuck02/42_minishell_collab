/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:06:57 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 18:48:15 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	is_valid_token(t_data *data)
{
	t_token *tmp;

	tmp = data->token;
	if (ft_strcmp(tmp->str, "&&") == 0|| ft_strcmp(tmp->str, ";") == 0|| \
			ft_strcmp(tmp->str, "\\") == 0)
	{
		free_token(&data->token);
		print_error("Error : one token is unvalide\n");
		return(0);
	}
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (ft_strcmp(tmp->str, "&&") == 0|| ft_strcmp(tmp->str, ";") == 0|| ft_strcmp(tmp->str, "\\") == 0)
		{
			free_token(&data->token);
			print_error("Error : one token is unvalide\n");
			return(0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("le token est %d et son contenu [%s]\n", tmp->token_type, tmp->str);
		tmp = tmp->next;
	}
	printf("le token est %d et son contenu [%s]\n", tmp->token_type, tmp->str);
}

void	print_array(char **cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i] != NULL)
	{
		printf("[%s]", cmd_param[i]);
		i++;
	}
	printf("\n");
}

void	print_cmd_list(t_cmd *list)
{
	t_cmd	*current;
	int		i;

	i = 1;
	current = list;
	printf("N° %d, infile %d, outfile %d ", i, current->infile, current->outfile);
	printf("cmd_param ");
	print_array(current->cmd_param);
	i++;
	current = current->next;
	while (current != list)
	{
		printf("N° %d, infile %d, outfile %d ", i, current->infile, current->outfile);
		printf("cmd_param ");
		print_array(current->cmd_param);
		current = current->next;
		i++;
	}
	
}

bool	is_pars(t_data *data, char *cmd_line)
{
	if (cmd_line == NULL)
		return (NULL);
	if (open_quote(cmd_line) == 1)
	{
		free(cmd_line);
		return (NULL);
	}
	if (!replace_dollar(&cmd_line, data) || !creat_token_list(&data->token, cmd_line))
	{
		free(cmd_line);
		free_all(data, "malloc error\n", EXT_MALLOC);
	}
	free(cmd_line);
	print_token(data->token);
	if (is_valid_token(data) == 0)
		return (0);
	if (!open_pipe(data))
		return (NULL);
	if (!data->token || !creat_cmd_list(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	print_cmd_list(data->cmd);
	return (check_pipe(data));
}
