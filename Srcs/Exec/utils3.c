/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:34:29 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/17 21:41:32 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

//fonctionne comme getenv sur la liste chainee
// renvoie le noeud de la liste qui correspond a la variable demandee
t_env	*ft_getenv(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

//reset stdin qui a pu etre change lors de l'execution
void	reset_stdin(int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO),
	close(saved_stdin);
}

void	reset_stdout(int saved_stdout)
{
	dup2(saved_stdout, STDOUT_FILENO),
	close(saved_stdout);
}

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
