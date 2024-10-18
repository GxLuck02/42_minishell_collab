/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:15:23 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/18 17:19:52 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_and_assign_pwd_value(t_env *current_pwd, char *new_pwd)
{
	if (!current_pwd)
		return ;
	free(current_pwd->value);
	new_pwd = getcwd(NULL, 0);
	current_pwd->value = ft_strdup(new_pwd);
	free(new_pwd);
}

int	update_old_pwd(t_data *data, char *old_pwd)
{
	t_env	*old_pwd_env;

	old_pwd_env = ft_getenv("OLDPWD", data->env);
	if (!old_pwd_env)
		return (0);
	else
	{
		if (old_pwd_env->value)
			free(old_pwd_env->value);
		old_pwd_env->value = old_pwd;
		return (1);
	}
	return (0);
}

static int	get_env_values(t_data *data, t_env **home_value, char **old_pwd)
{
	*home_value = ft_getenv("HOME", data->env);
	*old_pwd = getcwd(NULL, 0);
	if (!*home_value || !*old_pwd)
	{
		if (!*home_value)
			printf("bash %s: HOME not set\n", \
				data->cmd->cmd_param[0]);
		return (0);
	}
	return (1);
}

int	cd_no_args(t_data *data)
{
	t_env	*pwd_value;
	t_env	*home_value;
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = NULL;
	if (!get_env_values(data, &home_value, &old_pwd))
		return (0);
	if (!chdir(home_value->value))
	{
		pwd_value = ft_getenv("PWD", data->env);
		free_and_assign_pwd_value(pwd_value, new_pwd);
		update_old_pwd(data, old_pwd);
		return (1);
	}
	else
	{
		free(old_pwd);
		printf("bash: %s: No such file or directory\n", \
			data->cmd->cmd_param[0]);
		return (0);
	}
}
/*
 verifier si cd est seule ou avec arguments
 si seule appelle cd_no_args
essaye de changer le repertoire courant avec chdir
si ca fonctionne
	update la variable PWD
	update la variable OLDPWD
si ca fonctionne pas c'est que l'input est faux
	return (message d'erreure);
*/

int	ft_cd(t_data *data)
{
	t_env	*current_pwd;
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = NULL;
	if (!data->cmd->cmd_param[1])
	{
		if (!cd_no_args(data))
			return (0);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!chdir(data->cmd->cmd_param[1]))
	{
		current_pwd = ft_getenv("PWD", data->env);
		free_and_assign_pwd_value(current_pwd, new_pwd);
		update_old_pwd(data, old_pwd);
		return (1);
	}
	else
	{
		free(old_pwd);
		printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
	}
	return (0);
}
