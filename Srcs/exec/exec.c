#include "../../Includes/minishell.h"

//fonctionne comme getenv sur la liste chainee
// renvoie le noeud de la liste qui correspond a la variable demandee
t_env  *ft_getenv(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

//si oui execute la commande avec execve
/*void    execute_cmd(t_data *data)
{

}*/

/*char *is_path_executable(char *path, char *cmd)
{
	
}*/
/*
recupere la varible path
verifie si le path est executable avec access
si oui appelle execute commande si non renvoie cmd not found
*/
void    handle_cmd(t_data *data)
{
	t_env	*path_var;
	path_var = ft_getenv("PATH", data->env);
	if (!path_var)
	{
		perror("variable path not found\n");
		return ;
	}
	//is_path_executable(path_var->value, data->cmd->cmd_param[0]);

}
/*
envoie la commande
*/
void exec(t_data *data)
{
	ft_printf("heeeeeeeeeeere\n");
	fflush(stdout);
	handle_cmd(data);
}
