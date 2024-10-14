#include "../../Includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
	{
		perror("pwd");
		return (0);
	}
}