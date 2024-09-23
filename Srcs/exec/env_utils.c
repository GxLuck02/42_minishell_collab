#include "../Includes/minishell.h"


// fonction pour remplir les variables name et value de la liste env

void    ft_get_name_env(t_list *env)
{
    int i;

    i = 0;
    while (env)
    {
        i = 0;
        while (env->str[i] != '=')
            i++;
        env->name = (char *)malloc(sizeof(char) * (i + 1));
        if(!env->name)
            return ;
        i = 0;
        while (env->str[i] != '=')
        {
            env->name[i] = env->str[i];
            i++;
        }
        env->name[i] = '\0';
        env = env->next;
    }
    
}

void    ft_get_value_env(t_list *env)
{
    int     i;
    char    *str_value;

    i = 0;
    while (env)
    {
        str_value = ft_strchr(env->str, '=');
        str_value++;
        i = ft_strlen(str_value);
        env->value = (char *)malloc(sizeof(char) * (i + 1));
        if(!env->value)
            return ;
        i = 0;
      ft_strcpy(env->value, str_value);
      env = env->next;
    }
}
