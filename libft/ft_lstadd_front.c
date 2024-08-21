/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:01:26 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:40:52 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_liste **lst, t_liste *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int main(void)
{
	// Création d'un nouvel élément de liste
	char	username1[]="GxLuck"; 
	// Exemple de donnée, peut être n'importe quel type
	t_list *player = ft_lstnew(&username1);
	char	username2[]="Kjolo";
	t_list *player2 = ft_lstnew(&username2);
	ft_lstadd_front(&player, player2);

	if (player != NULL)
	{
		t_list *current = player; // Pointeur pour parcourir la liste

		while (current != NULL)
		{
			printf("Nom du joueur : %s\n", (char *)current->content);
			current = current->next;
		}

	}
	else
	{
		printf("Erreur lors de la création de l'élément.\n");
	}

	return 0;
}
*/