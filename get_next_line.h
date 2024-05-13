#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char    *ft_strdup(const char *s1);
char    *ft_strjoin(char const *s1, char const *s2);
void    *ft_memmove(void *dst, const void *src, size_t len);

#endif
