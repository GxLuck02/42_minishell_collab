/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:21:29 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 13:32:09 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*memb;

	memb = (unsigned char *)memoryBlock;
	while (size > 0)
	{
		if (*memb == (unsigned char)searchedChar)
			return (memb);
		memb++;
		size--;
	}
	return (0);
}
