#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int	fd;
	char	*line;
	int	line_count;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur : impossible d'ouvrir test.txt\n");
		return (1);
	}

	line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d: %s", line_count, line);
		free(line);
		line_count++;
	}

	close(fd);
	return (0);
}