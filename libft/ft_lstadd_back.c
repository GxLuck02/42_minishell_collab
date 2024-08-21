/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:13:40 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:34:28 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_liste **lst, t_liste *new)
{
	t_liste	*last;

	last = ft_lstlast(*lst);
	if (last == NULL)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}
