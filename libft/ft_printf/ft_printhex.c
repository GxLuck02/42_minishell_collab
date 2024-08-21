/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:16 by ttreichl          #+#    #+#             */
/*   Updated: 2023/11/14 17:37:52 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	len_hex(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_puthex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, format);
		ft_puthex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_printchar((int) num + '0');
		else
		{
			if (format == 'x')
				ft_printchar((int) num - 10 + 'a');
			if (format == 'X')
				ft_printchar((int) num - 10 + 'A');
		}
	}
}

int	ft_printhex(unsigned int c, const char format)
{
	if (c == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		ft_puthex(c, format);
	return (len_hex(c));
}
