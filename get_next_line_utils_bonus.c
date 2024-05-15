/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arenilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:24:36 by arenilla          #+#    #+#             */
/*   Updated: 2024/05/15 10:47:24 by arenilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*array;
	size_t			i;

	array = malloc(count * size);
	if (!array)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		array[i] = 0;
		i++;
	}
	return ((void *) array);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	character;

	character = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (character == s[i])
			return ((char *)(&s[i]));
		else
			i++;
	}
	if (character == '\0')
		return ((char *)(&s[i]));
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*scpy;
	size_t	size;
	size_t	j;

	size = ft_strlen(s1);
	scpy = (char *) malloc(size + 1);
	if (!scpy)
		return (0);
	j = 0;
	while (s1[j])
	{
		scpy[j] = s1[j];
		j++;
	}
	scpy[j] = '\0';
	return (scpy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenght;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	lenght = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
