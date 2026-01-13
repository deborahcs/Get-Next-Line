
#include "get_next_line.h"

static char	*ft_read_line(int fd, char *backup)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(backup);
		return (NULL);
	}
	read_bytes = 1;
	while (!ft_strchr(backup, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	free(buffer);
	return (backup);
}

static char	*ft_cut_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup || !backup[0])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_store_rest(char *backup)
{
	int		i;
	int		j;
	char	*new_backup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = (char *)malloc((ft_strlen(backup) - i + 1) * sizeof(char));
	if (!new_backup)
	{
		free(backup);
		return (NULL);
	}
	i++;
	j = 0;
	while (backup[i])
		new_backup[j++] = backup[i++];
	new_backup[j] = '\0';
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup = NULL;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup)
	{
		backup = (char *)malloc(1 * sizeof(char));
		if (!backup)
			return (NULL);
		backup[0] = '\0';
	}
	if (!ft_strchr(backup, '\n'))
		backup = ft_read_line(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_cut_line(backup);
	backup = ft_store_rest(backup);
	return (line);
}
/*#include <fcntl.h>
#include <stdio.h>

int main ()
{
	int	fd;
	char	*line;
	
	fd = open("teste.txt", O_RDONLY);

	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

}*/
