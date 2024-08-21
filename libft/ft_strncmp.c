/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:03:01 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 13:18:45 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	comp_char(char c1, char c2)
{
	if (c1 != c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	while ((first[i] || second[i]) && i < len && first[i] == second[i])
	{
		i++;
	}
	if (i == len)
		return (0);
	return (comp_char(first[i], second[i]));
}
