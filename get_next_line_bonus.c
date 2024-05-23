/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arenilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:24:23 by arenilla          #+#    #+#             */
/*   Updated: 2024/05/15 11:12:36 by arenilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char	*buffer[MAXFD];
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAXFD)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc(1, 1);
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	oneline = ft_newline(buffer[fd]);
	buffer[fd] = ft_nextbuf(buffer[fd]);
	return (oneline);
}

int main()
{
    int		fd1;
    int		fd2;
    int		fd3;
    char	*file1;
    char	*file2;
    char	*file3;

//reading some fd
    fd1 = open("prueba.txt", O_RDONLY);
    fd2 = open("prueba2.txt", O_RDONLY);
    fd3 = open("prueba3.txt", O_RDONLY);
    while (1) 
	{
        file1 = get_next_line(fd1);
        file2 = get_next_line(fd2);
        file3 = get_next_line(fd3);

        if (file1 == NULL && file2 == NULL && file3 == NULL) {
            break;
        }

        if (file1) {
            printf("%s", file1);
            free(file1);
        } else {
            printf("NULL\n");
        }

        if (file2) {
            printf("%s", file2);
            free(file2);
        } else {
            printf("NULL\n");
        }

        if (file3) {
            printf("%s", file3);
            free(file3);
        } else {
            printf("NULL\n");
        }
    }
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
