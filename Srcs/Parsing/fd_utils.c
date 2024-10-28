/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:39:16 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/26 16:11:48 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	open_file(t_data *data, char *file_name, int type, t_token *token)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(file_name, O_RDONLY, 0644);
	else if (type == HEREDOC)
	{
		data->heredoc = 1;
		fd = here_doc(data, file_name, token->quoted);
	}
	else if (type == APPEND)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == TRUNC)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type != HEREDOC && fd < 0)
		perror(file_name);
	return (fd);
}

int	get_inf(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->token_type == INPUT)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->token_type <= 5)
			return (0);
		cmd->infile = open_file(data, tmp->next->str, INPUT, NULL);
		if (cmd->infile == -1)
			return (0);
	}
	if (tmp->token_type == HEREDOC)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->token_type <= 5)
			return (0);
		cmd->infile = open_file(data, tmp->next->str, HEREDOC, tmp->next);
		if (cmd->infile == -1)
			return (0);
	}
	return (1);
}

int	get_infile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->token_type != PIPE && !get_inf(data, tmp, cmd))
		return (0);
	if (tmp->token_type == PIPE)
		return (1);
	tmp = tmp->next;
	while (tmp->token_type != PIPE && tmp != data->token)
	{
		if (!get_inf(data, tmp, cmd))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	get_outf(t_token *tmp, t_cmd *cmd)
{
	if (tmp->token_type == TRUNC)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->token_type <= 5)
			return (0);
		cmd->outfile = open_file(NULL, tmp->next->str, TRUNC, NULL);
		if (cmd->outfile == -1)
			return (0);
	}
	if (tmp->token_type == APPEND)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->token_type <= 5)
			return (0);
		cmd->outfile = open_file(NULL, tmp->next->str, APPEND, NULL);
		if (cmd->outfile == -1)
			return (0);
	}
	return (1);
}

int	get_outfile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->token_type != PIPE && !get_outf(tmp, cmd))
		return (0);
	tmp = tmp->next;
	while (tmp->token_type != PIPE && tmp != data->token)
	{
		if (!get_outf(tmp, cmd))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
