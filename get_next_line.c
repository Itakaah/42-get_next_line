
#include "get_next_line.h"

static char	*read_and_reserve(int fd, char *reserve)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(reserve, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		reserve = ft_strjoin(reserve, buffer);
	}
	free(buffer);
	return (reserve);
}

static char	*extract_line(char *reserve)
{
	int		i;
	char	*line;

	i = 0;
	if (!reserve[i])
		return (NULL);
	while (reserve[i] && reserve[i] != '\n')
		i++;
	line = ft_substr(reserve, 0, i + 1);
	return (line);
}

static char	*update_reserve(char *reserve)
{
	int		i;
	char	*new_reserve;

	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i])
	{
		free(reserve);
		return (NULL);
	}
	new_reserve = ft_substr(reserve, i + 1, ft_strlen(reserve) - i);
	free(reserve);
	return (new_reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = read_and_reserve(fd, reserve);
	if (!reserve)
		return (NULL);
	line = extract_line(reserve);
	reserve = update_reserve(reserve);
	return (line);
}