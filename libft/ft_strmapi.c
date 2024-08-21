/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:07:07 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/23 16:07:07 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstring;
	unsigned int	index;

	index = 0;
	newstring = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (newstring == 0)
		return (0);
	while (s[index] != '\0')
	{
		newstring[index] = f(index, s[index]);
		index++;
	}
	newstring[index] = '\0';
	return (newstring);
}
/*
char	my_fonction(unsigned int index, char character)
{
	printf ("index = %d et le cractere %c\n", index, character);
	character = character + 32;
	return (character);
}

int main ()
{
	char	string[] = "ASDFGHJ";
	char	*newstring;

	newstring = ft_strmapi(string, my_fonction);
	printf("%s\n", newstring);

	free(newstring);
	return (0);
}
 */