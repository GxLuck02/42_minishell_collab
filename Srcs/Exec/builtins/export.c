/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:41 by ttreichl          #+#    #+#             */
<<<<<<<< HEAD:Srcs/Builtins/export.c
/*   Updated: 2024/10/09 15:32:18 by ttreichl         ###   ########.fr       */
========
/*   Updated: 2024/10/07 20:07:19 by tmontani         ###   ########.fr       */
>>>>>>>> origin/tmontani:Srcs/Exec/builtins/export.c
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	invalid_var(char *var)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': not a valide identifier", STDERR_FILENO);
}

int	set_export_var(t_env **env, char *str)
{
	t_env	*new_node;
	char	**var;
	bool	have_equal;
	
	(void)len_key;
	have_equal = false;
	new_node = (t_env *)malloc(sizeof (t_env));
	if (ft_strchr(str, '=') != NULL)
		have_equal = true;
	var = ft_envsplit(str);
	key_var_to_node(var, &new_node);
	free_var(var);
	if (!new_node)
		return (0);
	if (var_already_exist(*env, new_node->key) == true)
	{
		if (have_equal == true)
			change_value(env, new_node);
	}
	else
		add_node_env(env, new_node);
	return (1);
}

int	is_valid_var(char *var)
{
	if (!var || !*var)
		return (0);
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (0);
		var++;
	}
	return (1);
}

int	export_no_args(t_env *env)
{
	char	**new_tab;
	int		i;
	
	if (!env)
		return (0);
	i = 0;
	new_tab = creat_table(env);
	bubble_sort(new_tab, env_lenthg(env));
	if (!new_tab)
		return (0);
	while (new_tab[i] != NULL)
	{
		printf("declare -x ");
		printf("%s\n",new_tab[i]);
		free(new_tab[i]);
		i++;
	}
	free(new_tab);
	return (1);
}

int	export(t_env **env, char **args)
{
	int	i;
	
	i = 1;
	if (!args[1])
		return (export_no_args(*env));
	else
	{
		while (args[i] != NULL)
		{
			if (!is_valid_var(args[i]))
			{	
				invalid_var(args[i]);
				return (0);
			}
			else if (!set_export_var(env, args[i]))
				return(0);
			i++;
		}
	}
	return (1);
}
