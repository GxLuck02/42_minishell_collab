/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:04:13 by ttreichl          #+#    #+#             */
/*   Updated: 2023/11/06 17:15:53 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printnbr(int num)
{
	int		length;
	char	*stringnbr;

	stringnbr = ft_itoa(num);
	length = ft_printstring(stringnbr);
	free (stringnbr);
	return (length);
}
