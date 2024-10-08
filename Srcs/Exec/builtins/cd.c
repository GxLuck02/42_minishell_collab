#include "../../../Includes/minishell.h"

/*
1. verifier si le dossier est valide
2. mettre a jour la variable env pwd
3. get_cwd donne le chemin absolu actuel stocker dans cwd
4. 
*/

int ft_cd(t_data *data)
{

	t_env *HOME;
	t_env *PWD;
	char *old_pwd;
	t_env	*OLD_PWD;

	HOME = NULL;
	if (!data->cmd->cmd_param[1])
	{
		puts("first if\n");
		HOME = ft_getenv("HOME", data->env);
		if (!HOME)
		{
			ft_putstr_fd("HOME not set", 2);
			return (0);
		}
		else
			old_pwd = getcwd(NULL, 0);
			if(!chdir(HOME->value))
			{
				PWD = ft_getenv("PWD", data->env);
				free(PWD->value);
				PWD->value = ft_strdup(getcwd(NULL, 0));
				OLD_PWD = ft_getenv("OLD_PWD", data->env);
				OLD_PWD->value = old_pwd;
				free(old_pwd);
				return (1);
			}
			else
			{
				free(old_pwd);
				printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
				return (0);
			}

	}
	else if (data->cmd->cmd_param[1])
	{
		puts("inside second if\n");
		old_pwd = getcwd(NULL, 0);
		if (!chdir(data->cmd->cmd_param[1]))
		{
			PWD = ft_getenv("PWD", data->env);
			free(PWD->value);
			PWD->value = ft_strdup(getcwd(NULL, 0));
			puts("yeyeyeyeyey\n");
			OLD_PWD = ft_getenv("OLD_PWD", data->env);
			OLD_PWD->value = old_pwd;
			free(old_pwd);
			puts("yeyeyeyeyey\n");
			return (1);
		}
		else
		{
			free(old_pwd);
			printf("bash %s: No such file or directory\n", data->cmd->cmd_param[0]);
			return (0);
		}
	}
	return (1);
}