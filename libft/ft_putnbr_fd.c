/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:56:03 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/09 15:34:24 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*string;

	if (n == -2147483648)
		string = "-2147483648";
	else
		string = ft_itoa(n);
	write(fd, string, ft_strlen(string));
	if (n != INT_MIN)
		free(string);
}
