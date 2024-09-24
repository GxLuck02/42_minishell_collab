#include "../../Includes/minishell.h"

static void	print_array(char **array)
{
	int	j;

	j = 0;
	while(array[j])
	{
		printf("%s\n", array[j]);
		j++;

	}
}
static void	ft_free(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
}

static char	*fill_word(const char *str, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * (len + 2)); // je fais len + 2 pour avoir la place de mettre '/' et '\0'
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_array(const char *path, char sep, char **array, size_t word_count)
{
	size_t	len;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	while (a < word_count)
	{
		len = 0;
		while (path[i] == sep)
			i++;
		while (path[i + len] != sep && path[i + len])
			len++;
		array[a] = fill_word(path + i, len);
		array[a][len] = '/';
		array[a][len + 1] = '\0';
		i = i + len;
		a++;
	}
	array[a] = NULL;
	return (array);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split_path(char const *path, char c)
{
	size_t	word_count;
	char	**array;

	word_count = ft_count_word(path, c);
	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_array(path, c, array, word_count))
	{
		ft_free(array, word_count);
		return (NULL);
	}
	print_array(array);
	return (array);
}

