/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:47:20 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/31 15:14:52 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	here_doc_loop(t_data *data, int fd, char *word, bool quoted)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(word, buf, ft_strlen(word)))
		{
			if (!buf)
			{
				close(fd);
				unlink(".heredoc.tmp");
				g_exit_code = 1;
			}
			break ;
		}
		if (!quoted && !replace_dollar_heredoc(&buf, data))
		{
			free(buf);
			free_all(data, "Error : malloc error", EXT_MALLOC);
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
}

static int	read_in_stdin(t_data *data, int fd, char *word, bool quoted)
{
	struct sigaction	*prev_handler;

	prev_handler = signal_heredoc(data);
	here_doc_loop(data, fd, word, quoted);
	sigaction(SIGINT, prev_handler, NULL);
	free(prev_handler);
	close(fd);
	return (1);
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
