/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:39:25 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 12:43:09 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
		character = character - 32;
	return (character);
}
/*
int main()
{
    int minuscule;

    minuscule = '!';
    printf("Avant : %c\n", minuscule);
    printf("Apres : %c\n", ft_toupper(minuscule));

    return 0;
}
*/
