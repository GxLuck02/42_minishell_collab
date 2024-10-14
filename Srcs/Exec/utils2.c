#include "../../Includes/minishell.h"
// fais les redirections
void	set_redir(t_data *data)
{
	if (data->cmd->infile == 3)
		dup2(data->cmd->infile, STDIN_FILENO);
	if (data->cmd->outfile == 3)
		dup2(data->cmd->outfile, STDOUT_FILENO);
	if (data->cmd->outfile == 4)
		dup2(data->cmd->outfile, STDOUT_FILENO);
	return ;
}

/*
calcule la longueur de la liste circulaire cmd
*/
int	ft_lstsize_circular(t_cmd *cmd)
{
	t_cmd	*temp;
	int		len;

	len = 1;
	temp = cmd;
	if (!cmd)
		return (0);
	temp = temp->next;
	while (temp != cmd)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

/* fais les redirections necessaires et execute le builtin
*/
int	execute_builtin(t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	set_redir(data);
	if (!ft_strcmp(data->cmd->cmd_param[0], "pwd") || !ft_strcmp(data->cmd->cmd_param[0], "PWD"))
		ft_pwd();
	if (!ft_strcmp(data->cmd->cmd_param[0], "echo") || !ft_strcmp(data->cmd->cmd_param[0], "ECHO"))
		ft_echo(data);
	if (!ft_strcmp(data->cmd->cmd_param[0], "cd") || !ft_strcmp(data->cmd->cmd_param[0], "CD"))
		ft_cd(data);
	if (!ft_strcmp(data->cmd->cmd_param[0], "env") || !ft_strcmp(data->cmd->cmd_param[0], "ENV"))
		env(data->env, data->cmd->cmd_param);
	if (!ft_strcmp(data->cmd->cmd_param[0], "exit") || !ft_strcmp(data->cmd->cmd_param[0], "EXIT"))
			ft_exit(data);
	if (!ft_strcmp(data->cmd->cmd_param[0], "export") || !ft_strcmp(data->cmd->cmd_param[0], "EXPORT"))
		export(&data->env, data->cmd->cmd_param);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}
/*
verifie si la commande est un builtin
*/
int	is_builtin(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd_param[0], "pwd") || !ft_strcmp(data->cmd->cmd_param[0], "PWD"))
		return(1);
	if (!ft_strcmp(data->cmd->cmd_param[0], "echo") || !ft_strcmp(data->cmd->cmd_param[0], "ECHO"))
		return(1);
	if (!ft_strcmp(data->cmd->cmd_param[0], "cd") || !ft_strcmp(data->cmd->cmd_param[0], "CD"))
		return (1);
	if (!ft_strcmp(data->cmd->cmd_param[0], "env") || !ft_strcmp(data->cmd->cmd_param[0], "ENV"))
		return(1);
	if (!ft_strcmp(data->cmd->cmd_param[0], "exit") || !ft_strcmp(data->cmd->cmd_param[0], "EXIT"))
			return(1);
	if (!ft_strcmp(data->cmd->cmd_param[0], "export") || !ft_strcmp(data->cmd->cmd_param[0], "EXPORT"))
		return(1);
	return (0);
}
