/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:52:52 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/02 13:44:22 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
