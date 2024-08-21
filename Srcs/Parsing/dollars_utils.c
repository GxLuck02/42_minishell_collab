/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:15:12 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/13 15:54:58 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

//Calculate the length of a var like VAR=salut
int	len_var(char *str, char *env)
{
	int	i;

	i = 0;
	if (!str || !env)
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == ft_search(env, '='))
		return (i);
	return (0);
}

//Calculate the length of a chained list
int	len_list(t_list *list)
{
	int		len;
	t_list	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	len = 1;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

//returns the name of the var ($VAR return VAR) 
char	*get_dollar_word(char *line, int size)
{
	char	*key;
	int		i;

	if (line == NULL)
		return (NULL);
	i = 0;
	key = malloc(size * sizeof(char));
	if (!key)
		return (NULL);
	while (line[++i] && i < size)
		key[i - 1] = line[i];
	key[i - 1] = '\0';
	return (key);
}

//search in env the $VAR and replace in string if $VAR exist
char	*get_value(t_list *env, char *key)
{
	t_list	*tmp;
	int		len_key;

	if (!env || !key)
		return (NULL);
	tmp = env;
	len_key = ft_strlen(key);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, key, len_key) == 0 && \
			tmp->str[len_key] == '=')
			return (ft_strdup(&(tmp->str[len_key + 1])));
		tmp = tmp->next;
	}
	return (NULL);
}

// This function checks if a variable exists in the environment list.
int	exist_in_env(t_data *data, int *i, char *str)
{
	t_list	*tmp;
	int		len;
	int		len_word;

	if (str[*i + 1] == '?')
		return (2);
	if (str[*i + 1] == '$')
		return (3);
	tmp = data->env;
	len = len_list(tmp);
	while (len--)
	{
		len_word = len_var(&str[*i + 1], tmp->str);
		if ((ft_strncmp(tmp->str, &str[*i + 1], \
				len_word) == 0) && len_word > 0)
		{
			*i += (len_word + 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
