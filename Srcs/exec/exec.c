#include "../Includes/minishell.h"

//fonctionne comme getenv sur la liste chainee
// renvoie le noeud de la liste qui correspond a la variable demandee
t_list  *ft_getenv(char *var, t_list *env)
{
    while (env)
    {
        if (!ft_strcmp(var, env->name))
            return (env);
        env = env->next;
    }
    return (NULL);
}
int is_absolute_path(char *str)
{
    if (str[0] == '/')
        return (1);
    else
        return (0);
}
//retourne la longueur du tableau pour execve
int find_len_array(t_token *token)
{
    t_token *temp;
    int num_args;

    temp = token;
    if (temp->token_type == CMD)
    {
        num_args++;
        temp = temp->next;
    }
    while (temp->token_type == ARG)
    {
        num_args++;
        temp = temp->next;
    }
    return (num_args);
}
//
// cree le double tableau pour execve
// allouer de la place pour le tableau = cmd + args
// copier chaque cmd + args dans le double tableau
// PS: amelioration simple en fonction pour changer n'importe quelle liste chainee en double tableau
char    **prepare_array(t_token *token)
{
    int num_args;
    int i;

    i = 0;
    num_args = find_len_array(token);
    char **args = malloc((num_args + 1) * sizeof(char *));
    if (!args)
    {
        ft_printf("malloc error");
        free(args);
        return ;
    }
    while (num_args > 0)
    {
        args[i] = ft_strdup(token->str);
        if (!args[i])
        {
            ft_free_array(args);
            return ;
        }
        i++;
        token = token->next;
        num_args--;
    }
    args[i] = NULL;
    return (args);
}
//recupere le tableau d'args pour execve
//verifie si la commande est un chemin absolu
// si non appel find_path
//si oui execute la commande avec execve
void    execute_cmd(t_data *data)
{
    char **args;

    args = prepare_array(data->token);
    if (is_absolute_path(args[0]))
    {
        if (!access(args[0], F_OK && X_OK))
            execve(args[0], args, data->env);
        else
            {
                ft_printf("PATH error\n");
                return ;
            }
    else
        ft_getenv("PATH", data->env);
        
}

// verifier si c'est un builtin
// creer un double tableau avec la commande et les arguments pour execve
// execute_builtin
// else
void    handle_cmd(t_data *data)
{
    execute_cmd(data);
}


// parcours la ligne de commande
// gere heredoc
//si pipe ou redir configure
// si il y a une commande ajoute les arguments
//check si la commande est un builtins ou externe
//fork execve pour executer la commande
//passe au token suivant
//sort de la boucle a la fin de la ligne de commande
void exec(t_data *data)
{
    while((data->token))
    {
        if (data->token->token_type == CMD)
            handle_cmd(data);
    }
}
 