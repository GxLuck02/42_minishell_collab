#include "../../../Includes/minishell.h"
int	cd_no_args(t_data *data)
{
	t_env	*PWD;
	t_env	*OLD_PWD;
	char	*old_pwd;
	t_env	*HOME;

	HOME = ft_getenv("HOME", data->env);
	if (!chdir(HOME->value))
	{
		PWD = ft_getenv("PWD", data->env);
		old_pwd = PWD->value;
		free(PWD->value);
		PWD->value = ft_strdup(getcwd(NULL, 0));
		OLD_PWD = ft_getenv("OLD_PWD", data->env);
		OLD_PWD->value = old_pwd;
		return (1);
	}
	else
	{
		printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
		return (0);
	}
	return (1);
}

/*
1. verifier si le dossier est valide
2. mettre a jour la variable env pwd
3. get_cwd donne le chemin absolu actuel stocker dans cwd
4. 
*/

int ft_cd(t_data *data)
{
	t_env	*PWD;
	t_env	*OLD_PWD;
	char	*old_pwd;

	if(!data->cmd->cmd_param[1])
	{
		puts("cd no args\n");
		if(!cd_no_args(data))
			return (0);
		else
			return (1);
	}
	else
	{
		if (!chdir(data->cmd->cmd_param[1]))
		{
			PWD = ft_getenv("PWD", data->env);
			old_pwd = PWD->value;
			free(PWD->value);
			PWD->value = ft_strdup(getcwd(NULL, 0));
			OLD_PWD = ft_getenv("OLD_PWD", data->env);
			OLD_PWD->value = old_pwd;
			return (1);
		}
		else
		{
			printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
			return (0);
		}
	}
	return (1);
}
