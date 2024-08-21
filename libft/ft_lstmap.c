/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:10:40 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:37:54 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_liste	*ft_lstmap(t_liste *lst, void *(*f)(void *), void (*del)(void *))
{
	t_liste	*newlst;
	t_liste	*startnewlst;

	if (lst == NULL || (*f) == NULL || del == NULL)
		return (0);
	newlst = ft_lstnew(f(lst->content));
	startnewlst = newlst;
	lst = lst->next;
	while (lst != NULL)
	{
		newlst->next = ft_lstnew(f(lst->content));
		if (!newlst->next)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	newlst->next = NULL;
	return (startnewlst);
}
