/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:05:22 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 15:11:39 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nbrelement, size_t elementsize)
{
	void	*tableau_malloc;

	tableau_malloc = (void *)malloc(nbrelement * elementsize);
	if (tableau_malloc == 0)
		return (0);
	ft_bzero(tableau_malloc, nbrelement * elementsize);
	return (tableau_malloc);
}
