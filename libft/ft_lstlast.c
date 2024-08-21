/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:09:36 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:37:08 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_liste	*ft_lstlast(t_liste *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}
