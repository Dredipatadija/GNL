#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static char	*ft_read(int fd,char *totalbuf)
{
	char	*cpybuf;
	char	*tmp;
	int	nread;

	tmp = ft_calloc(1, 1);
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

static char	*ft_newline(char *buffer)
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
	line = ft_memmove(line, buffer, len);
	return (line);
}

static char	*ft_nextbuf(char *buffer)
{
	int		i;
	int		len;
	char	*nextb;
	
	i = 0;
	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	nextb = ft_calloc((ft_strlen(buffer) - len + 1), sizeof(char));
	if (!nextb)
	{
		free(buffer);
		return (NULL);
	}
	nextb = ft_memmove(nextb, &buffer[len + 1], (ft_strlen(buffer) - len));
	free(buffer);
	return (nextb);
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
	buffer = ft_nextbuf(buffer);
	return (oneline);
}

int main()
{
    int     fd;
    char    *line;

    fd = open("prueba.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
