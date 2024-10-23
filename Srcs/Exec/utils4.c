/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:07:13 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/23 15:46:53 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void    add_pid_tab(t_data *data, pid_t pid)
{
    static int i = 0;
    
    if(!data->pid_tab[i])
    {
        data->pid_tab[i] = pid;
        data->pid_index = i;
        i++;
    }
    else
    {
        data->pid_tab[i] = pid;
        data->pid_index = i;
        i++;
    }
}

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