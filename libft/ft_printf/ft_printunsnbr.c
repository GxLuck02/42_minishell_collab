/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:08:07 by ttreichl          #+#    #+#             */
/*   Updated: 2023/11/07 17:08:12 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	unbrdigit(unsigned int n)
{
	int				digit;
	unsigned int	tempn;

	tempn = n;
	digit = 1;
	while (n != 0)
	{
		digit++;
		n = n / 10;
	}
	if (tempn != 0)
		digit--;
	return (digit);
}

static char	*transfo(char *dest, unsigned int src, int len)
{
	dest[len] = '\0';
	while (len--)
	{
		*(dest + len) = src % 10 + '0';
		src = src / 10;
	}
	return (dest);
}

char	*ft_uitoa(unsigned int n)
{
	char			*result;
	int				digit;
	unsigned int	num;

	digit = unbrdigit(n);
	num = n;
	result = (char *)malloc((digit + 1) * sizeof(char));
	if (result == 0)
		return (0);
	transfo(result, num, digit);
	return (result);
}

int	ft_printunsnbr(unsigned int c)
{
	int		len;
	char	*string;

	len = 0;
	string = ft_uitoa(c);
	len += ft_printstring(string);
	free(string);
	return (len);
}
