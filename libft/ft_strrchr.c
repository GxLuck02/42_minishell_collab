/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:57:41 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 13:01:13 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/

char	*ft_strrchr(const char	*string, int searchChar)
{
	const char	*lastocurrence;

	lastocurrence = 0;
	while (*string != '\0')
	{
		if ((unsigned char)*string == (unsigned char)searchChar)
			lastocurrence = string;
		string++;
	}
	if ((char)searchChar == '\0')
		return ((char *)string);
	return ((char *)lastocurrence);
}

/*
int main()
{
    const char *str = "teste";
    char c = 'e';
    char *result1 = strrchr(str, c);
    char *result2 = ft_strrchr(str, c);

    printf("%c est a la %ld eme position\n", c, result1 - str);
    printf("%c est a la %ld eme position\n", c, result2 - str);
}
*/