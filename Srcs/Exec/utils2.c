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
		puts("111\n");
		temp = temp->next;
		len++;
	}
	return (len);
}