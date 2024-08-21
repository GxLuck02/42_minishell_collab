/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:48:11 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/23 20:48:11 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	a;

	a = '\n';
	write(fd, s, ft_strlen(s));
	write(fd, &a, 1);
}

/*
int	main()
{
	int fd = 1;

	char message[] = "Bonjour, monde !";
	ft_putendl_fd(message, fd);
	printf("salut");
	return 0;
}
*/
