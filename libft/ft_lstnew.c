/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:22:38 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:38:05 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_liste	*ft_lstnew(void *content)
{
	t_liste	*new;

	new = (t_liste *)malloc (sizeof (*new));
	if (new == 0)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
