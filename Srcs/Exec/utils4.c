/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:07:13 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/22 16:42:49 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"


void    wait_all(t_data *data)
{
    int i;

    i = 0;
    while (data->pid_tab[i])
    {
        waitpid(data->pid_tab[i], NULL, 0);
        i++;
    }
}