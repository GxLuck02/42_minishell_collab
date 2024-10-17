/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:34:29 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/16 12:59:28 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
// renvoie une erreure si la variable path n'est pas trouvee dans l'env
void	error_path_var(t_data *data)
{
	ft_putstr_fd("xnxX-Minishell-Xx: ", 2);
	ft_putstr_fd(data->cmd->cmd_param[0], 2);
	ft_putstr_fd(" :no such file or directory\n", 2);
	exit(127);
}

void	ft_print_array(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		printf("%s ", array[j]);
		j++;
	}
}
