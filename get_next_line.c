#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	*ft_calloc(size_t count, size_t size);

char	*get_next_line(int fd)
{
	size_t	reader;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	reader = read(fd, buffer, BUFFER_SIZE);
	if (reader < 1)
	{
		free(buffer);
		return (0);
	}
	return (buffer);
}

int	main(void)
{
	int	fd;
	char	*buffer;

	fd = open("prueba.txt", O_RDONLY);
	while ((buffer = get_next_line(fd)) != NULL)
		printf("%s\n", buffer);
	return (0);
}
