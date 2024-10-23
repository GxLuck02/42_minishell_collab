/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:23 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/23 17:02:22 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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

	i = -1;
	path_array = ft_split_path(path, ':');
	if (!path_array)
		return (NULL);
	while (path_array[++i])
	{
		complete_path = ft_strjoin(path_array[i], cmd);
		if (!complete_path)
		{
			free_table(path_array);
			return (NULL);
		}
		if (!access(complete_path, F_OK | X_OK))
		{
			free_table(path_array);
			return (complete_path);
		}
		free(complete_path);
	}
	free_table(path_array);
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

	if (!inside_pipe)
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
		ft_putstr_fd("xX-Minishell-Xx: ", 2);
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
	int	saved_stdout;
	int	has_pipe;
	int	temp_len;
	int pipe_fd[2];
	
	len_cmd = ft_lstsize_circular(data->cmd);
	temp_len = len_cmd;
	data->pid_tab = malloc(sizeof(pid_t) * (len_cmd + 1));
    if (data->pid_tab == NULL)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
	}
	for (int i = 0; i < len_cmd; i++) {
        data->pid_tab[i] = -1;
	}
	 data->pid_tab[len_cmd] = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	
	if (data->cmd->skip_cmd == 1)
		return ;
	if (len_cmd == 1)
	{
		if (is_builtin(data))
		{
			execute_builtin(data);
			reset_stdin(saved_stdin);
			reset_stdout(saved_stdout);
			return ;
		}
		else if (!is_builtin(data))
		{
			handle_cmd(data);
			reset_stdin(saved_stdin);
			reset_stdout(saved_stdout);
			return;
		}
		return ;
	}
	while (temp_len)
	{
		puts("pipe cmd\n");
		has_pipe = len_cmd > 1;
		if (has_pipe)
		{
			pipe(pipe_fd);
			add_pid_tab(data, fork());
			if (data->pid_tab[data->pid_index] == -1)
			{
				ft_putstr_fd("pipe Error\n", 2);
				free_all(data, 0, 0);
				exit(EXIT_FAILURE);
			}
			if(data->pid_tab[data->pid_index] == 0)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				if (is_builtin(data))
					execute_builtin(data);
				else
					make_cmd(data, 1);
				close(pipe_fd[1]);
			}
			temp_len--;
			if (temp_len == 0)
				wait_all(data);
				dup2(data->cmd->next->infile, STDIN_FILENO);
			}
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(data->cmd->outfile);
	reset_stdout(saved_stdout);
	free(data->pid_tab);
	return ;
	
}

