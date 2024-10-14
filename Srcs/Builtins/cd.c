#include "../../Includes/minishell.h"

int	update_old_pwd(t_data *data, char *old_pwd)
{
	t_env *OLD_PWD;

	OLD_PWD = ft_getenv("OLDPWD", data->env);
	if (!OLD_PWD)
		return (0);
	else
	{
		if (OLD_PWD->value)
			free(OLD_PWD->value);
		OLD_PWD->value = old_pwd;
		return (1);
	}
	return (0);
}
int	cd_no_args(t_data *data)
{
	t_env	*PWD;
	t_env	*HOME;
	char	*old_pwd;
	char	*new_pwd;

	HOME = ft_getenv("HOME", data->env);
	old_pwd = getcwd(NULL, 0);  // Alloue la chaîne du répertoire actuel
	if (!HOME || !old_pwd)
	{	
		if (!HOME)
			printf("bash %s: HOME not set\n", data->cmd->cmd_param[0]);
		return (0);
	}
	if (!chdir(HOME->value))  // Si chdir réussit
	{
		PWD = ft_getenv("PWD", data->env);
		if (PWD)
		{
			free(PWD->value);  // Libère l'ancienne valeur de PWD
			new_pwd = getcwd(NULL, 0);  // Alloue la nouvelle chaîne pour PWD
			PWD->value = ft_strdup(new_pwd);  // Duplique la nouvelle valeur dans PWD
			free(new_pwd);  // Libère la chaîne retournée par getcwd
		}
		update_old_pwd(data, old_pwd);  // Met à jour OLDPWD avec l'ancienne valeur
		return (1);
	}
	else
	{
		free(old_pwd);
		printf("bash: %s: No such file or directory\n", data->cmd->cmd_param[0]);
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

int ft_cd(t_data *data)
{
	t_env	*PWD;
	char	*old_pwd;
	char	*new_pwd;

	if(!data->cmd->cmd_param[1])
	{
		if(!cd_no_args(data))
			return (0);
		else
			return (1);
	}
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (!chdir(data->cmd->cmd_param[1]))
		{
			PWD = ft_getenv("PWD", data->env);
			if (PWD)
			{
				free(PWD->value);
				new_pwd = getcwd(NULL, 0);
				PWD->value = ft_strdup(new_pwd);
				free(new_pwd);
			}
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
}
