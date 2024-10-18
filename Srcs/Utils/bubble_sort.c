/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:52:52 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/18 17:26:34 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	len_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	equal_check(t_env **env, char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal)
		(*env)->equal = true;
	else
		(*env)->equal = false;
}

void	bubble_sort(char **tab, int len_env)
{
	bool	unsorted;
	char	*tmp;
	int		n;

	unsorted = true;
	tmp = *tab;
	while (unsorted)
	{
		unsorted = false;
		n = 0;
		while (n < len_env - 1)
		{
			if (ft_strcmp(tab[n], tab[n + 1]) > 0)
			{
				tmp = tab[n];
				tab[n] = tab[n + 1];
				tab[n + 1] = tmp;
				unsorted = true;
			}
			n++;
		}
	}
}
