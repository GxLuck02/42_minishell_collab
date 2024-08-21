/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 02:03:00 by ttreichl          #+#    #+#             */
/*   Updated: 2024/05/23 02:05:26 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strstr(const char *x, const char *y)
{
	size_t	n;

	n = ft_strlen(y);
	while (*x)
	{
		if (!ft_memcmp(x, y, n))
			return (x);
		x++;
	}
	return (0);
}
