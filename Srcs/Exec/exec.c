/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:23 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/24 18:49:47 by tmontani         ###   ########.fr       */
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
void exec(t_data *data)
{
    int len_cmd = ft_lstsize_circular(data->cmd);
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid;

    if (len_cmd == 0) return;
    data->pid_tab = malloc(sizeof(pid_t) * len_cmd);
    if (data->pid_tab == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < len_cmd; i++)
    {
        if (i < len_cmd - 1 && pipe(pipe_fd) == -1)
        {
            perror("pipe");
            free(data->pid_tab);
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            free(data->pid_tab);
            exit(EXIT_FAILURE);
		}
        if (pid == 0) // Processus enfant
        {
             set_redir(data); // Gérer les redirections si nécessaire

            // Si on est pas dans le premier processus, rediriger stdin vers le pipe précédent
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < len_cmd - 1)
            {
				puts("here\n");
                close(pipe_fd[0]);  
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
			if (is_builtin(data))
			{	
				execute_builtin(data);
				exit(0);
			}
			else
            	make_cmd(data, len_cmd > 1); // Exécuter la commande avec pipes si nécessaire
        }
        else // Processus parent
        {
            data->pid_tab[i] = pid;  // Sauvegarder le PID du processus enfant

            if (prev_fd != -1)
                close(prev_fd); // Fermer l'extrémité précédente du pipe

            if (i < len_cmd - 1)
            {
                close(pipe_fd[1]);   // Fermer l'extrémité d'écriture du pipe
                prev_fd = pipe_fd[0]; // Sauvegarder l'extrémité de lecture pour la prochaine commande
            }
        }
        data->cmd = data->cmd->next; // Avancer vers la commande suivante
    }
	wait_all(data, len_cmd);
	close(STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    free(data->pid_tab);
}


