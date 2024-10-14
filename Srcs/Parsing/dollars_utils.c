/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:15:12 by ttreichl          #+#    #+#             */
/*   Updated: 2024/10/09 18:06:45 by tmontani         ###   ########.fr       */
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
char	*get_value(t_env *env, char *key)
{
	t_env	*tmp;
	int		len_key;

	if (!env || !key)
		return (NULL);
	tmp = env;
	len_key = ft_strlen(key);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, len_key) == 0 && key[len_key + 1] == '\0')
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*word_var(char *word)
{
	int		len;
	int		i;
	char	*new_str;

	len = 0;
	i = 0;
	while (ft_isalpha(word[i]) != 0)
	{
		i++;
		len++;
	}
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = word[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	exist_in_env(t_data *data, int *i, char *str)
{
	t_env	*tmp;
	char	*key_to_find;
	size_t	key_length;

	if (str[*i + 1] == '?')
		return (2);
	if (str[*i + 1] == '$')
		return (3);
	key_to_find = word_var(&str[*i + 1]);
	tmp = data->env;
	while (tmp)
	{
		key_length = ft_strlen(tmp->key);
		if (ft_strncmp(tmp->key, key_to_find, key_length) == 0 && \
			key_to_find[key_length + 1] == '\0')
		{
			*i += key_length + 1;
			free(key_to_find);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key_to_find);
	return (0);
}
