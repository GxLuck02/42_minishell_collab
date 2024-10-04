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

// int	is_builtin(t_data *data)
// {
// 	char *cmd;
// 	int	flag;

// 	cmd = data->cmd->cmd_param[0];
// 	if (!ft_strcmp(data-cmd, "pwd") || !ft_strcmp(cmd, "PWD"))
// 		flag = ft_pwd();
// 	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "ECHO"))
// 			flag = ft_echo(data->cmd->cmd_param);
	// if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "CD"))
	// 	ft_cd(data);
	// if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "ENV"))
	// 	ft_env(data);
	// if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "EXIT"))
	// 	ft_exit(data);
	//export
	//exit

// 	return (flag);
// }
