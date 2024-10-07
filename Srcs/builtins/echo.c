#include "../../Includes/minishell.h"


int check_n(char *cmd_param_1)
{
	int	i;

	i = 0;
	if (cmd_param_1[i] != '-')
		return (0);
	else
	{
		i++;
		while(cmd_param_1 && cmd_param_1[i])
		{
			if (cmd_param_1[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);

}

/*
verifie si il y a -n
et imprime ce qui est demande
*/
int ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (check_n(data->cmd->cmd_param[1]))
	{
		i = 2;
		while (data->cmd->cmd_param[i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		i = 1;
		while (data->cmd->cmd_param[i])
		{
			ft_putstr_fd(data->cmd->cmd_param[i], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
		ft_putstr_fd("\n", 2);
	}
	return (1);
}