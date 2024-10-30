/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:09:50 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/16 18:20:42 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nbrdigit(int n)
{
	size_t	digit;
	int		tempn;

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

static char	*transfo(char	*dest, long int src, size_t	len)
{
	dest[len] = '\0';
	if (src == -2147483648)
	{
		ft_strlcpy(dest, "-2147483648", len + 1);
		return (dest);
	}
	while (len--)
	{
		*(dest + len) = src % 10 + '0';
		src = src / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		digit;
	long int	num;

	digit = nbrdigit(n);
	num = n;
	if (n < 0)
	{
		num *= -1;
		digit++;
	}
	result = (char *)malloc((digit + 1) * sizeof(char));
	if (result == 0)
		return (0);
	transfo(result, num, digit);
	if (n < 0)
		result[0] = '-';
	return (result);
}
