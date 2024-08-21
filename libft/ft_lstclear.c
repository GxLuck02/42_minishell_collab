/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:55:56 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:41:58 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_liste **lst, void (*del)(void*))
{
	t_liste	*current;
	t_liste	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		(del)(current->content);
		free (current);
		current = next;
	}
	*lst = NULL;
}
