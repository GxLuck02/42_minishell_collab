/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:01:49 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/07 18:00:56 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

int	env(t_env *const env, char **cmd_param)
{
	t_env const	*curr;

	if (cmd_param[1] != 0)
	{
		print_error("Error: env to many argument\n");
		return (123);
	}
	curr = env;
	while (curr)
	{
		if (!curr->key || !curr->value)
		{
			curr = curr->next;
			continue ;
		}
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}