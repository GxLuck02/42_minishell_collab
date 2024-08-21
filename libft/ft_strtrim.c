/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:30 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 18:20:30 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
*/
size_t	getstart(char const *string, char const	*set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(string);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, string[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

size_t	getend(char const *string, char const	*set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(string);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, string[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char	*newstring;
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = getstart(s1, set);
	end = getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	newstring = (char *)malloc(sizeof(char) * (end - start + 1));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s1 + start, end - start + 1);
	return (newstring);
}
/*
int main()
{
	char string[] = "Blue, Blue, Blue ,";
	char set[] = ",";

	char *final = ft_strtrim(string, set);
	if (final != NULL)
	{
		printf("%s\n", final);
		free(final); // N'oubliez pas de libérer la mémoire après utilisation.
	}
	else
	{
		printf("Erreur d'allocation de mémoire.\n");
	}

	return 0;
}
*/