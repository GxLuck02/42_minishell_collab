/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:47:20 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/13 19:01:46 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
		if (!quoted && !replace_dollar(&buf, data))
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
