/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:56:54 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/06 07:59:13 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*
 * malloc_s - Alloue la mémoire nécessaire pour découper une chaîne au format "KEY=VALUE"
 *            en deux parties : une chaîne pour la clé (avant le '=') et une autre pour
 *            la valeur (après le '=').
 *
 * @s:       Un triple pointeur vers un tableau de chaînes de caractères qui contiendra
 *           les deux chaînes (clé et valeur).
 */
int	malloc_s(char ***s, char *env_str)
{
	(*s) = (char **)malloc(sizeof(char *) * 3);
	if (!(*s))
		return (0);
	(*s)[0] = (char *)malloc(sizeof(char) * (ft_caract(env_str, '=') + 1));
	(*s)[1] = (char *)malloc(sizeof(char) * ((ft_strlen(env_str) - \
				ft_caract(env_str, '=')) + 1));
	if (!(*s)[0] || !(*s)[1])
	{
		if ((*s)[0])
			free((*s)[0]);
		if ((*s)[1])
			free((*s)[1]);
		free(*s);
		return (0);
	}
	(*s)[2] = NULL;
	return (1);
}

/*
 * ft_caract - Compte le nombre de caractères dans une chaîne jusqu'à
 *             rencontrer un caractère donné ou la fin de la chaîne.
 */
int		ft_caract(char *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

/*
 * ft_envsplit - Sépare une chaîne de caractères au format "KEY=VALUE" en deux parties :
 *               la clé (avant le '=') et la valeur (après le '=').
 */
char	**ft_envsplit(char *env_str)
{
	char	**s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!malloc_s(&s, env_str))
		return (NULL);
	while (env_str[++i] && env_str[i] != '=')
		s[0][i] = env_str[i];
	s[0][i] = '\0';
	while (env_str[++i])
		s[1][++j] = env_str[i];
	s[1][j + 1] = '\0';
	return (s);
}
