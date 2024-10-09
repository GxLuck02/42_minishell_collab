/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:45:28 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/09 15:28:11 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *word)
{
	int	index;
	int	nbrchar;

	nbrchar = 0;
	index = 0;
	while (word[index] != '\0')
	{
		index++;
		nbrchar++;
	}
	return (nbrchar);
}
