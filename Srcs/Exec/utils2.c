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

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "PWD"))
	{
		ft_pwd();
		return (1);
	}
	return (0);
}