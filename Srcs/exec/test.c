
//cree des doubles tableau a partir d'une liste chainee
//
//
char    **prepare_array(t_token **list);
{
    int i;
    int num_args;

    i = 0;
    num_args = find_len_list(list);
    char **args = malloc((num_args + 1) * sizeof(char *));
    if (!args)
    {
        ft_printf("malloc error");
        free(args);
        return ;
    }
    while (num_args > 0)
    {
        args[i] = ft_strdup((*list)->str);
        if (!args[i])
        {
            ft_free_array(args);
            return ;
        }
        i++;
        (*list) = (*list)->next;

        num_args--;
    }
    args[i] = NULL;
    return (args);
}

//avec la copie de l'environnement sous forme de liste chainee
char *find_path(char *str, t_data *data)
{

}