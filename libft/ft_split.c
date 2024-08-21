/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:05:19 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/20 14:18:09 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

#include <stdio.h>

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

static char	**newstrings(char const *s, char c, char **dest, int nbrwords)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = -1;
	while (++j < nbrwords)
	{
		while (s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		dest[j] = ft_substr(s, i, size);
		if (!dest[j])
		{
			ft_free(dest, j);
			return (NULL);
		}
		i += size;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**strs;

	word = ft_count_word(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (newstrings(s, c, strs, word) == NULL)
	{
		ft_free(strs, word);
		return (NULL);
	}
	return (strs);
}

/*
int	main() {
	char const input_string[] = "      split       this for   me  !";

	char **result = ft_split(input_string, ' ');

	if (result) {
		for (int i = 0; result[i] != NULL; i++) {
			printf("Element %d: %s\n", i, result[i]);
			free(result[i]);
		}
		free(result);
	} else
		printf("Erreur d'allocation mémoire.\n");

	return (0);
}
*/