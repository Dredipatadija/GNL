#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static char	*ft_read(int fd,char *totalbuf)
{
	char	*cpybuf;
	char	*tmp;
	int	nread;

	if (!tmp)
	{
		tmp = ft_calloc(1, 1);
		tmp[0] = '\0';
	}
	cpybuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cpybuf)
		return (NULL);
	nread = 1;
	while (nread > 0)
	{
		nread = read(fd, cpybuf, BUFFER_SIZE);
		if (nread == -1)
		{
			free(cpybuf);
			if (tmp)
				free(tmp);
			return (NULL);
		}
		cpybuf[nread] = '\0';
		totalbuf = ft_strjoin(tmp, cpybuf);
		free(cpybuf);
		free(tmp);
		tmp = ft_strdup(totalbuf);
	}
	free(tmp);
	return (totalbuf);
}

char	*ft_newline(char *buffer)
{
	char	*line;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	if (buffer[len] != 0 && buffer[len] == '\n')
	{
		line = ft_calloc(len + 2, sizeof(char));
		line[len + 1] = '\n';
	}
	else 
		line = ft_calloc(len + 1, sizeof(char));
	line = ft_memmove(line, buffer, len - 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	oneline = ft_newline(buffer);
	return (buffer);
}

/*int	main(void)
{
	int	fd;
	char	*buffer;

	fd = open("prueba.txt", O_RDONLY);
	while ((buffer = get_next_line(fd)) != NULL)
		printf("%s\n", buffer);
	return (0);
}*/
