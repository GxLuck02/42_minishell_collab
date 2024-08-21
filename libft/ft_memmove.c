/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:43:40 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 15:17:04 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/
void	*ft_memmove(void *dest, const void *src, size_t nbroct)
{
	size_t	index;

	if (!dest && !src)
		return (NULL);
	dest = (char *)dest;
	src = (char *)src;
	index = 0;
	if (src < dest && dest < src + nbroct)
	{
		while (nbroct > 0)
		{
			((char *)dest)[nbroct - 1] = ((char *)src)[nbroct - 1];
			nbroct--;
		}
	}
	else
	{
		while (nbroct > index)
		{
			((char *)dest)[index] = ((char *)src)[index];
			index++;
		}
	}
	return (dest);
}

/*
int main()
{
	char src[]= "lorem ipsum dolor sit amet";
	char *dest;

	dest = src + 1;
	ft_memmove(NULL, src, 5);
	printf ("%s\n", dest);

	return (0);
}
*/