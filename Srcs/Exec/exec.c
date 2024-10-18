/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:23 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/18 15:38:16 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

//fonctionne comme getenv sur la liste chainee
// renvoie le noeud de la liste qui correspond a la variable demandee
t_env	*ft_getenv(char *var, t_env *env)
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
char	*is_path_executable(char *path, char *cmd)
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
(je dois encore ajouter une condition pour
 le absolute_path pour envoyer le bon message d'erreure)
recupere le complete_path (path/cmd)
execute la commande
*/
void	make_cmd(t_data *data, int inside_pipe)
{
	char	*complete_path;
	t_env	*path_var;

	if (inside_pipe)
		set_redir(data);
	path_var = ft_getenv("PATH", data->env);
	if (!access(data->cmd->cmd_param[0], F_OK | X_OK))
	{
		if (!execve(data->cmd->cmd_param[0],
				data->cmd->cmd_param, data->absolute_path))
			exit(127);
	}
	if (!path_var)
		error_path_var(data);
	complete_path = is_path_executable(path_var->value,
			data->cmd->cmd_param[0]);
	if (!complete_path)
	{
		ft_putstr_fd("xnxX-Minishell-Xx: ", 2);
		ft_putstr_fd(data->cmd->cmd_param[0], 2);
		ft_putstr_fd(" :cmd not found\n", 2);
		exit(127);
	}
	execve(complete_path, data->cmd->cmd_param, data->env_tab);
}

static int	return_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

void	handle_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(0);
	}
	else if (pid == 0)
	{
		set_redir(data);
		make_cmd(data, 0);
	}
	else
		data->exit_code = return_parent_process(pid);
	return ;
}

/*
boucle sur la liste de commandes
prepare les pipes
envoie la commande
*/
void	exec(t_data *data)
{
	int	len_cmd;
	int	saved_stdin;
	int	pipe;

	len_cmd = ft_lstsize_circular(data->cmd);
	saved_stdin = dup(STDIN_FILENO);
	if (data->cmd->skip_cmd == 1)
		return ;
	while (len_cmd)
	{
		pipe = len_cmd > 1;
		if (pipe == 0)
		{
			if (is_builtin(data))
				execute_builtin(data);
			else
				handle_cmd(data);
		}
		else
			execute_pipe(data);
		data->cmd = data->cmd->next;
		len_cmd--;
	}
	reset_stdin(saved_stdin);
	return ;
}
