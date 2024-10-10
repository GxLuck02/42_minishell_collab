#include "../../../Includes/minishell.h"

int len_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}
int	exit_error(char *arg)
{
    ft_putstr_fd("bash: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}
bool	ft_is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

/*
1. verifier si l'argument de exit est un nombre
2. afficher exit
3. gerer les cas
    pas d'arg exit(0)
    1 arg verifier si c'est un nb et quitter avec
    plusieurs args error
*/
void    ft_exit(t_data *data)
{
    int exit_code;

    exit_code = 0;
    if (len_array(data->cmd->cmd_param) == 1)
    {
        ft_free_data(data);
        exit(0);
    }
    if (len_array(data->cmd->cmd_param) >= 2)
    {
        if(!ft_is_numeric(data->cmd->cmd_param[1]))
        {
            printf("bash: exit: %s: numeric argument required\n", data->cmd->cmd_param[1]);
            exit_code = ft_atoi(data->cmd->cmd_param[1]) % 256;
            //ft_free_data(data);
            exit(exit_code);
        }
    }
        if (len_array(data->cmd->cmd_param) > 2)
        {   printf("exit\nbash: exit too many arguments\n");
            return ;
        }
        exit_code = ft_atoi(data->cmd->cmd_param[1]) % 256;
        //ft_free_data(data);
        exit(exit_code);
}
