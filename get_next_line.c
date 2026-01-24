#include "get_next_line.h"

char	*clear_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*read_and_join(int fd, char *buffer)
{
	char	*tmp;
	char	*old;
	int		bytes;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (free(buffer), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[bytes] = '\0';
		old = buffer;
		buffer = ft_strjoin(old, tmp);
		free(old);
		if (!buffer)
			return (free(tmp), NULL);
	}
	return (free(tmp), buffer);
}

char	*extract_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(buffer, 0, i));
}

char	*update_buffer(char *buffer)
{
	size_t	i;
	char	*new_buf;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buf = ft_strdup(buffer + i);
	free(buffer);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	buffer = read_and_join(fd, buffer);
	if (!buffer || !buffer[0])
		return (clear_buffer(&buffer));
	line = extract_line(buffer);
	if (!line)
		return (clear_buffer(&buffer));
	buffer = update_buffer(buffer);
	return (line);
}
