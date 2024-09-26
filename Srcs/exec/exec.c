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
split le path et recupere un tableau avec chaque path
verifie avec access si chaque path est executable
si oui renvoie le path executable sinon renvoie NULL
*/
char *is_path_executable(char *path, char *cmd)
{
	char	**path_array;
	int		i;
	char	*complete_path;

	i = 0;
	path_array = ft_split_path(path, ':');
	ft_print_array(path_array);
	if (!path_array)
		return (NULL);
	while (path_array[i])
	{
		complete_path = ft_strjoin(path_array[i], cmd);
		ft_printf("complete_path : %s\n", complete_path);
		if (!complete_path)
		{
			free(complete_path);
			return (NULL);
		}
		if (!access(complete_path, F_OK | X_OK))
			return (complete_path);
		i++;
	}
	return (NULL);
}
/*
recupere la variable path
verifie si le path est executable
si non cmd not found return ;
si oui execute la commande
*/
void    handle_cmd(t_data *data)
{
	char	*complete_path;
	t_env	*path_var;
	path_var = ft_getenv("PATH", data->env);
	if (!path_var)
	{
		perror("variable path not found\n");
		return ;
	}
	complete_path = is_path_executable(path_var->value, data->cmd->cmd_param[0]);
	if (!complete_path)
		perror("cmd not found\n");
	//printf(" voici le path complet: %s\n\n", complete_path);
	//execute_cmd(complete_path, data);
}
/*
envoie la commande
*/
void exec(t_data *data)
{	
	handle_cmd(data);
}
