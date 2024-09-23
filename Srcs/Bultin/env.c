/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:01:49 by ttreichl          #+#    #+#             */
/*   Updated: 2024/09/23 17:24:49 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
