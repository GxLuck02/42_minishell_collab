/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:47:20 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/28 18:00:29 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	replace_dollar_heredoc(char **cmd_line, t_data *data)
{
	int			i;
	char		*new_str;

	i = 0;
	new_str = ft_strdup("");
	while ((*cmd_line)[i] != '\0')
	{
		if ((*cmd_line)[i] && !data->sq && (*cmd_line)[i + 1] \
			&& (*cmd_line)[i] == '$' && \
			((*cmd_line)[i + 1] != '\'') && (*cmd_line)[i + 1] != '"' \
			&& (ft_isalpha((*cmd_line)[i + 1]) || \
			(*cmd_line)[i + 1] == '?' || (*cmd_line)[i + 1] == '_' \
			|| (*cmd_line)[i + 1] == '$') \
			&& !replace_dollar_var((*cmd_line), &i, data, &new_str))
			return (0);
		if ((*cmd_line)[i] && !add_char(&(*cmd_line)[i], &new_str, &i, data))
			return (0);
	}
	free(*cmd_line);
	*cmd_line = new_str;
	return (1);
}

static bool	read_in_stdin(t_data *data, int fd, char *word, bool quoted)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			print_error("warning: here-doc delimited by end-of-file (wanted '");
			print_error(word);
			print_error("')\n");
			break ;
		}
		if (!ft_strncmp(word, buf, ft_strlen(word)))
			break ;
		if (!quoted && !replace_dollar_heredoc(&buf, data))
		{
			free(buf);
			free_all(data, "Error : malloc error", EXT_MALLOC);
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	close(fd);
	return (true);
}

bool	gest_endfile(char *endfile)
{
	bool	ret;

	ret = false;
	if (endfile[0] == '"' || endfile[0] == '\'')
		ret = true;
	return (ret);
}

int	here_doc(t_data *data, char *end_file, bool quoted)
{
	int		fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(data, fd, end_file, quoted))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
