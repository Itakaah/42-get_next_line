#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *buffer;
	char		*tmp;
	int			bytes_read;
	char		*old_buffer;
	char		*line;
	char		*index;

	// LECTURE 
	if (fd < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	index = ft_strchr(buffer, '\n');
	while (!index && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		old_buffer = buffer;
		buffer = ft_strjoin(buffer, tmp);
		index = ft_strchr(buffer, '\n');
		free(old_buffer);
	}
	if (bytes_read == 0 && buffer[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	// EXTRACTION et MISE A JOUR
	old_buffer = buffer;
	if (index)
	{
		line = ft_substr(buffer, 0, index - buffer + 1);
		buffer = ft_substr(buffer, index - buffer + 1, ft_strlen(buffer) - ft_strlen(line));
	}
	else
	{
		line = ft_strdup(buffer);
		buffer = NULL;
	}
	free(old_buffer);
	free(tmp);
	return (line);
}