/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:49:54 by ttreichl          #+#    #+#             */
/*   Updated: 2023/10/18 12:52:15 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		character = character + 32;
	return (character);
}
/*
int main()
{
    int majuscule;

    majuscule= 'Z';
    printf("Avant : %c\n", majuscule);
    printf("Apres : %c\n", ft_tolower(majuscule));

    return 0;
}
*/
