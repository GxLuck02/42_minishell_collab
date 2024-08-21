/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:17:04 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/13 15:37:29 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

//this function tracks the opening and closing state of quotes in a string.
void	quote_choice(bool *sq, bool *dq, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
	}
	else if (c == '\'' || c == '"')
	{
		if (c == '\'' && *sq && !*dq)
			*sq = false;
		else if (c == '"' && *dq && !*sq)
			*dq = false;
	}
}

//Check if the quotes are open or not
int	open_quote(char *str)
{
	int		index;
	bool	sq;
	bool	dq;

	index = 0;
	sq = false;
	dq = false;
	if (str == NULL || str[index] == '\0')
		return (1);
	while (str[index] != '\0')
	{
		quote_choice(&sq, &dq, str[index]);
		++index;
	}
	if (sq == true || dq == true)
		return (1);
	return (0);
}

//Search a char in a string
int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
