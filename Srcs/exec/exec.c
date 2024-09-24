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
/*recupere le path et le nom de la commande
split le path et join la commande
verifie avec access si chaque path est executable
si oui renvoie le path executable sinon renvoie NULL
*/
char *is_path_executable(char *path, char *cmd)
{
	char	**path_array;
	(void)cmd;

	path_array = ft_split_path(path, ':');


	return (NULL);
}
/*
recupere la varible path
verifie si le path est executable avec access
si oui appelle execute commande si non renvoie cmd not found
*/
void    handle_cmd(t_data *data)
{
	t_env	*path_var;
	path_var = ft_getenv("PATH", data->env);
	printf("path_variable: %s\n\n", path_var->value);
	if (!path_var)
	{
		perror("variable path not found\n");
		return ;
	}
	is_path_executable(path_var->value, data->cmd->cmd_param[0]);

}
/*
envoie la commande
*/
void exec(t_data *data)
{	
	printf("inside exec\n");
	handle_cmd(data);
}
