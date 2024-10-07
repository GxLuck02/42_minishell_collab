#include "../../../Includes/minishell.h"

int ft_exit(t_data *data)
{
    (void)data;
    puts("in exit\n");
    exit(0);
    return (1);
}