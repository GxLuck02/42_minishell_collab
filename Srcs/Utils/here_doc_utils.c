/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:07 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/30 16:41:51 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// int	replace_dollar_heredoc(char **cmd_line, t_data *data)
// {
// 	int			i;
// 	char		*new_str;

// 	i = 0;
// 	new_str = ft_strdup("");
// 	while ((*cmd_line)[i] != '\0')
// 	{
// 		if ((*cmd_line)[i] && !data->sq && (*cmd_line)[i + 1] \
// 			&& (*cmd_line)[i] == '$' && \
// 			((*cmd_line)[i + 1] != '\'') && (*cmd_line)[i + 1] != '"' \
// 			&& (ft_isalpha((*cmd_line)[i + 1]) || \
// 			(*cmd_line)[i + 1] == '?' || (*cmd_line)[i + 1] == '_' \
// 			|| (*cmd_line)[i + 1] == '$') \
// 			&& !replace_dollar_var((*cmd_line), &i, data, &new_str))
// 			return (0);
// 		if ((*cmd_line)[i] && !add_char(&(*cmd_line)[i], &new_str, &i, data))
// 			return (0);
// 	}
// 	free(*cmd_line);
// 	*cmd_line = new_str;
// 	return (1);
// }

void    print_heredoc_error(char *word)
{
    print_error("warning: here-doc delimited by end-of-file (wanted '");
    print_error(word);
    print_error("')\n");
}
