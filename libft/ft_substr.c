/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:48:09 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 16:48:09 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/

char	*ft_substr(char const	*s, unsigned int start, size_t len)
{
	char	*newstring;
	int		i;

	i = 0;
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	newstring = ft_calloc((len + 1), sizeof (char ));
	if (s == NULL || newstring == NULL)
		return (NULL);
	while (start != 0 && ft_strlen(s) + 1 > start && *s != '\0')
	{
		s++;
		start--;
	}
	while (len > 0 && ft_strlen(s) + 1 > start && *s != '\0')
	{
		newstring[i] = *s;
		i++;
		s++;
		len--;
	}
	newstring[i] = '\0';
	return (newstring);
}

/*
int main()
{
	char *s = "tripouille";
	char *substr = ft_substr(s, 0, 42000);

	if (substr != NULL)
	{
		printf("Substring: %s\n", substr);
		free(substr); // Ne pas oublier de libérer la mémoire allouée
	}
	else
	{
		printf("Erreur lors de l'allocation de la sous-chaîne.\n");
	}

	return 0;
}
*/