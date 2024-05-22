/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arenilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:24:23 by arenilla          #+#    #+#             */
/*   Updated: 2024/05/22 17:29:55 by arenilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*bytedst;
	const unsigned char	*bytesrc;

	bytedst = dst;
	bytesrc = src;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < len)
	{
		if (dst >= src)
		{
			bytedst[len - 1] = bytesrc[len - 1];
			len--;
		}
		if (dst < src)
		{
			bytedst[i] = bytesrc[i];
			i++;
		}
	}
	return (dst);
}

static char	*ft_read(int fd, char *totalbuf)
{
	char	*cpybuf;
	int		nread;

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
			return (NULL);
		}
		cpybuf[nread] = '\0';
		totalbuf = ft_strjoin(totalbuf, cpybuf);
		if (ft_strchr(totalbuf, '\n'))
			break ;
	}
	free(cpybuf);
	return (totalbuf);
}

static char	*ft_newline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	line = ft_memmove(line, buffer, i);
	if (buffer[i] != '\0' && buffer[i] == '\n')
		line = ft_strjoin(line, "\n");
	return (line);
}

static char	*ft_nextbuf(char *buffer)
{
	int		len;
	char	*nextb;

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
	len++;
	nextb = ft_memmove(nextb, &buffer[len], (ft_strlen(buffer) - len));
	free(buffer);
	return (nextb);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	oneline = ft_newline(buffer);
	buffer = ft_nextbuf(buffer);
	return (oneline);
}

/*int main()
{
    int		fd;
    char	*line;

//reading from file
    fd = open("prueba.txt", O_RDONLY);
    line = get_next_line(fd);
    if (line == NULL)
	printf("(null)");
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
    	line = get_next_line(fd);
    }
    if (line)
	free(line);
    close(fd);
//reading from stdin
    fd = 0;
    line = get_next_line(fd);
    if (line == NULL)
	printf("(null)");
    while (line != NULL)
    {
	printf("%s", line);
        free(line);
    	line = get_next_line(0);
    }
    if (line)
	free(line);
    return (0);
}*/
