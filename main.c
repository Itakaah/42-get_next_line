#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("Premiere ligne : %s", get_next_line(fd));
	printf("Deuxieme ligne : %s", get_next_line(fd));
	printf("Derniere ligne : %s", get_next_line(fd));
	printf("Trop ligne : %s", get_next_line(fd));
}