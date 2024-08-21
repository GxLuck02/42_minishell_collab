/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:47:20 by ttreichl          #+#    #+#             */
/*   Updated: 2024/07/15 16:10:02 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	read_in_stdin(t_data *data, int fd, char *word)
{
	char	*buf;

	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		if (!replace_dollar(&buf, data))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	buf = NULL;
	close(fd);
	return (1);
}

int	here_doc(t_data *data, char *end_file)
{
	int	fd;
	
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(data, fd, end_file))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
