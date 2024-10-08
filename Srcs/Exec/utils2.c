#include "../../Includes/minishell.h"
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

/*
verifie si la commande est un builtin et appelle le builtin
*/
int	is_builtin(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd_param[0], "pwd") || !ft_strcmp(data->cmd->cmd_param[0], "PWD"))
		return(ft_pwd());
	if (!ft_strcmp(data->cmd->cmd_param[0], "echo") || !ft_strcmp(data->cmd->cmd_param[0], "ECHO"))
		return(ft_echo(data));
	if (!ft_strcmp(data->cmd->cmd_param[0], "cd") || !ft_strcmp(data->cmd->cmd_param[0], "CD"))
		return (ft_cd(data));
	// if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "ENV"))
	// 	ft_env(data);
	if (!ft_strcmp(data->cmd->cmd_param[0], "exit") || !ft_strcmp(data->cmd->cmd_param[0], "EXIT"))
			return(ft_exit(data));
	if (!ft_strcmp(data->cmd->cmd_param[0], "export") || !ft_strcmp(data->cmd->cmd_param[0], "EXPORT"))
		return(export(&data->env, data->cmd->cmd_param));
	return (0);
}
