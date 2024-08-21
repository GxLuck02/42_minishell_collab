/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:44:55 by ttreichl          #+#    #+#             */
/*   Updated: 2023/11/14 18:04:52 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	ft_format(va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		length += ft_printstring(va_arg(args, char *));
	else if (format == 'i' || format == 'd')
		length += ft_printnbr(va_arg(args, int));
	else if (format == 'p')
		length += ft_printptr(va_arg(args, unsigned long long));
	else if (format == 'x' || format == 'X')
		length += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == 'u')
		length += ft_printunsnbr(va_arg(args, unsigned int));
	else if (format == '%')
		length += ft_printpercent();
	return (length);
}

int	ft_printf(const char *start, ...)
{
	va_list	args;
	int		length;

	length = 0;
	va_start(args, start);
	while (*start != '\0')
	{
		if (*start == '%')
		{
			length += ft_format(args, (*(++start)));
		}
		else
			length += ft_printchar(*start);
		start++;
	}
	va_end(args);
	return (length);
}
