/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:37:18 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/13 16:45:02 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/
size_t	ft_strlcat(char	*dest, const char	*src, size_t size)
{
	size_t	index1;
	size_t	index2;
	size_t	tempindex;

	index1 = 0;
	index2 = 0;
	while (dest[index1] != '\0')
	{
		index1++;
	}
	tempindex = index1;
	while (index1 < size - 1 && src[index2] != '\0' && size > 0)
	{
		dest[index1] = src[index2];
		index1++;
		index2++;
	}
	dest[index1] = '\0';
	while (src[index2] != '\0')
		index2++;
	if (size < index1)
		return (index2 + size);
	else
		return (tempindex + index2);
}

/*
int main()
{
	char	dest[10]= "ahhgfh";
	char	src[]= "lorem ipsum dolor sit amet";

	printf("Dest : %s\n", dest);
	printf("Source : %s\n", src);
	printf("Nombre caractere copier : %zu\n", ft_strlcat(dest, src, 0));
	printf("New Dest : %s\n", dest);

	return (0);
}
*/