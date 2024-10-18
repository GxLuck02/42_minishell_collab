/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:15:23 by tmontani          #+#    #+#             */
/*   Updated: 2024/10/18 15:39:37 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	update_old_pwd(t_data *data, char *old_pwd_update)
{
	t_env	*old_pwd;

	old_pwd = ft_getenv("OLDPWD", data->env);
	if (!old_pwd)
		return (0);
	else
	{
		if (old_pwd->value)
			free(old_pwd->value);
		old_pwd->value = old_pwd_update;
		return (1);
	}
	return (0);
}

int	cd_no_args(t_data *data)
{
	t_env	*pwd;
	t_env	*home;
	char	*old_pwd;
	char	*new_pwd;

	home = ft_getenv("HOME", data->env);
	old_pwd = getcwd(NULL, 0);
	if (!home || !old_pwd)
	{
		if (!home)
			printf("bash %s: home not set\n", data->cmd->cmd_param[0]);
		return (0);
	}
	if (!chdir(home->value))
	{
		pwd = ft_getenv("PWD", data->env);
		if (pwd)
		{
			free(pwd->value);
			new_pwd = getcwd(NULL, 0);
			pwd->value = ft_strdup(new_pwd);
			free(new_pwd);
		}
		update_old_pwd(data, old_pwd);
		return (1);
	}
	else
	{
		free(old_pwd);
		printf("bash: %s: No such file or directory\n",
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
	t_env	*pwd;
	char	*old_pwd;
	char	*new_pwd;

	if (!data->cmd->cmd_param[1])
	{
		if (!cd_no_args(data))
			return (0);
		else
			return (1);
	}
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (!chdir(data->cmd->cmd_param[1]))
		{
			pwd = ft_getenv("PWD", data->env);
			if (pwd)
			{
				free(pwd->value);
				new_pwd = getcwd(NULL, 0);
				pwd->value = ft_strdup(new_pwd);
				free(new_pwd);
			}
			update_old_pwd(data, old_pwd);
			return (1);
		}
		else
		{
			free(old_pwd);
			printf("bash %s: No such file or directory\n",
				data->cmd->cmd_param[0]);
		}
		return (0);
	}
}
