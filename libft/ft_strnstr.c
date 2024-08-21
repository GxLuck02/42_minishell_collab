/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:41:16 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 13:55:36 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *string, const char *needle, size_t len)
{
	const char	*temp_string;
	const char	*temp_needle;
	size_t		temp_len;

	if ((len == 0 && ft_strlen(needle) == 0) || *needle == '\0')
		return ((char *)string);
	while (*string != '\0' && len > 0)
	{
		temp_string = string;
		temp_needle = needle;
		temp_len = len;
		while (*temp_string == *temp_needle && *temp_needle != '\0'
			&& temp_len > 0)
		{
			temp_string++;
			temp_needle++;
			temp_len--;
		}
		if (*temp_needle == '\0')
			return ((char *)string);
		string++;
		len--;
	}
	return (0);
}
