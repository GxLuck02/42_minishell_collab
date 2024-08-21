/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:01:32 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:38:19 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_liste *lst)
{
	int	result;

	result = 0;
	while (lst)
	{
		lst = lst -> next;
		result++;
	}
	return (result);
}
