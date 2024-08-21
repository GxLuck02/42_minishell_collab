/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:11 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 12:57:03 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <string.h>
#include <stdio.h>
*/

char	*ft_strchr(const char	*string, int searchChar)
{
	while (*string != '\0')
	{
		if (*string == (char)searchChar)
			return ((char *) string);
		string++;
	}
	if (*string == (char)searchChar)
		return ((char *)string);
	return (NULL);
}

/*
int main()
{
    const char *str = "tripouille";
    char c = '\0';

    char *result1 = strchr(str, 1024);
    char *result2 = ft_strchr(str, 1024);

    printf("strchr:\n");
    printf("   Adresse du caractère trouvé : %p\n", (void *)result1);
    printf("   Adresse du caractère nul : %p\n", (void *)c);
    printf("   Différence d'adresses : %ld\n", result1 - str);

    printf("\nft_strchr:\n");
    printf("   Adresse du caractère trouvé : %p\n", (void *)result2);
    printf("   Adresse du caractère nul : %p\n", (void *)c);
    printf("   Différence d'adresses : %ld\n", result2 - str);

    return 0;
}
*/