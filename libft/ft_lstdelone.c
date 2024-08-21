/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:21:19 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:37:28 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_liste *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		if (del != NULL && lst->content != NULL)
			(del)(lst->content);
		free (lst);
		lst = NULL;
	}
}
