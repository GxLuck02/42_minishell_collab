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
/*
fork
execute la commande ou absolute_path avec execve dans child process

*/

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
	if (!path_array)
		return (NULL);
	while (path_array[i])
	{
		complete_path = ft_strjoin(path_array[i], cmd);
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
verifie si c'est un absolute path;
	si oui execute la commande
	(je dois encore ajouter une condition pour le absolute_path pour envoyer le bon message d'erreure)
recupere le complete_path (path/cmd)
execute la commande
*/
void    make_cmd(t_data *data)
{
	char	*complete_path;
	t_env	*path_var;

	path_var = ft_getenv("PATH", data->env);
	if (!access(data->cmd->cmd_param[0], F_OK | X_OK))
	{
	 	if(!execve(data->cmd->cmd_param[0], data->cmd->cmd_param, data->absolute_path))
			exit(127);
	}
	if (!path_var)
	{
		ft_putstr_fd("xnxX-Minishell-Xx: ", 2);
		ft_putstr_fd(data->cmd->cmd_param[0], 2);
		ft_putstr_fd(" :no such file or directory\n", 2);
		exit(127);
	}
	complete_path = is_path_executable(path_var->value, data->cmd->cmd_param[0]);
	if (!complete_path)
	{
		ft_putstr_fd("xnxX-Minishell-Xx: ", 2);
		ft_putstr_fd(data->cmd->cmd_param[0], 2);
		ft_putstr_fd(" :cmd not found\n", 2);
		exit(127);
	}
	execve(complete_path, data->cmd->cmd_param, data->env_tab);
}

void    handle_cmd(t_data *data)
{
	pid_t pid;
	int	status;
	pid = fork();
    if (pid < 0)
    {
		perror("fork failed");
    	exit(0);
	}
	else if (pid == 0)
	{
		if (data->cmd->outfile == 3)
			dup2(data->cmd->outfile, STDOUT_FILENO);
		if (data->cmd->infile == 3)
			dup2(data->cmd->infile, STDIN_FILENO);
		if (data->cmd->outfile == 4)
			dup2(data->cmd->outfile, STDOUT_FILENO);
		make_cmd(data);
	}
	else
		waitpid(pid, &status, 0);
	return ;
}
/*
boucle sur la liste de commandes
prepare les pipes
envoie la commande
*/
void exec(t_data *data)
{
	int	len_cmd;
	len_cmd = ft_lstsize_circular(data->cmd);
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
<<<<<<< HEAD
=======
	if (data->cmd->skip_cmd == 1)
		return ;
>>>>>>> origin/tmontani
	while (len_cmd)
	{
		int	pipe;

		pipe = len_cmd > 1;
		if (pipe == 0)
		{
<<<<<<< HEAD
=======
			if(is_builtin(data))
				execute_builtin(data);
			else
>>>>>>> origin/tmontani
			handle_cmd(data);
		}
		else
			handle_pipe(data);
		data->cmd = data->cmd->next;
		len_cmd--;
	}
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin); 
	return ;
}
