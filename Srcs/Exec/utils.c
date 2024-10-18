/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:55:15 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/18 16:21:05 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_free(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
}
/*
malloc une char * 
remplit cette chaine avec len caractere de la chaine passee en parametre
*/

static char	*fill_word(const char *str, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * (len + 2));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/* rempli le tableau avec les paths et
 ajoute un '/' pour pouvoir ensuite join la commande
 retourne un double tableau avec tous les paths suivi de '/'
 */
static char	**fill_array(const char *path, char sep, char **array, size_t word)
{
	size_t	len;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	while (a < word)
	{
		len = 0;
		while (path[i] == sep)
			i++;
		while (path[i + len] != sep && path[i + len])
			len++;
		array[a] = fill_word(path + i, len);
		array[a][len] = '/';
		array[a][len + 1] = '\0';
		i = i + len;
		a++;
	}
	array[a] = NULL;
	return (array);
}

//compte le nb de mot dans une chaine
static size_t	ft_count_word(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

/*split la variable path et renvoie un double tableau 
avec chaque path et '/' a la fin de chaque path */
char	**ft_split_path(char const *path, char c)
{
	size_t	word_count;
	char	**array;

	word_count = ft_count_word(path, c);
	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_array(path, c, array, word_count))
	{
		ft_free(array, word_count);
		return (NULL);
	}
	return (array);
}
