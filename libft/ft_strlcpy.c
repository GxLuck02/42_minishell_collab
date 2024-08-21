/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:37:41 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/13 15:34:28 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t lenght)
{
	unsigned int	i;

	i = 0;
	if (lenght == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	while (src[i] && lenght - 1 > i)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*
int main()
{
	char src[] = "Hello, World!";
	char dest[20];
	size_t length = 5;

	ft_strlcpy(dest, src, length);

	printf( "dest = %s\n", dest);


	return 0;
}
*/