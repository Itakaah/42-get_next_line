#include "get_next_line.h"

int	read_until_nl(int fd, char **buffer, char *tmp)
{
	int			bytes_read;
	char		*old_buffer;
	char		*index;

	bytes_read = 1;
	index = ft_strchr(*buffer, '\n');
	while (!index && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*buffer);
			*buffer = NULL;
			return (-1);
		}
		tmp[bytes_read] = '\0';
		old_buffer = *buffer;
		*buffer = ft_strjoin(*buffer, tmp);
		index = ft_strchr(*buffer, '\n');
		free(old_buffer);
	}
	if (bytes_read == 0 && (*buffer)[0] == '\0')
		return (0);
	return (1);
}

char	*extract_and_update(char **buffer)
{
	char		*old_buffer;
	char		*line;
	char		*index;
	size_t		line_len;
	size_t		buffer_len;

	buffer_len = ft_strlen(*buffer);
	index = ft_strchr(*buffer, '\n');
	old_buffer = *buffer;
	if (index)
	{
		line_len = index - *buffer + 1;
		line = ft_substr(*buffer, 0, line_len);
		*buffer = ft_substr(*buffer, line_len, buffer_len - ft_strlen(line));
	}
	else
	{
		line = ft_strdup(*buffer);
		*buffer = NULL;
	}
	free(old_buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	int			bytes_read;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	bytes_read = read_until_nl(fd, &buffer, tmp);
	if (bytes_read == -1 || bytes_read == 0)
	{
		free(tmp);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_and_update(&buffer);
	free(tmp);
	return (line);
}
