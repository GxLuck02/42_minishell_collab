/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:59 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/23 15:11:25 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	check_for_first_token(t_token *tmp)
{
	if (!ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<") ||
        !ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<"))
    {
        // S'assurer qu'il y a un token suivant après une redirection
        if (!tmp->next || (ft_strcmp(tmp->next->str, ">") == 0 || ft_strcmp(tmp->next->str, "<") == 0 ||
            ft_strcmp(tmp->next->str, ">>") == 0 || ft_strcmp(tmp->next->str, "<<") == 0))
        {
            printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
            return (0);
         }
    }
        // Vérifier pour les combinaisons invalides
       if (ft_strncmp(tmp->str, ">", 1) == 0 || ft_strncmp(tmp->str, "<", 1) == 0)
        {
            // Si le token est un mauvais format de redirection, comme >>> ou <<<<<
            if (ft_strlen(tmp->str) > 2 || (!ft_strcmp(tmp->str, "<>") || !ft_strcmp(tmp->str, "><")))
            {
                printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
                return (1);
            }
        }
	return (1);
}

int	check_syntax(t_data *data)
{
    t_token *tmp;

    tmp = data->token;
	if (!check_for_first_token(tmp))
		return (0);
	tmp = tmp->next;
    while (tmp != data->token)
    {
        // Vérifier la validité des redirections simples (>, <, >>, <<)
        if (!ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<") ||
            !ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<"))
        {
            // S'assurer qu'il y a un token suivant après une redirection
            if (!tmp->next || (ft_strcmp(tmp->next->str, ">") == 0 || ft_strcmp(tmp->next->str, "<") == 0 ||
                ft_strcmp(tmp->next->str, ">>") == 0 || ft_strcmp(tmp->next->str, "<<") == 0))
            {
                printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
                return (0);
            }
        }
        // Vérifier pour les combinaisons invalides
        if (ft_strncmp(tmp->str, ">", 1) == 0 || ft_strncmp(tmp->str, "<", 1) == 0)
        {
            // Si le token est un mauvais format de redirection, comme >>> ou <<<<<
            if (ft_strlen(tmp->str) > 2 || (!ft_strcmp(tmp->str, "<>") || !ft_strcmp(tmp->str, "><")))
            {
                printf("bash: syntax error near unexpected token `%s'\n", tmp->str);
                return (1);
            }
        }
        tmp = tmp->next;
    }
    return (1);
}
