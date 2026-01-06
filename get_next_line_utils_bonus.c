#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *backup, int c)
{
	int		i;
	char	ptr;

	i = 0;
	if (!backup)
		return (NULL);
	ptr = ((char)c);
	while (backup[i])
	{
		if (backup[i] == ptr)
			return ((char *)&backup[i]);
		i++;
	}
	if (backup[i] == ptr)
		return ((char *)&backup[i]);
	return (NULL);
}

char	*ft_strjoin(char *backup, char *buffer)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!backup || !buffer)
		return (NULL);
	len = ft_strlen(backup) + ft_strlen(buffer);
	new = (char *)malloc(sizeof (char) * (len + 1));
	if (!new)
	{
		free(backup);
		return (NULL);
	}
	i = -1;
	while (backup[++i])
		new[i] = backup[i];
	while (buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	free (backup);
	return (new);
}
