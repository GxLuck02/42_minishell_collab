/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:31:43 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/24 19:31:43 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char	*string)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*string >= 9 && *string <= 13) || *string == 32)
	{
		string++;
	}
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			sign = -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		result = (result * 10 + (*string - 48));
		string++;
	}
	return (sign * result);
}
