#include "../../../Includes/minishell.h"

// static void ft_test(t_data *data)
// {
// 	t_env *test;
// 	test = ft_getenv("OLD_PWD", data->env);
		
// 		printf("old_pwd value: %s\n", test->value);
// }
int	update_old_pwd(t_data *data, char *old_pwd)
{
	t_env *OLD_PWD;

	OLD_PWD = ft_getenv("OLDPWD", data->env);
	if (!OLD_PWD)
		return (0);
	else
	{
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

	HOME = ft_getenv("HOME", data->env);
	old_pwd = getcwd(NULL, 0);
	if (!chdir(HOME->value))
	{
		PWD = ft_getenv("PWD", data->env);
		free(PWD->value);
		PWD->value = ft_strdup(getcwd(NULL, 0));
		update_old_pwd(data, old_pwd);
		return (1);
	}
	else
	{
		printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
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
			free(PWD->value);
			PWD->value = ft_strdup(getcwd(NULL, 0));
			update_old_pwd(data, old_pwd);
			return (1);
		}
		else
			printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
		return (0);
	}
}
