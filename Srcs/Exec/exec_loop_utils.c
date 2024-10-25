/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:33 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/25 11:25:51 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
void    init_pid_tab(t_data *data, int len_cmd)
{
    data->pid_tab = malloc(sizeof(pid_t) * len_cmd);
    if (data->pid_tab == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

void    fork_fail(t_data *data)
{
    perror("fork failed");
    free(data->pid_tab);
    exit(EXIT_FAILURE);
}

void    handle_child(t_data *data, int len_cmd, int prev_fd, int pipe_fd[], int i)
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

void    handle_parent(t_data *data, int len_cmd,  pid_t pid, int i, int prev_fd, int pipe_fd[])
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

