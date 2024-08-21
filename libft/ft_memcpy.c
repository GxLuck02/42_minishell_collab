/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:35:48 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:41:39 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t nbroct)
{
	int							index;
	char		*restrict		chardest;
	const char	*restrict		charsrc;

	chardest = dest;
	charsrc = src;
	index = 0;
	if (dest == NULL && src == NULL)
	{
		return (NULL);
	}
	while (nbroct != 0)
	{
		chardest[index] = charsrc[index];
		index++;
		nbroct--;
	}
	return (dest);
}
/*
int main()
{
	char *src_null = NULL;
	char dest_null[10];
	char *result = ft_memcpy(NULL, NULL, 17);
	if (result == NULL) {
		printf("Test 3: Copie depuis NULL réussie.\n");
	} else {
		printf("Test 3: Erreur 
		La copie depuis NULL aurait dû renvoyer NULL.\n");
	}
	return (0);
}
*/