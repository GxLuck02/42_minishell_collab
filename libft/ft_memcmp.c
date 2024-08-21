/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:36:27 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/24 19:16:29 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_memcmp(const void *str1, const void *str2, size_t size)
{
	size_t	i;

	i = 0;
	while (size > i)
	{
		if (*(unsigned char *)str1 != *(unsigned char *)str2)
			return ((*(unsigned char *)str1) - (*(unsigned char *)str2));
		str1++;
		str2++;
		size--;
	}
	return (0);
}

/*
int main()
{
    char str1[]= "\xff\xaa\xde\xffMACOSX\xff";
    char str2[]= "\xff\xaa\xde\x02";
    size_t size = 8;
    if ((ft_memcmp(str1, str2, size)) > 0)
        printf("Str 1 superieur a str2\n");
    else if ((ft_memcmp(str1, str2, size) < 0))
        printf("str1 est plsu petit que str2\n");
    else
        printf("les %zu octect sont identique\n", size);
    return (0);
}
*/
/*
int main()
{
	char str1[]= "\xff\xaa\xde\xffMACOSX\xff";
	char str2[]= "\xff\xaa\xde\x02";
	size_t size = 8;
	if ((memcmp(str1, str2, size)) > 0)
		printf("Str 1 superieur a str2\n");
	else if ((memcmp(str1, str2, size) < 0))
		printf("str1 est plsu petit que str2\n");
	else
		printf("les %zu octect sont identique\n", size);
	return (0);
}
*/